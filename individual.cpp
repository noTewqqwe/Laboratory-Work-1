#include "individual.h"
#include "bits.h"

#include <iostream>

using namespace std;

int makeOdd(int value) {
    value |= 1;
    return value;
}

static const char* parity(int value) {
    return testBit(static_cast<unsigned int>(value), 0) ? "нечёт" : "чёт";
}

void runIndividualTask() {
    const int tests[] = { 4, 7, 0, -4, -7 };
    cout << "Тестовые примеры:\n";
    for (int t : tests) {
        int r = makeOdd(t);
        cout << "  " << t << " -> " << r << "  (было " << parity(t) << ", стало " << parity(r) << ")\n";
    }

    int odv;
    cout << "\nВведите число, чтобы оно стало нечётным: ";
    if (!(cin >> odv)) {
        cout << "\nОшибка: нужно ввести целое число.\n";
        return;
    }

    int y = makeOdd(odv);
    cout << '\n' << odv << " -> " << y
         << "  было " << parity(odv) << ", стало " << parity(y) << '\n';
    printIntBits(odv, "до");
    printIntBits(y, "после");
}
