#include "lib.h"

#include "version.h"
#include "build_number.h"
#include <string>

int version()
{
    return PROJECT_VERSION_PATCH;
}
int get_build_number()
{
    return BUILD_NUMBER;
}
std::string get_greeting()
{

    return std::string("Hello, World!");
}