#include "lib.h"

#include <iostream>

int main(int, char**)
{
    std::cout << get_build_number()<< std::endl;
    std::cout << get_greeting() << std::endl;

    return 0;
}
