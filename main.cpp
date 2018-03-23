#include <iostream>

#include "UnitTestDriver.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    UnitTestDriver driver1 = UnitTestDriver();
    driver1.testQueue();
    driver1.testCircularCharQueue();

    return 0;
}