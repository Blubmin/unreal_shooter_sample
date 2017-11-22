#include <Test.h>

#include <iostream>

//#include <glog/logging.h>

namespace thesis {

	int TestClassForUnrealToLinkTo::DoTheThing(int a, int b) {
		//LOG(INFO) << "Test" << std::endl;
		return a + b;
	}
}