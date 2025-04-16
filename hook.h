#pragma once
#include "framework.h"

static UObject* (*StaticFindObject_)(UClass* Class, UObject* Package, const wchar_t* OrigInName, bool ExactClass) = decltype(StaticFindObject_)(uintptr_t(GetModuleHandle(0)) + 0x15B6350);
static UObject* (*StaticLoadObject_)(UClass* Class, UObject* InOuter, const TCHAR* Name, const TCHAR* Filename, uint32_t LoadFlags, UObject* Sandbox, bool bAllowObjectReconciliation) = decltype(StaticLoadObject_)(uintptr_t(GetModuleHandle(0)) + 0x15B7E30); // offset for this might be incorrect oh well
template <typename T>
inline T* StaticFindObject(std::string ObjectPath, UClass* Class = UObject::StaticClass())
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
	return DispatchRequest(a1, a2, a3);
}

static __int64 __fastcall NoReserve(__int64 a1, __int64 a2, char a3, __int64 a4) {
	return 0;
}
static __int64 __fastcall KickPlayer(__int64 a1, __int64 a2, __int64 a3) {
	return 1;
}
static __int64 __fastcall CanActivateAbility(__int64 a1, unsigned int a2, DWORD* a3, __int64 a4, __int64 a5, __int64* a6) {
	return 1;
}

static UNetDriver* (*CreateNetDriver)(UEngine* Engine, UWorld*, FName NetDriverDefinition) = decltype(CreateNetDriver)(uintptr_t(GetModuleHandle(0)) + 0x24E2F80);