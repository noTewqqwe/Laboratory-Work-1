#define NOMINMAX
#include "bits.h"

#include <iostream>
#include <iomanip>
#include <cstring>
#include <Windows.h>

using namespace std;

static const char* const RED = "\033[31m";
static const char* const YELLOW = "\033[33m";
static const char* const GREEN = "\033[32m";
static const char* const GRAY = "\033[90m";
static const char* const RESET = "\033[0m";

void enableConsole() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;
    if (GetConsoleMode(h, &mode)) {
        SetConsoleMode(h, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    }
}

struct SizeRow {
    const char* name;
    size_t size;
    const char* note;
};

void printSizes() {
    const SizeRow rows[] = {
        { "bool ",          sizeof(bool),               "  логическое значение" },
        { "char ",          sizeof(char),               "  всегда 1 байт" },
        { "short int ",     sizeof(short int),          "  не меньше 16 бит" },
        { "int ",           sizeof(int),                "  на современных платформах 32 бита" },
        { "unsigned int ",  sizeof(unsigned int),       "  тот же размер, что у int, но без знака" },
        { "long int ",      sizeof(long int),           "  4 байта на Windows, 8 на Linux x64" },
        { "long long ",     sizeof(long long),          "  не меньше 64 бит" },
        { "float ",         sizeof(float),              "  IEEE 754 binary32" },
        { "double ",        sizeof(double),             "  IEEE 754 binary64" },
        { "long double ",   sizeof(long double),        "  8 байт в MSVC, 16 байт в GCC на x64" },
    };
    for (const SizeRow& r : rows) {
        cout << "  " << left << setw(13) << r.name << " — " << r.size  << " байт " << " — " << r.note << '\n';
    }
}

bool testBit(unsigned long long value, int n) {
    return ((value >> n) & 1ULL) != 0;
}

static void printIntegerBits(unsigned long long bits, int width, bool isSigned) {
    bool neg = isSigned && testBit(bits, width - 1);
    int start = isSigned ? 1 : 0;
    int first = -1;
    for (int i = start; i < width; i++) {
        if (testBit(bits, width - 1 - i) != neg) {
            first = i;
            break;
        }
    }

    cout << "  ";
    for (int i = 0; i < width; i++) {
        const char* color;
        if (isSigned && i == 0) {
            color = RED;
        }
        else if (first == -1 || i < first) {
            color = GRAY;
        }
        else {
            color = GREEN;
        }
        cout << color << (testBit(bits, width - 1 - i) ? '1' : '0') << RESET;
        if (isSigned && i == 0) {
            cout << ' ';
        }
    }
    cout << '\n';
}

void printIntBits(int value, const string& name) {
    cout << "\n[" << name << "]  value = " << value << "  &value = " << &value << '\n';
    printIntegerBits(static_cast<unsigned int>(value), sizeof(int) * 8, true);
}

void printUnsignedBits(unsigned int value, const string& name) {
    cout << "\n[" << name << "]  value = " << value << "  &value = " << &value << '\n';
    printIntegerBits(value, sizeof(unsigned int) * 8, false);
}

static void printFloatingBits(unsigned long long bits, int width, int expBits, const string& expLabel, const string& mantLabel) {
    int mantBits = width - 1 - expBits;

    cout << "  " << RED << "знак" << RESET << " | "
         << YELLOW << "порядок (" << expLabel << ")" << RESET << " | "
         << GREEN << "мантисса (" << mantLabel << ")" << RESET << "\n  ";

    for (int i = 0; i < width; i++) {
        if (i == 0) cout << RED;
        if (i == 1) cout << YELLOW;
        if (i == 1 + expBits) cout << GREEN;

        cout << (testBit(bits, width - 1 - i) ? '1' : '0');

        if (i == 0 || i == expBits) cout << RESET << ' ';
    }
    cout << RESET << '\n';

}

void printFloatBits(float value, const string& name) {
    unsigned int bits;
    memcpy(&bits, &value, sizeof bits);
    cout << "\n[" << name << "]  value = " << value << "  &value = " << &value << "  bits = " << bits << '\n';
    printFloatingBits(bits, sizeof(float) * 8, 8, "8 бит", "23 бита");
}

void printDoubleBits(double value, const string& name) {
    unsigned long long bits;
    memcpy(&bits, &value, sizeof bits);
    cout << "\n[" << name << "]  value = " << value << "  &value = " << &value << "  bits = " << bits << '\n';
    printFloatingBits(bits, sizeof(double) * 8, 11, "11 бит", "52 бита");
}

unsigned int modifyBit(unsigned int value, int n, BitOp op) {
    unsigned int mask = 1u << n;
    switch (op) {
    case BitOp::Set:    value |= mask;  break;
    case BitOp::Clear:  value &= ~mask; break;
    case BitOp::Toggle: value ^= mask;  break;
    }
    return value;
}

unsigned long long modifyBit(unsigned long long value, int n, BitOp op) {
    unsigned long long mask = 1ULL << n;
    switch (op) {
    case BitOp::Set:    value |= mask;  break;
    case BitOp::Clear:  value &= ~mask; break;
    case BitOp::Toggle: value ^= mask;  break;
    }
    return value;
}

int modifyBit(int value, int n, BitOp op) {
    return static_cast<int>(modifyBit(static_cast<unsigned int>(value), n, op));
}

float modifyBit(float value, int n, BitOp op) {
    unsigned int bits;
    memcpy(&bits, &value, sizeof bits);
    bits = modifyBit(bits, n, op);
    memcpy(&value, &bits, sizeof value);
    return value;
}

double modifyBit(double value, int n, BitOp op) {
    unsigned long long bits;
    memcpy(&bits, &value, sizeof bits);
    bits = modifyBit(bits, n, op);
    memcpy(&value, &bits, sizeof value);
    return value;
}

const char* opName(BitOp op) {
    switch (op) {
    case BitOp::Set:    return "установить (|=)";
    case BitOp::Clear:  return "сбросить (&= ~)";
    case BitOp::Toggle: return "инвертировать (^=)";
    }
    return "";
}
