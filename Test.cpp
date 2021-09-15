#include "Test.h"




TestinSpace::Test::Test(int anArg1, int anArg2)
{
	myTest1 = anArg1;
	myTest2 = anArg2;
}

int TestinSpace::Test::CalculateCachedValues(CalculationType aCalculationType)
{
	switch (aCalculationType)
	{
	case Test::CalculationType::Addition:
		return myTest1 + myTest2;
	case Test::CalculationType::Multiplication:
		return myTest1 * myTest2;
	case Test::CalculationType::Division:
		return myTest1 / myTest2;
	case Test::CalculationType::Subtraction:
		return myTest1 - myTest2;
	case Test::CalculationType::Module:
		return myTest1 % myTest2;


	default:
		break;
	}

}



