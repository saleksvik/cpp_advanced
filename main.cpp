#include <iostream>
#include "lib_helloworld.h"

int main(int argc, const char* argv[])
{
    std::cout << "Hello, World!" << std::endl;
    std::cout << "Version " << version() << std::endl;

    return 0;
}