#define GOOGLE_TEST_MODULE test_version

#include "lib.h"
#include "gtest/gtest.h"
#include <string>

TEST(OutputMessageTest, WorldGreetingIsCorrect)
{
	std::string str1 = "Hello, World!";
	std::string str2 = get_greeting();
	EXPECT_TRUE(str1==str2);
}

int main(int argc, char* argv[])
{
	//testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
