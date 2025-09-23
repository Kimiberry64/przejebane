#include "przejebane.h"

BOOL
WINAPI
SetPrivilege(
	_In_ HANDLE	  hToken,
	_In_ PWSTR	  szPrivilege
)
{
	LUID luidPrivilege;
	TOKEN_PRIVILEGES tokenPrivileges;

	tokenPrivileges.PrivilegeCount = 1;
	tokenPrivileges.Privileges[ 0 ].Luid = luidPrivilege;
	tokenPrivileges.Privileges[ 0 ].Attributes = SE_PRIVILEGE_ENABLED;

	LookupPrivilegeValueW( NULL, szPrivilege, &luidPrivilege ) ;
	AdjustTokenPrivileges( hToken, FALSE, &tokenPrivileges, sizeof( TOKEN_PRIVILEGES ), ( PTOKEN_PRIVILEGES )NULL, ( PDWORD )NULL );
	return TRUE;
}