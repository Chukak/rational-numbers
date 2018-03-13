
/* 
 * The function returns the smallest common denominator for two 
 * rational numbers.
 * 
 */
int LeastCommonDenominator(int a, int b) {
    if (a < b) {
        int t = a;
        a = b;
        b = t;
    }
    // find common denominator. 
    for (int i = 2; a % b; i++) {
        a = a * i;
    }
    return a;
}

/*  
 * The function returns the greatest common divisor of two numbers.
 *
 * Euclid's algorithm for integers is used.
 */
int GreatestCommonDivisor(int p, int q) {
    while (q) {
        int t = p % q;
        p = q;
        q = t; 
    }
    return p;
}
