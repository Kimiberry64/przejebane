#include "przejebane.h"

BOOL
WINAPI
TakeOwnership(
	_In_ PWSTR szOwnFile
)
{
	BOOL bRetval = FALSE;
	HANDLE hToken = NULL;

	PACL pAcl = NULL;
	PSID pSidAdmin = NULL;
	PSID pSidEverybody = NULL;

	EXPLICIT_ACCESS explicitAccess[ NUMERAL_ACES ] = { 0 };
	SID_IDENTIFIER_AUTHORITY sidAuthWorld = SECURITY_WORLD_SID_AUTHORITY;
	SID_IDENTIFIER_AUTHORITY sidAuthorityNT = SECURITY_NT_AUTHORITY;

	AllocateAndInitializeSid( &sidAuthWorld, 1, SECURITY_WORLD_RID, NULL, 0, 0, NULL, 0, NULL, 0, &pSidEverybody );
	AllocateAndInitializeSid( &sidAuthorityNT, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS, 0, 0, NULL, 0, NULL, 0, &pSidAdmin );

	explicitAccess[ 0 ].grfAccessPermissions = GENERIC_ALL;
	explicitAccess[ 0 ].grfAccessMode = SET_ACCESS;
	explicitAccess[ 0 ].grfInheritance = NO_INHERITANCE;
	explicitAccess[ 0 ].Trustee.TrusteeForm = TRUSTEE_IS_SID;
	explicitAccess[ 0 ].Trustee.TrusteeType = TRUSTEE_IS_WELL_KNOWN_GROUP;
	explicitAccess[ 0 ].Trustee.ptstrName = ( PWSTR )pSidEverybody;

	explicitAccess[ 1 ].grfAccessPermissions = GENERIC_ALL;
	explicitAccess[ 1 ].grfAccessMode = SET_ACCESS;
	explicitAccess[ 1 ].grfInheritance = NO_INHERITANCE;
	explicitAccess[ 1 ].Trustee.TrusteeForm = TRUSTEE_IS_SID;
	explicitAccess[ 1 ].Trustee.TrusteeType = TRUSTEE_IS_GROUP;
	explicitAccess[ 1 ].Trustee.ptstrName = ( PWSTR )pSidAdmin;

	SetEntriesInAclW( NUMERAL_ACES, explicitAccess, 0, &pAcl );
	DWORD dwRes1 = SetNamedSecurityInfoW( szOwnFile, SE_FILE_OBJECT, DACL_SECURITY_INFORMATION, 0, NULL, pAcl, NULL );

	if ( dwRes1 == ERROR_SUCCESS )
	{
		bRetval = TRUE;
		goto cleanup;
	}

	if ( dwRes1 != ERROR_ACCESS_DENIED )
	{
		goto cleanup;
	}

	OpenProcessToken( GetCurrentProcess( ), TOKEN_ADJUST_PRIVILEGES, &hToken );
	SetPrivilege( hToken, SE_TAKE_OWNERSHIP_NAME, TRUE );

	DWORD dwRes2 = SetNamedSecurityInfoW( szOwnFile, SE_FILE_OBJECT, DACL_SECURITY_INFORMATION, 0, NULL, pAcl, NULL );

	if ( dwRes2 == ERROR_SUCCESS )
	{
		bRetval = TRUE;
	}

cleanup:
	LocalFree( pAcl );
	FreeSid( pSidAdmin );
	FreeSid( pSidEverybody );
	CloseHandle( hToken );

	return bRetval;
}