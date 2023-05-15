#include "truth_ptr.h"

#include <iostream>

int main()
{
	//revolutionary stuff
	truth_ptr<int> ptr(10);
	std::printf("ptr value -> %d", *ptr);

	return 0;
}