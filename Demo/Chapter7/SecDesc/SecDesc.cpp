// SecDesc.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Aclapi.h"


int _tmain(int argc, _TCHAR* argv[])
{
	PACL pDACL = NULL;
	PSECURITY_DESCRIPTOR pSD = NULL;

	// Get file security info
	if (GetNamedSecurityInfo(L"C:\\\\Temp\\test.txt", SE_FILE_OBJECT,
		DACL_SECURITY_INFORMATION, NULL, NULL, &pDACL, NULL,
		&pSD) != ERROR_SUCCESS) 
	{
		printf("Get security information error");
		return 0;
	}

	if (pDACL == NULL)
	{
		printf("ACL list is empty");
		return 0;
	}

	ACL_SIZE_INFORMATION aclInfo;
	if (!GetAclInformation(pDACL, &aclInfo, sizeof(aclInfo), 
		AclSizeInformation))
	{
		printf("Can't get ACL info");
		return 0;
	}


	SID_NAME_USE sid_nu;
	DWORD len = 200;
	for (DWORD i = 0; i < aclInfo.AceCount; i++)
	{
		LPWSTR user = new WCHAR[200];
		LPWSTR domain = new WCHAR[200];
		void *ace;
		if (GetAce(pDACL, i, &ace))
		{
			SID *SidStart = (SID *) &((ACCESS_ALLOWED_ACE *) ace)->SidStart;

			if (LookupAccountSid(NULL, SidStart, user, &len,
				domain, &len, &sid_nu))
			{
				wprintf(L"Account: %ws ", user);
			}
			if (((ACCESS_ALLOWED_ACE *) ace)->Header.AceType == ACCESS_ALLOWED_ACE_TYPE)
				printf(" Allow ");
			else
				printf(" Deny ");

			if (((ACCESS_ALLOWED_ACE *) ace)->Mask & 1)
				printf(" Read ");
			if (((ACCESS_ALLOWED_ACE *) ace)->Mask & 2)
				printf(" Write ");
			if (((ACCESS_ALLOWED_ACE *) ace)->Mask & 4)
				printf(" Execute ");
			printf(" \n");
		}
		delete [] user;
		delete [] domain;
	}

	return 0;
}

