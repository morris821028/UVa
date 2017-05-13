#include "pgm.h"

inline int peekc(FILE *fp)
{
	int peeked = getc(fp);
	ungetc(peeked, fp);
	return peeked;
}

unique_ptr<uint8_t[]> ReadNetpbm(int &width, int &height, int &num_channel, bool &success, const char *filename)
{
#define FAIL_IF(cond)\
	if (cond) {\
		success = false;\
		return i;\
	}
	unique_ptr<uint8_t[]> i;

	FILE *fp = fopen(filename, "rb");
	FAIL_IF(not fp);

	char magic[3];
	fread(magic, 1, 3, fp);
	FAIL_IF(magic[0] != 'P' or magic[2] != '\n' or (magic[1] != '5' and magic[1] != '6'));

	num_channel = magic[1] == '5' ? 1 : 3;
	while (peekc(fp) == '#') {
		while (getc(fp) != '\n');
	}

	int norm;
	FAIL_IF(fscanf(fp, "%d %d\n%d\n", &width, &height, &norm) != 3);
	FAIL_IF(norm != 255);
	
	int nbytes = width*height*num_channel;
	i.reset(new uint8_t[nbytes]);
	FAIL_IF(fread(i.get(), 1, nbytes, fp) != nbytes);

#undef FAIL_IF
	success = true;
	return i;
}

void WriteNetpbm(uint8_t* i, const int width, const int height, const int num_channel, const char *filename, const char *magic)
{
	const int num_pixel = width*height;
	const int num_element = num_pixel*num_channel;
	FILE *fp = fopen(filename, "wb");
	fprintf(fp, "%s\n%d %d\n255\n", magic, width, height);
	fwrite(i, 1, num_element, fp);
}

void WritePGM(uint8_t* i, const int width, const int height, const char *filename)
{
	WriteNetpbm(i, width, height, 1, filename, "P5");
}

void WritePPM(uint8_t* i, const int width, const int height, const char *filename)
{
	WriteNetpbm(i, width, height, 3, filename, "P6");
}
