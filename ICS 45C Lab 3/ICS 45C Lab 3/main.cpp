#include "HashMap.hpp"
#include <iostream>

int main()
{
	HashMap Test;
	Test.add("Ford", "Tang");
	Test.deleteBucket();
	std::cout << Test.size() << std::endl;
	
	
	return 0;
}