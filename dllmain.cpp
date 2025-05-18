// dllmain.cpp : Defines the entry point for the DLL application.
#include <windows.h>
#include <iostream>
#include <vector>
#include "framework.h"
#include "hook.h"
#include "gamemode.h"
#include "player.h"

DWORD WINAPI Main(LPVOID) {
    AllocConsole();
    FILE* file;
    freopen_s(&file, "CONOUT$", "w+", stdout);
    SetConsoleTitleA("zvi is fatty");
    MH_Initialize();
    Sleep(5000);

    //crash fix
    *reinterpret_cast<char*>(ImageBase + 0xAEC475 + 0) = 0xE9;
    *reinterpret_cast<char*>(ImageBase + 0xAEC475 + 1) = 0x39;
    *reinterpret_cast<char*>(ImageBase + 0xAEC475 + 2) = 0x02;
    *reinterpret_cast<char*>(ImageBase + 0xAEC475 + 3) = 0x00;
    *reinterpret_cast<char*>(ImageBase + 0xAEC475 + 4) = 0x00;

    *(bool*)(ImageBase + 0x4DAD489) = false; // prob will work and maybe not
    *(bool*)(ImageBase + 0x4DAD48A) = true;

    CREATEHOOK(ImageBase + 0x824670, DispatchRequestHook, &DispatchRequest);

    CREATEHOOK(ImageBase + 0xE1A770, NoReserve, nullptr); //this offset may be wrong I believe

    CREATEHOOK(ImageBase + 0x216DEA0, KickPlayer, nullptr);

    CREATEHOOK(ImageBase + 0x568F20, CanActivateAbility, nullptr);

    CREATEHOOK(ImageBase + 0x2540030, UWorldGetNetMode, nullptr);

    CREATEHOOK(ImageBase + 0x24EB5D8, GetMaxTickRate, nullptr); // ida says the output might be wrong and I don't know what that means so yeah

    CREATEHOOK(ImageBase + 0x2299FF0, TickFlushHook, nullptr);

    CREATEHOOK(ImageBase + 0x25A0BE0, GM::ReadyToStartMatchHook, &GM::ReadyToStartMatch);
    CREATEHOOK(ImageBase + 0xA81410, GM::SpawnDefaultPawnForHook, nullptr);
    CREATEHOOK(ImageBase + 0x239C750, Player::GetPlayerViewPointHook, &Player::GetPlayerViewPoint);

    VirtualHook((void **)AFortPlayerControllerAthena::GetDefaultObj()->VTable, 0x104, Player::ServerAcknowlegePossessionHook, (void**)&Player::ServerAcknowlegePossession);
    VirtualHook((void**)AFortPlayerControllerAthena::GetDefaultObj()->VTable, 0x242, Player::ServerLoadingScreenDroppedHook, (void**)&Player::ServerLoadingScreenDropped);
    VirtualHook((void**)AFortPlayerControllerAthena::GetDefaultObj()->VTable, 0x240, Player::ServerReadyToStartMatchHook, (void**)&Player::ServerReadyToStartMatch);
    VirtualHook((void**)AFortPlayerControllerAthena::GetDefaultObj()->VTable, 0x23C, Player::ServerReturnToMainMenuHook, (void**)&Player::ServerReturnToMainMenu);
    VirtualHook((void**)AGameModeBase::GetDefaultObj()->VTable, 0xC7, GM::HandleStartingNewPlayerHook, (void**)&GM::HandleStartingNewPlayer);

    PatchThing(ImageBase + 0x1E365E0); // widget class
    PatchThing(ImageBase + 0xC96CA0); // changegamesession
    PatchThing(ImageBase + 0x52480E); // collect garbage?

    MH_EnableHook(MH_ALL_HOOKS);

    UKismetSystemLibrary::ExecuteConsoleCommand(UWorld::GetWorld(), L"open Athena_Terrain", nullptr);
    UWorld::GetWorld()->OwningGameInstance->LocalPlayers.Remove(0);

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

