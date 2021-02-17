#define UNUSED(expr) (void)(expr) //clang-tidy

#include <iostream>

#include "Animal.hpp"

int main(int argc, char **argv)
{
    UNUSED(argc);
    UNUSED(argv);

    Animal animal("Falco");

    std::cout << "Hello World!" << std::endl;

    return 0;
}