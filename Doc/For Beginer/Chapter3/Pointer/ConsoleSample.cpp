// ConsoleSample.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

bool Factorial(int *max)
{
	if (*max>31) 
		return false;
	if (*max<0)
		return false;

	int sum=1;
	for (int i = 2; i<=*max; i++)
	{
		sum = sum*i;
	}
	*max=sum;
	return true;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int b=10, i=10;
	int * pi=&i;

    printf("i value: %i\n Pointer to %i\n", *pi, pi);

	int f=5;
	if (Factorial(&f))
		printf("Factorial: %i\n", f);
	else
		printf("Error");

	return 0;
}
