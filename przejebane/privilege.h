#pragma once
#include "przejebane.h"

BOOL
WINAPI
SetPrivilege(
	_In_ HANDLE	  hToken,
	_In_ PWSTR	  szPrivilege
);