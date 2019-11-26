// ConsoleSample.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

void OutInt(int iNumber);
int Factorial(int iNumber);
int Req(int iNumber);

int Factorial(int max)
{
	if (max>31) 
		return false;

	int sum=1;
	for (int i = 2; i<=max; i++)
	{
		sum = sum*i;
	}
	return sum;
}

int _tmain(int argc, _TCHAR* argv[])
{
	OutInt(10);

	printf("Factorial: ");
	int f = Factorial(34);
	if (f)
		OutInt(f);
	else
		printf("Too big param");

	printf("\n");
	OutInt(Req(1));
	return 0;
}

void OutInt(int iNumber)
{
	printf("%i\n", iNumber);
}

void OutInt(void)
{
	printf("Test");
}

int Req(int iNumber)
{
 if (iNumber<=5)
  return iNumber*Req(iNumber+1);
 else
  return 1;
}

