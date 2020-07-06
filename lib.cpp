#include "lib.h"

#include "version.h"
#include <string>
#include "build_number.h"
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
	return "Hello, World!";
}