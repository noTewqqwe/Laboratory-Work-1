#pragma once

#include <string>

enum class BitOp { Set, Clear, Toggle };

void enableConsole();

void printSizes();

void printIntBits(int value, const std::string& name);
void printUnsignedBits(unsigned int value, const std::string& name);
void printFloatBits(float value, const std::string& name);
void printDoubleBits(double value, const std::string& name);

unsigned int modifyBit(unsigned int value, int n, BitOp op);
unsigned long long modifyBit(unsigned long long value, int n, BitOp op);
int modifyBit(int value, int n, BitOp op);
float modifyBit(float value, int n, BitOp op);
double modifyBit(double value, int n, BitOp op);

bool testBit(unsigned long long value, int n);
const char* opName(BitOp op);
