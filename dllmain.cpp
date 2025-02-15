// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <windows.h>
#include <iostream>
#include <vector>
#include "MinHook.h"
#include "framework.h"

DWORD WINAPI Main(LPVOID) {
    AllocConsole();
    FILE* file;
    freopen_s(&file, "CONOUT$", "w+", stdout);
    SetConsoleTitleA("zvi is fatty");
    MH_Initialize();
    Sleep(5000);

    __int64 Base = __int64(GetModuleHandleW(0)); //maybe?

    //crash fix
    *reinterpret_cast<char*>(Base + 0xAEC475 + 0) = 0xE9;
    *reinterpret_cast<char*>(Base + 0xAEC475 + 1) = 0x39;
    *reinterpret_cast<char*>(Base + 0xAEC475 + 2) = 0x02;
    *reinterpret_cast<char*>(Base + 0xAEC475 + 3) = 0x00;
    *reinterpret_cast<char*>(Base + 0xAEC475 + 4) = 0x00;

    UKismetSystemLibrary::ExecuteConsoleCommand(UWorld::GetWorld(), L"open Athena_Terrain", nullptr);
    return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(0, 0, Main, 0, 0, 0);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

