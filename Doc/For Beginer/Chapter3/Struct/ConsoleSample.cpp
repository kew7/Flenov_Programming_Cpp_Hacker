// ConsoleSample.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

typedef int integer;
typedef char filepath[40];

typedef struct tagAddress
{
      char first_name[255]; 
      char last_name[255]; 
      int age;
} Address, *pAddress;

struct addr
{
      char first_name[255]; 
      char last_name[255]; 
      int age;
};

int _tmain(int argc, _TCHAR* argv[])
{
	Address a;
	strcpy(a.first_name, "Michael");
	strcpy(a.last_name, "Flenov");
	a.age=30;
	printf(a.first_name);

	addr ta;
	ta.age=10;

	printf("\n");
	filepath f;
	strcpy(f, "Flenov1");
	printf(f);

	pAddress ad;
    ad=&a;

	return 0;
}

