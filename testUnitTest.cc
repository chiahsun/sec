#include "UnitTest.h"

void testBool() {
    assertEqual(true, true, "true == true");
    intendedFail(true, false, "This should print this message since true != false");
}

int main() {
    testBool();
    return 0;
}
