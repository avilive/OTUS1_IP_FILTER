// ip_filter.cpp : Defines the entry point for the application.
//

#include "ip_filter.h"
#include "lib.h"
#include "build_number.h"
using namespace std;

int main()
{	
	cout << BUILD_NUMBER << endl;
	cout << "Hello CMake. " << endl;
	
	return 0;
}
