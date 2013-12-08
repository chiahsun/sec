#ifndef UNIT_TEST_H
#define UNIT_TEST_H

#include <iostream>

#define assertEqual(a, b, non_equal_message) do { if ((a) != (b)) { std::cerr << "TestFail : (" << __FILE__ << " : " << __LINE__ << ")\nGolden: "\
    << (a) << "\nOutput: " << (b) << "\nMessage: " << non_equal_message << "\n"; }} while(0)

#endif // UNIT_TEST_H
