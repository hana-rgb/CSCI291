#include <iostream>
#include <iomanip> // for std::setprecision and std::setw
using namespace std;

// a) Function to print the number with specified field space and precision
void print_real(float number, int fieldspace, int precision) {
    cout << fixed << setw(fieldspace) << setprecision(precision) << number << endl;
}

// b) Template function to update scale
template <typename T>
void update_scale(T& m1, T& m2, T m3 = 10) {
    T original_m1 = m1; // Store original value of m1
    T original_m2 = m2; // Store original value of m2

    // Update m1 and m2 as specified
    m1 = (original_m1 + original_m2) * m3;
    m2 = (original_m1 - original_m2) * m3;
}

int main() {
    // Test part (a): print_real function
    float number = 123.456;
    int fieldspace = 10;
    int precision = 2;

    cout << "Output of print_real:" << endl;
    print_real(number, fieldspace, precision);

    // Test part (b): update_scale template function
    double a = 5.5, b = 2.2;

    cout << "Before calling update_scale:" << endl;
    cout << "a = " << a << ", b = " << b << endl;

    update_scale(a, b);

    cout << "After calling update_scale:" << endl;
    cout << "a = " << a << ", b = " << b << endl;

    return 0;
}
