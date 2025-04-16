#pragma once
#include "framework.h"
namespace Player
{
	void (*ServerAcknowlegePossession)(AFortPlayerControllerAthena* Controller, AFortPawn* Pawn);
	void ServerAcknowlegePossessionHook(AFortPlayerControllerAthena* Controller, AFortPawn* Pawn) {
		Controller->AcknowledgedPawn = Pawn;
		return ServerAcknowlegePossession(Controller, Pawn);
	}

	void (*ServerLoadingScreenDropped)(AFortPlayerControllerAthena*);
	void ServerLoadingScreenDroppedHook(AFortPlayerControllerAthena* Controller) {
		return ServerLoadingScreenDropped(Controller);
	}
}