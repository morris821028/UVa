#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#define SINGLE_ONE_BIT 0x80
#define BLOCK_SIZE 512
#define MOD_SIZE 448
#define APP_SIZE 64
#define BITS 8
// MD5 Chaining Variable
#define A 0x67452301UL
#define B 0xEFCDAB89UL
#define C 0x98BADCFEUL
#define D 0x10325476UL
// Creating own types
#ifdef UINT64
# undef UINT64
#endif
#ifdef UINT32
# undef UINT32
#endif
typedef unsigned long long UINT64;
typedef unsigned long UINT32;
typedef unsigned char UINT8;
typedef struct
{
char * message;
UINT64 length;
}STRING;
const UINT32 X[4][2] = {{0, 1}, {1, 5}, {5, 3}, {0, 7}};
// Constants for MD5 transform routine.
const UINT32 S[4][4] = {
{ 7, 12, 17, 22 },
{ 5, 9, 14, 20 },
{ 4, 11, 16, 23 },
{ 6, 10, 15, 21 }
};
// F, G, H and I are basic MD5 functions.
UINT32 F( UINT32 X, UINT32 Y, UINT32 Z )
{
return ( X & Y ) | ( ~X & Z );
}
UINT32 G( UINT32 X, UINT32 Y, UINT32 Z )
{
return ( X & Z ) | ( Y & ~Z );
}
UINT32 H( UINT32 X, UINT32 Y, UINT32 Z )
{
return X ^ Y ^ Z;
}
UINT32 I( UINT32 X, UINT32 Y, UINT32 Z )
{
return Y ^ ( X | ~Z );
}
// rotates x left s bits.
UINT32 rotate_left( UINT32 x, UINT32 s )
{
return ( x << s ) | ( x >> ( 32 - s ) );
}
// Pre-processin
UINT32 count_padding_bits ( UINT32 length )
{
	UINT32 div = length * BITS / BLOCK_SIZE;
	UINT32 mod = length * BITS % BLOCK_SIZE;
	UINT32 c_bits;
	if ( mod == 0 )
	c_bits = MOD_SIZE;
	else
	c_bits = ( MOD_SIZE + BLOCK_SIZE - mod ) % BLOCK_SIZE;
	return c_bits / BITS;
}
STRING append_padding_bits ( char * argv )
{
	UINT32 msg_length = strlen ( argv );
	UINT32 bit_length = count_padding_bits ( msg_length );
	UINT64 app_length = msg_length * BITS;
	//printf("%u %u %llu %s\n", msg_length, bit_length, app_length, argv);
	STRING string;
	string.message = (char *)malloc(msg_length + bit_length + APP_SIZE / BITS);
	//printf("%u\n", msg_length + bit_length + APP_SIZE / BITS);
	// Save message
	strncpy ( string.message, argv, msg_length );
	// Pad out to mod 64.
	memset ( string.message + msg_length, 0, bit_length );
	string.message [ msg_length ] = SINGLE_ONE_BIT;
	// Append length (before padding).
	memmove ( string.message + msg_length + bit_length, (char *)&app_length, sizeof( UINT64 ) );
	string.length = msg_length + bit_length + sizeof( UINT64 );
	/*for(int a = 0; a < string.length; a++)
		printf("%u ", string.message[a]);
	puts("");*/
	return string;
}
int main ( int argc, char *argv[] )
{
	STRING string;
	UINT32 w[16];
	UINT32 chain[4];
	UINT32 state[4];
	UINT8 r[16];
	UINT32 ( *auxi[ 4 ])( UINT32, UINT32, UINT32 ) = { F, G, H, I };
	int roundIdx;
	int argIdx;
	int sIdx;
	int wIdx;
	int i;
	int j;
	if ( argc < 2 )
	{
		fprintf ( stderr, "usage: %s string ...\n", argv[ 0 ] );
		return EXIT_FAILURE;
	}
	for ( argIdx = 1; argIdx < argc; argIdx++ )
	{
		string = append_padding_bits ( argv[ argIdx ] );	
// MD5 initialization.
		chain[0] = A;
		chain[1] = B;
		chain[2] = C;
		chain[3] = D;
		for ( j = 0; j < string.length; j += BLOCK_SIZE / BITS)
		{
			memmove ( (char *)w, string.message + j, BLOCK_SIZE / BITS );
			memmove ( state, chain, sizeof(chain) );

			for ( roundIdx = 0; roundIdx < 4; roundIdx++ )
			{
				wIdx = X[ roundIdx ][ 0 ];
				
				sIdx = 0;
				for ( i = 0; i < 16; i++ )
				{
				// FF, GG, HH, and II transformations for rounds 1, 2, 3, and 4.
				// Rotation is separate from addition to prevent recomputation.
					state[sIdx] = state [ (sIdx + 1) % 4 ] +
					rotate_left ( state[sIdx] +
					( *auxi[ roundIdx ] )
					( state[(sIdx+1) % 4], state[(sIdx+2) % 4], state[(sIdx+3) % 4]) +
					w[ wIdx ] +(UINT32)floor( (1ULL << 32) * fabs(sin( roundIdx * 16 + i + 1 )) ),
					S[ roundIdx ][ i % 4 ]);
					printf("wIdx %0x %u\n", w[wIdx], wIdx);
					//printf("ABCD%d %d %d %d %d)\n", roundIdx, (sIdx) % 4, (sIdx+1)%4, (sIdx+2)%4, (sIdx+3)%4);
					//printf("%x %x %x %x %x %x %x\n", state[0], state[1], state[2], state[3], w[wIdx], S[roundIdx][i%4], (UINT32)floor( (1ULL << 32) * fabs(sin( roundIdx * 16 + i + 1 ))));
					sIdx = ( sIdx + 3 ) % 4;
					wIdx = ( wIdx + X[ roundIdx ][ 1 ] ) & 0xF;
					}
				//puts("XXXXXXXXXXXXXXXX");
				
			}
			
			chain[ 0 ] += state[ 0 ];
			chain[ 1 ] += state[ 1 ];
			chain[ 2 ] += state[ 2 ];
			chain[ 3 ] += state[ 3 ];
		}
		//printf("%u %u %u %u\n", chain[0], chain[1], chain[2], chain[3]);
		memmove ( r + 0, (char *)&chain[0], sizeof(UINT32) );
		memmove ( r + 4, (char *)&chain[1], sizeof(UINT32) );
		memmove ( r + 8, (char *)&chain[2], sizeof(UINT32) );
		memmove ( r + 12, (char *)&chain[3], sizeof(UINT32) );
		for ( i = 0; i < 16; i++ )
			printf ( "%02x", r[i]);
			putchar ( '\n' );
	}
	return EXIT_SUCCESS;
} 
/*
computer-based schemes of the present. The results of cryptanalysis have also changed ¡X it is no longer possible to have
110001101101111011011010111011101010111010001100101011100100010110101100010011000010111001101100101011001000010011100110110001101101000011001010110110101100101011100110010011011110110011000100111010001101000011001010010011101110010011001010111001101100101011011100111010000101110001001010100011010000110010100100111001001100101011100110111010101101100011101000111001100100110111101100110001001100011011100100111100101110111010001100001011011100110000101101100011110010111001101101001011100110010011010000110000101110110011001010010011000010110110001110011011011110010011000110110100001100001011011100110011101100101011001000010101000010101100000100110100101110100001001101001011100110010011011100110111100100110110001101111011011100110011101100101011100100010011101101111011100110111001101101001011000100110110001100101001001110100011011110010011010000110000101110110011001011000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001101101011
*/
