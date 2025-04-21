#pragma once
#include "framework.h"
namespace Player
{
	void (*ServerAcknowlegePossession)(AFortPlayerControllerAthena* PC, AFortPawn* Pawn);
	void ServerAcknowlegePossessionHook(AFortPlayerControllerAthena* PC, AFortPawn* Pawn) {
		PC->AcknowledgedPawn = Pawn;
		auto PS = reinterpret_cast<AFortPlayerStateAthena*>(PC->PlayerState);
		ApplyCharacterCustomization(PS, (AFortPawn*)Pawn);
		return ServerAcknowlegePossession(PC, Pawn);
	}

	void (*ServerLoadingScreenDropped)(AFortPlayerControllerAthena*);
	void ServerLoadingScreenDroppedHook(AFortPlayerControllerAthena* PC) {
		return ServerLoadingScreenDropped(PC);
	}

	void (*ServerReadyToStartMatch)(AFortPlayerControllerAthena* PC);
	void ServerReadyToStartMatchHook(AFortPlayerControllerAthena* PC) {
		return ServerReadyToStartMatch(PC);
	}

	void (*ServerReturnToMainMenu)(AFortPlayerControllerAthena* PC);
	void ServerReturnToMainMenuHook(AFortPlayerControllerAthena* PC) { // bye!
		PC->bIsDisconnecting = true;
		PC->ClientTravel(L"Frontend", ETravelType::TRAVEL_Absolute, false, {});

		return ServerReturnToMainMenu(PC);
	}

	void (*GetPlayerViewPoint)(AFortPlayerControllerAthena*, FVector Location, FRotator Rotation);
	void GetPlayerViewPointHook(AFortPlayerControllerAthena* PC, FVector& Location, FRotator& Rotation) {
		if (auto Pawn = PC->Pawn) {
			Location = Pawn->K2_GetActorLocation();
			Rotation = PC->GetControlRotation();
			return;
		}

		return GetPlayerViewPoint(PC, Location, Rotation);
	}
}