#ifndef UNIT_TEST_H
#define UNIT_TEST_H

#include <iostream>

#define assertEqual(a, b, non_equal_message) do { if ((a) != (b)) { std::cerr << "TestFail(" << #a << " == " << #b << ") : (" << __FILE__ << " : " << __LINE__ << ")\n    Golden:\n"\
    << (a) << "\n    Output:\n" << (b) << "\n    Message: " << non_equal_message << "\n"; }} while(0)

#define assertNonEqual(a, b, equal_message) do { if ((a) == (b)) { std::cerr << "TestFail(" << #a << " == " << #b << ") : ("  << __FILE__ << " : " << __LINE__ << ")\n: "\
        << "\n    Output:\n" << (b) << "\n    Message: " << equal_message << "\n"; }} while(0)

#define intendedFail(a, b, fail_message) do { if ((a) != (b)) { std::cerr << "Intended fail(" << #a << " == " << #b << ") : ("   << __FILE__ << " : " << __LINE__ << ")\n    Reference:\n"\
    << (a) << "\n    Output:\n" << (b) << "\n    Message: " << fail_message << "\n"; }} while(0)

#endif // UNIT_TEST_H
