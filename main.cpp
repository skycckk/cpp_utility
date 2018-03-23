#include <iostream>

#include "UnitTestDriver.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    UnitTestDriver driver1 = UnitTestDriver();
    driver1.testQueue();

    return 0;
}