// CreateSecFile.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "windows.h"


int _tmain(int argc, _TCHAR* argv[])
{
	DWORD sidLength = 0;
	DWORD sidLengthDomain = 0;
	SID_NAME_USE sidType;
	LookupAccountName(NULL, L"Flenov", NULL, &sidLength, NULL, &sidLengthDomain, &sidType);

	PSID sidValue = (PSID)new BYTE[sidLength];
	LPTSTR wszDomainName = new WCHAR[sidLengthDomain];

	if (!LookupAccountName(NULL, L"Flenov", sidValue, &sidLength, wszDomainName, &sidLengthDomain, &sidType))
	{
		printf("Account do not found");
		return 0;
	}
	
	printf("User Flenov has found\n");

	SECURITY_DESCRIPTOR securityDescriptor;
	InitializeSecurityDescriptor(&securityDescriptor, SECURITY_DESCRIPTOR_REVISION);
	SetSecurityDescriptorOwner(&securityDescriptor, sidValue, true);
	SetSecurityDescriptorGroup(&securityDescriptor, NULL, true);

	SECURITY_ATTRIBUTES securityAttributes;
	securityAttributes.nLength = sizeof(SECURITY_ATTRIBUTES);
	securityAttributes.lpSecurityDescriptor = &securityDescriptor;
	securityAttributes.bInheritHandle = false;
	

	HANDLE h = CreateFile(L"c:\\Temp\\test.txt", GENERIC_ALL, 0, &securityAttributes,
		CREATE_ALWAYS, FILE_FLAG_BACKUP_SEMANTICS, 0);

	if (h == INVALID_HANDLE_VALUE)
	{
		printf("Can't create file");
		return 0;
	}

	printf("File has just creared\n");
	CloseHandle(h);

	return 0;
}

