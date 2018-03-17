#include <iostream>
#include <sstream>
#include <stdexcept>
#include <set>
#include <vector> 
#include <map>
#include <c++/5/functional>

#include "rational.h"

using namespace std;

/*
 * Variables.
 */
struct Errors {
public:
    int GetError() const {
        return error;
    }
    int GetGlobalError() const {
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

// Initialize TestError object.
Errors TestErrors;


/* 
 * Print result when, group tests completed. Print `Done!` if tests are success.
 * Otherwise print number of errors.
 * 
 * Called in every test.
 */
void PrintResultTest() {
    if (TestErrors.GetError() == 0) {
        cout << "Done!\n";
    } else {
        string error = "Test failed! Please checks your tests and "
                "fix any errors.\n";
        
        cout << error << "\n";
    }
}

/* 
 * Print global result when, all group tests completed. 
 * Print `All test are success!` if all tests are success.
 * Otherwise print number of errors and throw runtime_error.
 * 
 * Called, when all group tests are completed.
 */
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
 * Print error to stderr in the format:
 * `In file: ` - file, in which error exists.
 * `At line: ` - line, in wich error exists.
 * `Function ` - testing function.
 * `Expression: ` - error cause.
 */
void PrintError(const string& file, const int& line, 
        const string& func, const ostringstream& stream) 
{
    cerr << string(50, '*') << "\n";
    cerr << "Assertion failed!" << "\n\n";
    cerr << "In file: " << file << "." << "\n";
    cerr << "At line: " << line << "." << "\n\n";
    cerr << "Function " << '`' << func << '`' << " failed!" << "\n";
    cerr << "Expression: " << stream.str() << "\n\n";
    cerr << string(50, '*') << "\n";
}

/*
 * Run all group tests. Catch `runtime_error`, if error exists.
 * Print test result and update global errors. 
 */
void RunTests(const vector<function<void()>> functions) {
    function<void()> f;
    for (size_t i = 0; i < functions.size(); i++) {
        TestErrors.ResetError();
        cout << "The test №" << i + 1 <<  " has begin.\n";
        f = functions[i];
        try {
            f();
            TestErrors.UpdateGlobalError();
            PrintResultTest();
        } catch (runtime_error& e) {
            TestErrors.UpdateGlobalError();
            PrintResultTest();
            continue;
        } 
    } 
}


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
        ostringstream os;
        os << lhs << " != " << rhs;
        PrintError(file, line, "AssertEqual", os);
        throw runtime_error("");
    } 
}
/* 
 * Macro for `AssertEqual` function.
 * 
 * Call func with parameters:
 * `lhs` - left rational.
 * `rhs` - right rational.
 */
#define AssertEqual(lhs, rhs) _AssertEqual(lhs, rhs, __LINE__, __FILE__)


void _AssertNotEqual(const rational& lhs, const rational& rhs, 
        int line, const string& file) 
{
    if (lhs == rhs) {
        TestErrors.UpdateError();
        ostringstream os;
        os << lhs << " == " << rhs;
        PrintError(file, line, "AssertNotEqual", os);
        throw runtime_error("");
    } 
}
/* 
 * Macro for `AssertNotEqual` function.
 * 
 * Call func with parameters:
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
        ostringstream os;
        os << lhs << " != " << output.str();
        PrintError(file, line, "AssertOutputEqual", os);
        throw runtime_error("");
    } 
}
/* 
 * Macro for `AssertOutputEqual` function.
 * 
 * Call func with parameters:
 * `lhs` - left rational.
 * `stream` - string stream.
 */
#define AssertOutputEqual(lhs, stream) _AssertOutputEqual(lhs, stream, __LINE__, __FILE__)


void _AssertFalse(bool check, int line, const string& file) {
    if (check) {
        TestErrors.UpdateError();
        ostringstream os;
        os << boolalpha << check << " != false ";
        PrintError(file, line, "AssertFalse", os);
        throw runtime_error("");
    }
}
/* 
 * Macro for `AssertFalse` function.
 * 
 * Call func with parameters:
 * `check` - true or false.
 */
#define AssertFalse(check) _AssertFalse(check, __LINE__, __FILE__)


void _AssertTrue(bool check, int line, const string& file) {
    if (!check) {
        TestErrors.UpdateError();
        ostringstream os;
        os << boolalpha << check << " != true ";
        PrintError(file, line, "AssertTrue", os);
        throw runtime_error("");
    }
}
/* 
 * Macro for `AssertTrue` function.
 * 
 * Call func with parameters:
 * `check` - true or false.
 */
#define AssertTrue(check) _AssertTrue(check, __LINE__, __FILE__)

template<typename type>
void _AssertContainerEqual(const type& lhs, 
        const type& rhs, int line, const string& file) 
{
    if (lhs != rhs) {
        TestErrors.UpdateError();
        ostringstream os;
        os << "vectors are not equal";
        PrintError(file, line, "AssertContainerEqual", os);
        throw runtime_error("");
    } 
}
/* 
 * Macro for `AssertContainerEqual` function.
 * 
 * Call func with parameters:
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
        ostringstream os;
        os << "vectors are equal";
        PrintError(file, line, "AssertContainerNotEqual", os);
        throw runtime_error("");
    } 
}
/* 
 * Macro for `AssertContainerNotEqual` function.
 * 
 * Call func with parameters:
 * `lhs` - left container rational.
 * `rhs` - right container rational.
 */
#define AssertContainerNotEqual(lhs, rhs) _AssertContainerNotEqual(lhs, rhs, __LINE__, __FILE__)



/* 
 * Test function, check equality of class rational.
 */
void TestEqual() {
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
}

/* 
 * Test function. Check `if (rational == true)` or `if (!rational)`. 
 */
void TestTrueOrFalse() {
    {
        const rational r{};
        AssertFalse(!r);
    }
    
    {
        const rational r(-2 ,1);
        bool a = r ? true : false;
        AssertTrue(a);
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
}

/* 
 * Test function. Compare two rational clases.
 */
void TestComparsion() {
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
}

/* 
 * Test function, check operators for class rational.
 * Operators: `+`, `-`, `*`, `/`.
 */
void TestOperators() {
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
}

/* 
 * Test function, check operators for class rational.
 * Operators: `+=`, `-=`, `*=`, `/=`.
 */
void TestOperatorsTwo() {
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
}

/* 
 * Test function. Check, how class rational printed.
 * Also, check, set class rational update from input.
 */
void TestIOSTREAM() {
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
}

/* 
 * Test function, check containers with class rational.
 * Containers: `vector<rational>`, `set<rational>`.
 */
void TestContainer() {
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
}

/* 
 * Test function, check containers with class rational.
 * Containers: `map<rational, ...>`, `map<..., rational>`.
 */
void TestMap() {
    {
        map<rational, int> count;
        rational number = {0, 1};
        ++count[number];
        ++count[{1, 2}];
        ++count[{2, 3}];
        ++count[{2, 3}];
        if (count.size() != 3) {
            ostringstream os;
            os << "map<rational, ...> not work";
            PrintError(__FILE__, __LINE__, "TestMap", os);
        }
    }
}

/* 
 * 
 */
void TestCatchError() {
    {
        try {
            rational a(1, 0);
            ostringstream os;
            os << "do not catch logic_error!";
            PrintError(__FILE__, __LINE__, "TestCatchError", os);
        } 
        catch (logic_error const& err) {
            rational a(1, 1);
            AssertEqual(a, rational(1, 1));
        }
    }
}
/* 
 * Function run all defauls tests for class rational.
 */
void RunDefaultTests() {
    vector<function<void()>> funcs = {
        TestEqual, TestTrueOrFalse, TestComparsion, TestOperators, 
        TestOperatorsTwo, TestIOSTREAM, TestContainer, TestMap, TestCatchError,
    };
    RunTests(funcs);
    PrintGlobalResultTest();
} 
