#pragma once
#include <memory>
#include <cstdint>
using std::unique_ptr;

unique_ptr<uint8_t[]> ReadNetpbm(int &width, int &height, int &num_channel, bool &success, const char *filename);
void WriteNetpbm(uint8_t* i, const int width, const int height, const int num_channel, const char *filename, const char *magic);
void WritePGM(uint8_t* i, const int width, const int height, const char *filename);
void WritePPM(uint8_t* i, const int width, const int height, const char *filename);

