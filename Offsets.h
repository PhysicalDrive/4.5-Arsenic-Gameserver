#pragma once
#include <windows.h>
#include <iostream>
#include <format>
#include <vector>

//if I did something wrong then change it ig

namespace EngineOffsets { // I'm bad at finding engine offsets so I'm cooked
	static uintptr_t ReadyToStartMatch = 0x25A0BE0;
	static uintptr_t InternalTryActivateAbility = 0x581590;
	static uintptr_t StaticFindObject = 0x15B6350;
	static uintptr_t StaticLoadObject = 0x15B7E30;
	static uintptr_t SpawnDefaultPawnFor = 0xA81410;
}
namespace VTableOffsets {
	static uintptr_t ServerReadyToStartMatch = 0x240;
	static uintptr_t ServerLoadingScreenDropped = 0x242;
	static uintptr_t ServerAcknowledgePossession = 0x104;
	static uintptr_t ServerExecuteInventoryItem = 0x1E4;
	static uintptr_t ServerAttemptInventoryDrop = 0x1F6;
	static uintptr_t ServerHandlePickup = 0x199;
	static uintptr_t ServerCreateBuildingActor = 0x200; // I don't even know if this is correct or not my ida is fucked
	static uintptr_t ServerBeginEditingBuildingActor = 0x206;
	static uintptr_t ServerEditBuildingActor = 0x202;
	static uintptr_t ServerEndEditingBuildingActor = 0x204;
	static uintptr_t ServerPlayEmoteItem = 0x1B3;

}