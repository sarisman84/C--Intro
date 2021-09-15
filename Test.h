#pragma once

namespace TestinSpace
{
	class Test
	{
	public:
		enum class CalculationType
		{
			Addition,
			Multiplication,
			Division,
			Subtraction,
			Module
		};
		int CalculateCachedValues(CalculationType aCalculationType);
		Test(int anArg1, int anArg2);



	private:
		int myTest1;
		int myTest2;
	};




}


