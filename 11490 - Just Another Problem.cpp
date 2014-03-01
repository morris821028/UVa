#include <iostream>
#include <cmath>
using namespace std ;
void in( long long & d )
{
    char q ;
    d = 0 ;
    do
    {
        q = getchar() ;
    }
    while ( q < 48 || q > 57 ) ;
    do
    {
        d = d * 10 + ( q ^ 48 ) ;
        q = getchar() ;
    }
    while ( q >= 48 && q <= 57 ) ;
}
int main ()
{
    long long n , sq , N1 , N2 , j , i , a[ 100000 ] , ans ;
    bool ck , first = true ;
    while ( in( n ) , n )
    {
        first = false ;
        ans = 0 ;
        ck = false ;
        sq = ( long long ) sqrt( ( double ) n ) ;
        if ( n & 1 )
        {
            for ( i = 1 ; i <= sq ; i += 2 )
            {
                if ( n % i == 0 )
                {
                    j = n / i ;
                    N1 = ( n / j - 6 * j ) / 7 ;
                    N2 = ( n / i - 6 * i ) / 7 ;
                    if ( N1 > 0 && n / j == 6 * j + 7 * N1 )
                    {
                        ck = true ;
                        N1 %= 100000007 ;
                        a[ ans ++ ] = ( 2 * N1 * N1 ) % 100000007 ;
                    }
                    if ( N2 > 0 && n / i == 6 * i + 7 * N2 && N1 != N2 )
                    {
                        ck = true ;
                        N2 %= 100000007 ;
                        printf( "Possible Missing Soldiers = %lld\n" , ( 2 * N2 * N2 ) % 100000007 ) ;
                    }
                }
            }
        }
        else
        {
            for ( i = 1 ; i <= sq ; i ++ )
            {
                if ( n % i == 0 )
                {
                    j = n / i ;
                    N1 = ( n / j - 6 * j ) / 7 ;
                    N2 = ( n / i - 6 * i ) / 7 ;
                    if ( N1 > 0 && n / j == 6 * j + 7 * N1 )
                    {
                        ck = true ;
                        N1 %= 100000007 ;
                        a[ ans ++ ] = ( 2 * N1 * N1 ) % 100000007 ;
                    }
                    if ( N2 > 0 && n / i == 6 * i + 7 * N2 && N1 != N2 )
                    {
                        ck = true ;
                        N2 %= 100000007 ;
                        printf( "Possible Missing Soldiers = %lld\n" , ( 2 * N2 * N2 ) % 100000007 ) ;
                    }
                }
            }
        }
        for ( i = ans - 1 ; i >= 0 ; i -- )
        {
            printf( "Possible Missing Soldiers = %lld\n" , a[ i ] ) ;
        }
        if ( ! ck )
        {
            puts( "No Solution Possible" ) ;
        }
        puts( "" ) ;
    }
}
