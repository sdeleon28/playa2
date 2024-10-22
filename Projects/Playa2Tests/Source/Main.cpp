#include "UnitTest.h"

int main()
{
    thmstudio::UnitTestRunner runner;
    runner.setAssertOnFailure (false);
    runner.runAllTests();
    return 0;
}
