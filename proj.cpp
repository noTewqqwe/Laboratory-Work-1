#include <iostream>
#include <Windows.h>

using namespace std;

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(h, &mode);
    SetConsoleMode(h, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    cout << "bool : " << sizeof(bool) << endl;
    cout << "char : " << sizeof(char) << endl;
    cout << "short int : " << sizeof(short int) << endl;
    cout << "int : " << sizeof(int) << endl;
    cout << "long int : " << sizeof(long int) << endl;
    cout << "float : " << sizeof(float) << endl;
    cout << "double : " << sizeof(double) << endl;
    cout << "long double : " << sizeof(long double) << endl;

    //////////////////////////////////////////////////

    // int a;
    // int* p = &a;
    // cout << endl;
    // cin >> a;
    // cout << "a = " << a <<  "&a = " << &a;

    //cout << endl;
    int intv[4] = {5, -5, 0, 2147483647};
    const char* intNames[4] = {
        "положительное (5)",
        "отрицательное (-5)",
        "ноль (0)",
        "максимум int (2147483647)"
    };

    const short int OrderInt = sizeof(int) *8;
    unsigned mask = 1 << (OrderInt - 1);

    for (int k = 0; k < 4; k++) {
        int a = intv[k];

        cout << "\n[" << intNames[k] << "]  a = " << a << "  &a = " << &a << "\n";

        int fsign = -1;
        for (int i = 1; i < OrderInt; i++){
            if (a & (mask >> i)){
                fsign = i;
                break;
            }
        }

        cout << endl;
        for(int i = 0; i < OrderInt; i++){
            const char* color;
            if (i == 0){
                color = "\033[31m";
            }
            else if (fsign == -1 || i < fsign){
                color = "\033[90m";
            }
            else{
                color = "\033[32m";
            }
            if (a & mask >> i) {
                cout << color << '1' << "\033[0m";
            }
            else {
                cout << color << '0' << "\033[0m";
            }
            if (i == 0){
                cout << ' ';
            }
        }
    }
    /////////////////////////////////////
    cout << endl;
    union{
        float pi;
        int f_i;
    };
    float flv[6] = { 3.14f, -3.14f, 0.5f, 1.4e-45f, 0.0f, -0.0f };
    const char* flnames[6] = {
        "положительное (3.14)",
        "отрицательное (-3.14)",
        "точная степень 2 (0.5)",
        "денормализованное (1.4e-45)",
        "ноль (0.0)",
        "отрицательный ноль (-0.0)"
    };
    for (int k = 0; k < 6; k ++){
        pi = flv[k];

        cout << "\n[" << flnames[k] << "]  pi = " << pi << "  &pi = " << &pi<< "  f_i = " << f_i << "  &f_i = " << &f_i << "\n";
        cout << "  \033[31m знак\033[0m | \033[33m порядок \033[0m | \033[32m мантисса \033[0m\n  ";
        mask = 1 << (OrderInt - 1);
        for(int i = 0; i < OrderInt; i++){
            if (i == 0){
                cout << "\033[31m";
            }
            if (i == 1){
                cout << "\033[33m";
            }
            if (i == 9){
                cout << "\033[32m";
            }
            cout << ((f_i & mask >> i) ? '1' : '0');
            if (i == 0){  
                cout << "\033[0m";
            }
            if (i == 8){
                cout << "\033[0m";
            }
            if (i == 31){ 
                cout << "\033[0m";
            }

        }
    }
    cout << endl;
    //////////////////////////////////////
    union {
        double d;
        unsigned long long d_u;
    };
    unsigned long long dmask = 1ULL << 63;

    double dbv[5] = { 3.14, -3.14, 0.5, 4.9e-324, 0.0 };
    const char* dbn[5] = {
        "положительное (3.14)",
        "отрицательное (-3.14)",
        "точная степень 2 (0.5)",
        "денормализованное (4.9e-324)",
        "ноль (0.0)"
    };

    for (int k = 0; k < 5; k++) {
        d = dbv[k];

        cout << "\n[" << dbn[k] << "]  d = " << d << "  &d = " << &d << "  d_u = " << d_u << "\n";
        cout << "  \033[31m знак\033[0m | \033[33m порядок (11 бит) \033[0m | \033[32m мантисса (52 бита) \033[0m\n  ";

        for (int i = 0; i < 64; i++){
            if (i == 0)  {
                cout << "\033[31m";
            }
            if (i == 1)  {
                cout << "\033[33m";
            }
            if (i == 12){ 
                cout << "\033[32m";
            }
            cout << ((d_u & (dmask >> i)) ? '1' : '0');

            if (i == 0) { 
                cout << "\033[0m";
            }
            if (i == 11) {
                cout << "\033[0m";
            }
            if (i == 63) {
                cout << "\033[0m";
            }
        }
        cout << endl;
    }
    ///////////////////
    int x = 5;
    int n = 1;

    cout << "x = " << x << ", меняем бит #" << n << "\n";
    cout << "Установить в 1 (x | (1<<n))  : " << (x | (1 << n))  << "\n";
    cout << "Сбросить в 0   (x & ~(1<<n)) : " << (x & ~(1 << n)) << "\n";
    cout << "Инвертировать  (x ^ (1<<n))  : " << (x ^ (1 << n))  << "\n";
    cout << "Проверить бит  ((x>>n) & 1)  : " << ((x >> n) & 1)  << "\n";

    cout << endl;
    
    ////////////////////
    int odv;
    cout << "Введите число, чтобы оно стало нечётным ";
    cin >> odv;
    cout << endl;
    int y = odv | 1;
    cout << odv << " -> " << y 
    << "  было " << (odv % 2 == 0 ? "чёт" : "нечет")
    << ", стало " << (y % 2 == 0 ? "чёт" : "нечет");
}
// без uint32!!!