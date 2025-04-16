#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>
#include <iostream>
#include "SDK.hpp"
#include "./libs/MinHook.h"
#pragma comment(lib,"./libs/minhook.lib")
using namespace std;
using namespace SDK;

#define CREATEHOOK(Address, Hook, Og) \
MH_CreateHook((void*)(Address), Hook, (void**)(Og));

void VirtualHook(void** VFT, int index, PVOID Hook, void** OG) {

    if (OG) {
        *OG = VFT[index];
    }

    DWORD Protect;
    VirtualProtect(VFT + index, 8, PAGE_EXECUTE_READWRITE, &Protect);
    VFT[index] = Hook;
    VirtualProtect(VFT + index, 8, Protect, &Protect);
}

inline AFortGameStateAthena* GetGameState() {
	return reinterpret_cast<AFortGameStateAthena*>(UWorld::GetWorld()->GameState);
}
