#include <iostream>
#include <sstream>
#include <stdexcept>
#include <set>
#include <vector> 
#include <map>

#include "rational.h"

/*
 * Variables.
 */
struct Errors {
public:
    int GetError() {
        return error;
    }
    int GetGlobalError() {
        return global;
    }
    void ResetError() {
        error = 0;
    }
    void ResetGlobalError() {
        global = 0;
    }
    void UpdateError() {
        error += 1;
    }
    void UpdateGlobalError() {
        global += error;
    }
private:
    int error = 0;
    int global = 0;
};

Errors TestErrors;


using namespace std;

/* 
 * Declared unit-tests functions for rational. 
 * `_Assert...` - test funcitions.  
 *
 * In macros declared for functions, which declared below:
 * `__LINE__` - get line from the code, where the error exists.
 * `__FILE_` - get file, where the error exists.
 *
 */
void _AssertEqual(const rational& lhs, const rational& rhs, 
        int line, const string& file) 
{
    if (lhs != rhs) {
        TestErrors.UpdateError();
        cout << string(50, '*') << "\n";
        cout << "Assertion failed!" << "\n\n";
        cout << "In file: " << file << "." << "\n";
        cout << "At line: " << line << "." << "\n\n";
        cout << "Function `AssertEqual` failed!" << "\n";
        cout << "Expression: " << lhs << " != " << rhs << "\n\n";
        cout << string(50, '*') << "\n";
    } 
}
/* 
 * Macro for `AssertEqual` function.
 * 
 * Call func with parametres:
 * `lhs` - left rational.
 * `rhs` - right rational.
 */
#define AssertEqual(lhs, rhs) _AssertEqual(lhs, rhs, __LINE__, __FILE__)


void _AssertNotEqual(const rational& lhs, const rational& rhs, 
        int line, const string& file) 
{
    if (lhs == rhs) {
        TestErrors.UpdateError();
        cout << string(50, '*') << "\n";
        cout << "Assertion failed!" << "\n\n";
        cout << "In file: " << file << "." << "\n";
        cout << "At line: " << line << "." << "\n\n";
        cout << "Function `AssertNotEqual` failed!" << "\n";
        cout << "Expression: " << lhs << " == " << rhs << "\n\n";
        cout << string(50, '*') << "\n";
    } 
}
/* 
 * Macro for `AssertNotEqual` function.
 * 
 * Call func with parametres:
 * `lhs` - left rational.
 * `rhs` - right rational.
 */
#define AssertNotEqual(lhs, rhs) _AssertNotEqual(lhs, rhs, __LINE__, __FILE__)


void _AssertOutputEqual(const rational& lhs, const string& stream, 
        int line, const string& file) 
{
    ostringstream output;
    output << lhs.numerator() << '/' << lhs.denominator();
    if (output.str() != stream) {
        TestErrors.UpdateError();
        cout << string(50, '*') << "\n";
        cout << "Assertion failed!" << "\n\n";
        cout << "In file: " << file << "." << "\n";
        cout << "At line: " << line << "." << "\n\n";
        cout << "Function `AssertOutputEqual` failed!" << "\n";
        cout << "Expression: " << lhs << " == " << output.str() << "\n\n";
        cout << string(50, '*') << "\n";
    } 
}
/* 
 * Macro for `AssertOutputEqual` function.
 * 
 * Call func with parametres:
 * `lhs` - left rational.
 * `stream` - string stream.
 */
#define AssertOutputEqual(lhs, stream) _AssertOutputEqual(lhs, stream, __LINE__, __FILE__)


void _AssertFalse(bool check, int line, const string& file) {
    if (check) {
        TestErrors.UpdateError();
        cout << string(50, '*') << "\n";
        cout << "Assertion failed!" << "\n\n";
        cout << "In file: " << file << "." << "\n";
        cout << "At line: " << line << "." << "\n\n";
        cout << "Function `AssertFalse` failed!" << "\n";
        cout << "Expression: " << boolalpha << check << " != false " << "\n\n";
        cout << string(50, '*') << "\n";
    }
}
/* 
 * Macro for `AssertEqual` function.
 * 
 * Call func with parametres:
 * `check` - true or false.
 */
#define AssertFalse(check) _AssertFalse(check, __LINE__, __FILE__)


void _AssertTrue(bool check, int line, const string& file) {
    if (!check) {
        TestErrors.UpdateError();
        cout << string(50, '*') << "\n";
        cout << "Assertion failed!" << "\n\n";
        cout << "In file: " << file << "." << "\n";
        cout << "At line: " << line << "." << "\n\n";
        cout << "Function `AssertTrue` failed!" << "\n";
        cout << "Expression: " << boolalpha << check << " != true " << "\n\n";
        cout << string(50, '*') << "\n";
    }
}
/* 
 * Macro for `AssertEqual` function.
 * 
 * Call func with parametres:
 * `check` - true or false.
 */
#define AssertTrue(check) _AssertTrue(check, __LINE__, __FILE__)

template<typename type>
void _AssertContainerEqual(const type& lhs, 
        const type& rhs, int line, const string& file) 
{
    if (lhs != rhs) {
        TestErrors.UpdateError();
        cout << string(50, '*') << "\n";
        cout << "Assertion failed!" << "\n\n";
        cout << "In file: " << file << "." << "\n";
        cout << "At line: " << line << "." << "\n\n";
        cout << "Function `AssertContainerEqual` failed!" << "\n";
        cout << "Expression: " << "vectors are not equal" << "\n\n";
        cout << string(50, '*') << "\n";
    } 
}
/* 
 * Macro for `AssertEqual` function.
 * 
 * Call func with parametres:
 * `lhs` - left container with rational.
 * `rhs` - right container with rational.
 */
#define AssertContainerEqual(lhs, rhs) _AssertContainerEqual(lhs, rhs, __LINE__, __FILE__)

template<typename type>
void _AssertContainerNotEqual(const type& lhs, 
        const type& rhs, int line, const string& file) 
{
    if (lhs == rhs) {
        TestErrors.UpdateError();
        cout << string(50, '*') << "\n";
        cout << "Assertion failed!" << "\n\n";
        cout << "In file: " << file << "." << "\n";
        cout << "At line: " << line << "." << "\n\n";
        cout << "Function `AssertContainerNotEqual` failed!" << "\n";
        cout << "Expression: " << "vectors are equal" << "\n\n";
        cout << string(50, '*') << "\n";
    } 
}
/* 
 * Macro for `AssertEqual` function.
 * 
 * Call func with parametres:
 * `lhs` - left container rational.
 * `rhs` - right container rational.
 */
#define AssertContainerNotEqual(lhs, rhs) _AssertContainerNotEqual(lhs, rhs, __LINE__, __FILE__)


void PrintResultTest() {
    if (TestErrors.GetError() == 0) {
        cout << "Done!\n";
    } else {
        cout << "You have " << to_string(TestErrors.GetError()) << " errors!" 
                << " Please checks you tests and fix any errors.\n";
    }
}

void PrintGlobalResultTest() {
    if (TestErrors.GetGlobalError() == 0) {
        cout << "All tests are success!";
        TestErrors.ResetGlobalError();
        TestErrors.ResetError();
    } else {
        string error = "You have " + to_string(TestErrors.GetGlobalError()) +
                " global errors! Please checks you tests and fix any errors.";
        TestErrors.ResetGlobalError();
        TestErrors.ResetError();
        throw runtime_error(error);
    }
}



/* 
 * Test function, check equality of class rational.
 */
void TestEqual() {
    TestErrors.ResetError();
    cout << "The test №1 has begin.\n";
    {
        const rational r(3, 10);
        AssertEqual(r, rational(3, 10));
    }

    {
        const rational r(8, 12);
        AssertEqual(r, rational(2, 3));
    }

    {
        const rational r(-4, 6);
        AssertEqual(r, rational(-2, 3));
    }

    {
        const rational r(4, -6);
        AssertEqual(r, rational(-2, 3));
    }
    TestErrors.UpdateGlobalError();
    PrintResultTest();
}

/* 
 * Test function. Check `if (rational == true)` or `if (!rational)`. 
 */
void TestTrueOrFalse() {
    TestErrors.ResetError();
    cout << "The test №2 has begin.\n";
    {
        const rational r();
        AssertFalse(!r);
    }

    {
        const rational r(1, 15);
        bool a = r ? true : false;
        AssertTrue(a);
    }

    {
        const rational r;
        AssertFalse(!r);
    }
    
    {
        const rational r(14, 15);
        bool a = r ? true : false;
        AssertTrue(a);
    }
    
    {
        const rational r(0, 1);
        AssertFalse(!r);
    }
    
    {
        const rational r(0, 15);
        AssertFalse(!r);
    }
    TestErrors.UpdateGlobalError();
    PrintResultTest();
}

/* 
 * Test function. Compare two rational clases.
 */
void TestComparsion() {
    TestErrors.ResetError();
    cout << "The test №3 has begin.\n";
    {
        rational r1(4, 6);
        rational r2(2, 5);
        AssertTrue(r1 > r2);
    }
    
    {
        rational r1(2, 5);
        rational r2(4, 6);
        AssertTrue(r1 < r2);
    }
    
    {
        rational r1(4, 6);
        rational r2(2, 3);
        AssertTrue(r1 == r2);
    }
    
    {
        rational r1(4, 6);
        rational r2(2, 5);
        AssertFalse(r1 == r2);
    }
    
    {
        rational r1(0, 1);
        AssertFalse(!r1);
    }
    TestErrors.UpdateGlobalError();
    PrintResultTest();
}

/* 
 * Test function, check operators for class rational.
 * Operators: `+`, `-`, `*`, `/`.
 */
void TestOperators() {
    TestErrors.ResetError();
    cout << "The test №4 has begin.\n";
    {
        rational a(2, 3);
        rational b(4, 3);
        rational c(2, 1);
        AssertEqual(a + b, c);
    }
    
    {
        rational a(5, 7);
        rational b(2, 9);
        rational c(31, 63);
        AssertEqual(a - b, c);
    }
    
    {
        rational a(2, 3);
        rational b(4, 3);
        rational c(8, 9);
        AssertEqual(a * b, c);
    }
    
    {
        rational a(5, 4);
        rational b(15, 8);
        rational c(2, 3);
        AssertEqual(a / b, c);
    }
    TestErrors.UpdateGlobalError();
    PrintResultTest();
}

/* 
 * Test function, check operators for class rational.
 * Operators: `+=`, `-=`, `*=`, `/=`.
 */
void TestOperatorsTwo() {
    TestErrors.ResetError();
    cout << "The test №5 has begin.\n";
    {
        rational a(2, 3);
        rational b(4, 3);
        a += b;
        AssertEqual(a, rational(2, 1));
    }
    
    {
        rational a(5, 7);
        rational b(2, 9);
        a -= b;
        AssertEqual(a, rational(31, 63));
    } 
    
    {
        rational a(2, 3);
        rational b(4, 3);
        a *= b;
        AssertEqual(a, rational(8, 9));
    }
    
    {
        rational a(5, 4);
        rational b(15, 8);
        a /= b;
        AssertEqual(a, rational(2, 3));
    }
    TestErrors.UpdateGlobalError();
    PrintResultTest();
}

/* 
 * Test function. Check, how class rational printed.
 * Also, check, set class rational update from input.
 */
void TestIOSTREAM() {
    TestErrors.ResetError();
    cout << "The test №6 has begin.\n";
    {
        ostringstream output;
        rational a(-6, 8);
        output << a;
        AssertOutputEqual(a, "-3/4");
    }
    
    {
        ostringstream output;
        rational a(5, 7);
        output << a;
        AssertOutputEqual(a, "5/7");
    }

    {
        istringstream input("5/7");
        rational r;
        input >> r;
        AssertEqual(r, rational(5, 7));
    }

    {
        istringstream input("5/7 10/8");
        rational r1, r2;
        input >> r1 >> r2;
        AssertEqual(r1, rational(5, 7));
        AssertEqual(r2, rational(5, 4));
        
        
        input >> r1;
        input >> r2;
        AssertEqual(r1, rational(5, 7));
        AssertEqual(r2, rational(5, 4));
    }
    TestErrors.UpdateGlobalError();
    PrintResultTest();
}

/* 
 * Test function, check containers with class rational.
 * Containers: `vector<rational>`, `set<rational>`.
 */
void TestContainer() {
    TestErrors.ResetError();
    cout << "The test №7 has begin.\n";
    {
        const set<rational> rs = {{1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2}};
        const set<rational> ls = {{1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2}};
        AssertContainerEqual(rs, ls);
    }

    {
        const set<rational> rs = {{1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2}};
        const set<rational> ls = {{1, 3}, {1, 21}, {3, 4}, {9, 4}, {1, 2}};
        AssertContainerNotEqual(rs, ls);
    }
    TestErrors.UpdateGlobalError();
    PrintResultTest();
}

/* 
 * Test function, check containers with class rational.
 * Containers: `map<rational, ...>`, `map<..., rational>`.
 */
void TestMap() {
    TestErrors.ResetError();
    cout << "The test №8 has begin.\n";
    {
        map<rational, int> count;
        rational number = {0, 1};
        ++count[{1, 2}];
        ++count[{1, 2}];
        ++count[{2, 3}];
        if (count.size() != 2) {
            cout << string(50, '*') << "\n";
            cout << "Assertion failed!" << "\n\n";
            cout << "In file: " << __FILE__ << "." << "\n";
            cout << "At line: " << __LINE__ << "." << "\n\n";
            cout << "Function `TestMap` failed!" << "\n";
            cout << "Expression: " << "map<rational, ..> not work" << "\n\n";
        }
    }
    TestErrors.UpdateGlobalError();
    PrintResultTest();
}

/* 
 * Function run all defauls tests for class rational.
 */
void RunDefaultTests() {
    TestEqual();
    TestTrueOrFalse();
    TestComparsion();
    TestOperators();
    TestOperatorsTwo();
    TestIOSTREAM();
    TestContainer();
    TestMap();
    
    // try to catch logic error
    {
        TestErrors.ResetError();
        cout << "The test №9 has begin.\n";
        {
            try {
                rational a(1, 0);
                cout << string(50, '*') << "\n";
                cout << "Assertion failed!" << "\n\n";
                cout << "In file: " << __FILE__ << "." << "\n";
                cout << "At line: " << __LINE__ << "." << "\n\n";
                cout << "Expression: " << "do not catch logic_error!" << "\n\n";
            } 
            catch (logic_error const& err) {
                rational a(1, 1);
                bool equal = a == rational(1, 1);
                AssertEqual(a, rational(1, 1));
            }
        }
        TestErrors.UpdateGlobalError();
        PrintResultTest();
    }
    PrintGlobalResultTest();
} 
