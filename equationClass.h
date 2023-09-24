#pragma once
#include <string>

struct rootStruct
{
	int rootCount;
	double firstRoot, secondRoot;
};

struct coeffStruct
{
	double squareXCoeff = 0;
	double regXCoeff = 0;
	double constantCoeff = 0;

	bool failureFlag = 0;
};
