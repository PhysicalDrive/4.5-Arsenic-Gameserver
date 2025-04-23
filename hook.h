#pragma once
#include "framework.h"

static UObject* (*StaticFindObject_)(UClass* Class, UObject* Package, const wchar_t* OrigInName, bool ExactClass) = decltype(StaticFindObject_)(uintptr_t(GetModuleHandle(0)) + 0x15B6350);
static UObject* (*StaticLoadObject_)(UClass* Class, UObject* InOuter, const TCHAR* Name, const TCHAR* Filename, uint32_t LoadFlags, UObject* Sandbox, bool bAllowObjectReconciliation) = decltype(StaticLoadObject_)(uintptr_t(GetModuleHandle(0)) + 0x15B7E30); // offset for this might be incorrect oh well
template <typename T>
inline T* StaticFindObject(std::string ObjectPath, UClass* Class = nullptr)
{
	return (T*)StaticFindObject_(Class, nullptr, std::wstring(ObjectPath.begin(), ObjectPath.end()).c_str(), false);
}

template <typename T>
inline T* StaticLoadObject(std::string Path, UClass* InClass = T::StaticClass(), UObject* Outer = nullptr)
{
	return (T*)StaticLoadObject_(InClass, Outer, std::wstring(Path.begin(), Path.end()).c_str(), nullptr, 0, nullptr, false);
}
static __int64 (*DispatchRequest)(__int64, __int64*, int);
static __int64 DispatchRequestHook(__int64 a1, __int64* a2, int a3) {
	*(int*)(__int64(a2) + 0x60) = a3;
	return DispatchRequest(a1, a2, 3);
}

static __int64 __fastcall NoReserve(__int64 a1, __int64 a2, char a3, __int64 a4) {
	return true;
}
int KickPlayer() {
	return 1;
}
static __int64 __fastcall CanActivateAbility(__int64 a1, unsigned int a2, DWORD* a3, __int64 a4, __int64 a5, __int64* a6) {
	return 1;
}

int UWorldGetNetMode() { // idk ida doesn't show
	return 1;
}

float GetMaxTickRate() {
	return 30.f;
}

static UNetDriver* (*CreateNetDriver)(UEngine* Engine, UWorld*, FName NetDriverDefinition) = decltype(CreateNetDriver)(uintptr_t(GetModuleHandle(0)) + 0x24E2F80);
static bool (*InitHost)(AOnlineBeacon* Beacon) = decltype(InitHost)(uintptr_t(GetModuleHandle(0)) + 0x39DAB0);
static void (*SetWorld)(UNetDriver* Driver, UWorld* World) = decltype(SetWorld)(uintptr_t(GetModuleHandle(0)) + 0x1AEFA50);
static bool (*InitListen)(UNetDriver* Driver, void* InNotify, FURL& LocalURL, bool bReuseAddressAndPort, FString& Error) = decltype(InitListen)(uintptr_t(GetModuleHandle(0)) + 0x39DE90);
static void* (*ApplyCharacterCustomization)(AFortPlayerState* PlayerState, AFortPawn* Pawn) = decltype(ApplyCharacterCustomization)(uintptr_t(GetModuleHandle(0)) + 0xFC8DA0);
static bool (*ServerReplicateActors)(UReplicationDriver* ReplicationDriver) = decltype(ServerReplicateActors)(uintptr_t(GetModuleHandle(0)) + 0x700820);
static void (*PauseBeaconRequests)(AOnlineBeacon* Beacon, bool bPause) = decltype(PauseBeaconRequests)(uintptr_t(GetModuleHandle(0)) + 0xE15DB0);

void TickFlushHook(UNetDriver* NetDriver) {
	if (NetDriver->ReplicationDriver && NetDriver->ClientConnections.Num() > 0 && !NetDriver->ClientConnections[0]->InternalAck)
		ServerReplicateActors(NetDriver->ReplicationDriver);
}
