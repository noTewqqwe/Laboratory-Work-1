#include "bits.h"
#include "individual.h"

#include <iostream>
#include <limits>
#include <string>

using namespace std;

int main() {
    enableConsole();

    cout << "=== Этап 2. Размеры типов\n";
    printSizes();

    cout << "\n=== Этап 3. Целые числа: int\n";
    int k;
    cout << "введите целое число - ";
    cin >> k;
    const int ints[] = { 5, -5, 0, 2147483647, -2147483648, k};
    const string intNames[] = {
        "положительное (5)",
        "отрицательное (-5)",
        "ноль (0)",
        "максимум int (2147483647)",
        "минимум int (-2147483648)",
        "пользователь"
    };
    for (int i = 0; i < 6; i++) {
        printIntBits(ints[i], intNames[i]);
    }

    cout << "\n=== Этап 3. Целые числа: unsigned int\n";
    int kk;
    cout << "введите целое число - ";
    cin >> kk;
    const unsigned int uints[] = { 5u, 0u, 4294967295u, static_cast<unsigned int>(-5), static_cast<unsigned int>(kk)};
    const string uintNames[] = {
        "5",
        "ноль (0)",
        "максимум unsigned (4294967295)",
        "-5, приведённое к unsigned",
        "пользователь"
    };
    for (int i = 0; i < 5; i++) {
        printUnsignedBits(uints[i], uintNames[i]);
    }

    const float finf = numeric_limits<float>::infinity();
    const double dinf = numeric_limits<double>::infinity();

    cout << "\n=== Этап 4. float\n";
    int kkk;
    cout << "введите число одинарной точности - ";
    cin >> kkk;
    const float floats[] = { 3.14f, -2.5f, 0.0f, -0.0f, 1.4e-45f, finf, -finf, static_cast<float>(kkk)};
    const string floatNames[] = {
        "3.14",
        "-2.5",
        "ноль (0.0)",
        "отрицательный ноль (-0.0)",
        "денормализованное (1.4e-45)",
        "+inf",
        "-inf",
        "пользователь"
    };
    for (int i = 0; i < 8; i++) {
        printFloatBits(floats[i], floatNames[i]);
    }

    cout << "\n=== Этап 4. double\n";
    int kkkk;
    cout << "введите число двойной точности с плавающей точкой - ";
    cin >> kkkk;
    const double doubles[] = { 3.14, -2.5, 0.0, -0.0, 4.9e-324, dinf, -dinf, static_cast<double>(kkkk)};
    const string doubleNames[] = {
        "3.14",
        "-2.5",
        "ноль (0.0)",
        "отрицательный ноль (-0.0)",
        "денормализованное (4.9e-324)",
        "+inf",
        "-inf",
        "пользователь"
    };
    for (int i = 0; i < 8; i++) {
        printDoubleBits(doubles[i], doubleNames[i]);
    }

    cout << "\n=== Этап 5. Манипуляция битами: int\n";
    const BitOp ops[] = { BitOp::Set, BitOp::Clear, BitOp::Toggle };
    int x = 5;
    for (int n : { 1, 2 }) {
        cout << "\nx = " << x << ", бит #" << n << " сейчас = " << testBit(static_cast<unsigned int>(x), n) << '\n';
        for (BitOp op : ops) {
            cout << "  " << opName(op) << " : " << modifyBit(x, n, op) << '\n';
        }
    }

    //const BitOp ops[] = { BitOp::Set, BitOp::Clear, BitOp::Toggle }; аналогичная работа блока
    int usx;
    int usn;
    cout << "введите число для манипуляций с int - ";
    cin >> usx;
    cout << "номер бита - ";
    cin >> usn;
    for (int usn : { 1, 2 }) {
        cout << "\nx = " << usx << ", бит #" << usn << " сейчас = " << testBit(static_cast<unsigned int>(usx), usn) << '\n';
        for (BitOp op : ops) {
            cout << "  " << opName(op) << " : " << modifyBit(usx, usn, op) << '\n';
        }
    }
    

    cout << "\n=== Этап 5. Манипуляция битами: float и double\n";
    float f = 3.14f;
    printFloatBits(f, "исходное float 3.14");
    printFloatBits(modifyBit(f, 31, BitOp::Toggle), "инвертирован знак");
    printFloatBits(modifyBit(f, 23, BitOp::Set), "установлен бит младший бит порядка: x2");
    printFloatBits(modifyBit(f, 0, BitOp::Toggle), "инвертирован младший бит мантиссы");

    double d = 2.5;
    printDoubleBits(d, "исходное double 2.5");
    printDoubleBits(modifyBit(d, 63, BitOp::Toggle), "инвертирован знак");
    printDoubleBits(modifyBit(d, 50, BitOp::Clear), "сброшен бит 50");

        cout << "\n=== Этап 5. Манипуляция битами: float и double\n";
    float ff;
    cout << "Введите число для манипуляций с float - ";
    cin >> ff;
    printFloatBits(ff, "исходное float");
    printFloatBits(modifyBit(ff, 31, BitOp::Toggle), "инвертирован знак");
    printFloatBits(modifyBit(ff, 23, BitOp::Set), "установлен бит младший бит порядка: x2");
    printFloatBits(modifyBit(ff, 0, BitOp::Toggle), "инвертирован младший бит мантиссы");

    double fff;
    cout << "Введите число для манипуляций с double - ";
    cin >> fff;
    printDoubleBits(fff, "исходное double 2.5");
    printDoubleBits(modifyBit(fff, 63, BitOp::Toggle), "инвертирован знак");
    printDoubleBits(modifyBit(fff, 50, BitOp::Clear), "сброшен бит 50");

    cout << "\n=== Этап 6. Индивидуальное задание: сделать число нечётным\n";
    runIndividualTask();

    cout << endl;
    return 0;
}
