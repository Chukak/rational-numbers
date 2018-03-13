#include <iostream>
#include <sstream>
#include <stdexcept>
#include <set>
#include <vector> 
#include <map>

#include "rational.h"

using namespace std;

/*
 * Testing the class rational number.
 *
 * Various tests are run, checks the possibility of using
 * operators that are implemented in the class rational numbers.
 *
 * The function returns 0 if all tests passed successfully. Otherwise
 * prints the result, which the test should return,
 * and returns `N`, where `N > 0`.
 *
 * For each successfully passed tests group, the function prints "OK".
 * Otherwise prints the result, which should return the test and
 * exit with a non-zero status.
 */
int run_tests() {
    {
        const rational r(3, 10);
        if (r.numerator() != 3 || r.denominator() != 10) {
            cout << "rational(3, 10) != 3/10" << "\n";
            return 1;
        }
    }

    {
        const rational r(8, 12);
        if (r.numerator() != 2 || r.denominator() != 3) {
            cout << "rational(8, 12) != 2/3" << "\n";
            return 2;
        }
    }

    {
        const rational r(-4, 6);
        if (r.numerator() != -2 || r.denominator() != 3) {
            cout << "rational(-4, 6) != -2/3" << "\n";
            return 3;
        }
    }

    {
        const rational r(4, -6);
        if (r.numerator() != -2 || r.denominator() != 3) {
            cout << "rational(4, -6) != -2/3" << "\n";
            return 4;
        }
    }
    
    {
        const rational r();
        if (!r) {
            cout << "rational() not is 0" << "\n";
            return 5;
        }
    }

    {
        const rational r(0, 15);
        if (r.numerator() != 0 || r.denominator() != 1) {
            cout << "rational(0, 15) != 0/1" << "\n";
            return 6;
        }
    }

    {
        const rational defaultConstructed;
        if (defaultConstructed.numerator() != 0 || 
                defaultConstructed.denominator() != 1) {
            cout << "rational() != 0/1" << "\n";
            return 7;
        }
    }

    cout << "OK" << "\n";
    // Comparsion tests.
    {
        rational r1(4, 6);
        rational r2(2, 5);
        bool equal = r1 > r2;
        if (!equal) {
            cout << "4/6 > 2/5" << "\n";
            return 1;
        }
    }
    
    {
        rational r1(2, 5);
        rational r2(4, 6);
        bool equal = r1 < r2;
        if (!equal) {
            cout << "4/6 > 2/5" << "\n";
            return 2;
        }
    }
    
    {
        rational r1(4, 6);
        rational r2(2, 3);
        bool equal = r1 == r2;
        if (!equal) {
            cout << "4/6 != 2/3" << "\n";
            return 3;
        }
    }
    
    {
        rational r1(4, 6);
        rational r2(2, 5);
        bool equal = r1 != r2;
        if (!equal) {
            cout << "4/6 == 2/5" << "\n";
            return 4;
        }
    }
    
    {
        rational r1(0, 1);
        if (!r1) {
            cout << "rational 0/1 is 0" << "\n";
            return 5;
        }
    }
    
    cout << "OK" << "\n";
    /* 
     * Operator tests.
     * Operators: `a + b`, `a - b`, `a * b`, `a / b`.
     */
    {
        rational a(2, 3);
        rational b(4, 3);
        rational c = a + b;
        bool equal = c == rational(2, 1);
        if (!equal) {
            cout << "2/3 + 4/3 != 2" << "\n";
            return 1;
        }
    }
    
    {
        rational a(5, 7);
        rational b(2, 9);
        rational c = a - b;
        bool equal = c == rational(31, 63);
        if (!equal) {
            cout << "5/7 - 2/9 != 31/63" << "\n";
            return 2;
        }
    }
    
    {
        rational a(2, 3);
        rational b(4, 3);
        rational c = a * b;
        bool equal = c == rational(8, 9);
        if (!equal) {
            cout << "2/3 * 4/3 != 8/9" << "\n";
            return 3;
        }
    }
    
    {
        rational a(5, 4);
        rational b(15, 8);
        rational c = a / b;
        bool equal = c == rational(2, 3);
        if (!equal) {
            cout << "5/4 / 15/8 != 2/3" << "\n";
            return 4;
        }
    }
    
    cout << "OK" << "\n";
    /* 
     * One more operator tests.
     * Operators: `a += b`, `a -= b`, `a *= b`, `a /= b`.
     */
    {
        rational a(2, 3);
        rational b(4, 3);
        a += b;
        bool equal = a == rational(2, 1);
        if (!equal) {
            cout << "2/3 + 4/3 != 2" << "\n";
            return 1;
        }
    }
    
    {
        rational a(5, 7);
        rational b(2, 9);
        a -= b;
        bool equal = a == rational(31, 63);
        if (!equal) {
            cout << "5/7 - 2/9 != 31/63" << "\n";
            return 2;
        }
    } 
    
    {
        rational a(2, 3);
        rational b(4, 3);
        a *= b;
        bool equal = a == rational(8, 9);
        if (!equal) {
            cout << "2/3 * 4/3 != 8/9" << "\n";
            return 3;
        }
    }
    
    {
        rational a(5, 4);
        rational b(15, 8);
        a /= b;
        bool equal = a == rational(2, 3);
        if (!equal) {
            cout << "5/4 / 15/8 != 2/3" << "\n";
            return 4;
        }
    }

    cout << "OK" << "\n";
    /* 
     * Input/output tests. 
     * Tests creation rational object from input: `cin >> rational`.
     * And tests output rational object: `cout << rational`.
     */
    {
        ostringstream output;
        output << rational(-6, 8);
        if (output.str() != "-3/4") {
            cout << "rational(-6, 8) should be written as \"-3/4\"" << "\n";
            return 1;
        }
    }

    {
        istringstream input("5/7");
        rational r;
        input >> r;
        bool equal = r == rational(5, 7);
        if (!equal) {
            cout << "5/7 is incorrectly read as " << r << "\n";
            return 2;
        }
    }

    {
        istringstream input("5/7 10/8");
        rational r1, r2;
        input >> r1 >> r2;
        bool correct = r1 == rational(5, 7) && r2 == rational(5, 4);
        if (!correct) {
            cout << "Multiple values are read incorrectly: " << r1 
                    << " " << r2 << "\n";
            return 3;
        }

        input >> r1;
        input >> r2;
        correct = r1 == rational(5, 7) && r2 == rational(5, 4);
        if (!correct) {
            cout << "Read from empty stream shouldn't change arguments: " 
                    << r1 << " " << r2 << "\n";
            return 4;
        }
    }

    cout << "OK" << "\n";
    // Map/set/vector creation tests.
    {
        const set<rational> rs = {{1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2}};
        if (rs.size() != 3) {
            cout << "Wrong amount of items in the set" << "\n";
            return 1;
        }

        vector<rational> v;
        for (auto x : rs) {
            v.push_back(x);
        }
        if (v != vector<rational>{{1, 25}, {1, 2}, {3, 4}}) {
            cout << "rationals comparison works incorrectly" << "\n";
            return 2;
        }
    }
    
    {
        map<rational, int> count;
        rational number = {0, 1};
        ++count[{1, 2}];
        ++count[{1, 2}];

        ++count[{2, 3}];

        if (count.size() != 2) {
            cout << "Wrong amount of items in the map" << "\n";
            return 3;
        }
    } 

    cout << "OK" << "\n";
    /* 
     * Denominator test. If denominator is zero, raise logic_error.
     * Example: `1/0` - will catch a error.
     */
    {
        try {
            rational a(1, 0);
            return 1;
        } 
        catch (logic_error const& err) {
            rational a(1, 1);
            bool equal = a == rational(1, 1);
            if (!equal) {
                cout << "1/1 != 1/1" << "\n";
                return 2;
            }
        }    
        
    }
    
    cout << "OK" << "\n";
    return 0;
} 
