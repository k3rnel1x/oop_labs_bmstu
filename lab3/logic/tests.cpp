#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <cmath>
#include "deixtralg.h"

using namespace std;

#define ASSERT_THROWS(expr, err_type, msg) \
    try { \
        expr; \
        assert(false && "Expected exception: " #msg); \
    } catch (const err_type& e) { \
        string what = e.what(); \
        assert(what.find(msg) != string::npos); \
    }

void test_numbers_and_dots() {
    cout << "Testing: Numbers and Decimal Dots..." << endl;

    // Корректные дробные числа
    assert(calcInPostfix(toPostfix("2.5+2.5")) == 5.0);
    assert(calcInPostfix(toPostfix("0.1*10")) == 1.0);

    ASSERT_THROWS(toPostfix(".5 + 1"), runtime_error, "invalid number")
    ASSERT_THROWS(toPostfix("5. + 1"), runtime_error, "invalid number");
    ASSERT_THROWS(toPostfix("5.5.5 + 1"), runtime_error, "invalid number"); 
}

void test_overflow_logic() {
    cout << "Testing: Overflow Detection..." << endl;

    string large_add = "1.7e308 + 1.7e308";
    ASSERT_THROWS(calcInPostfix(toPostfix(large_add)), runtime_error, "number overflow");

    string large_mul = "1e308 * 2";
    ASSERT_THROWS(calcInPostfix(toPostfix(large_mul)), runtime_error, "number overflow");

    ASSERT_THROWS(calcInPostfix(toPostfix("10^1000")), runtime_error, "number overflow");

    ASSERT_THROWS(calcInPostfix("1e1000"), runtime_error, "huge value");
}

void test_math_errors() {
    cout << "Testing: Math Errors..." << endl;

    ASSERT_THROWS(calcInPostfix(toPostfix("10 / 0")), runtime_error, "zero dividing");
    ASSERT_THROWS(calcInPostfix(toPostfix("10 / (5-5)")), runtime_error, "zero dividing");
}

void test_complex_expressions() {
    cout << "Testing: Complex Expressions..." << endl;

    assert(calcInPostfix(toPostfix("-(2+2)*-3")) == 12.0);
    
    assert(calcInPostfix(toPostfix("2*3^2")) == 18.0); 

    assert(calcInPostfix(toPostfix("((1+1)*2)^3")) == 64.0);
}


int main() {
    try {
        test_numbers_and_dots();
        test_overflow_logic();
        test_math_errors();
        test_complex_expressions();
        
        cout << "ALL TESTS PASSED SUCCESSFULLY" << endl;

    } catch (const exception& e) {
        cout << "\n!!! TEST FAILED: " << e.what() << endl;
    }
    return 0;
}