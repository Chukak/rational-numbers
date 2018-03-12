#include "tests.h"


int main(int argc, char** argv) {
    // if test not success, exit with non-zero status.
    if (run_tests()) {
        return 1;
    }
    return 0;
}
