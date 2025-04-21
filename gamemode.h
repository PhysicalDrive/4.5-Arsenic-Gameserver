#pragma once
#include "framework.h"
#include "hook.h"
#include "global.h"
namespace GM {
	bool (*ReadyToStartMatch)(AFortGameModeAthena*);
	bool ReadyToStartMatchHook(AFortGameModeAthena* GM) {
		bool Ready = false;
		if (!Ready) {
			Ready = true;
			UFortPlaylistAthena* Playlist = StaticFindObject<UFortPlaylistAthena>(Global::Playlist);
			GetGameState()->CurrentPlaylistData = Playlist;
			GetGameState()->OnRep_CurrentPlaylistData();
			if (UWorld::GetWorld()->NetDriver) {
				UNetDriver* NetDriver = CreateNetDriver(UEngine::GetEngine(), UWorld::GetWorld(), FName(282));
				NetDriver->World = UWorld::GetWorld();
				NetDriver->NetDriverName = FName(282);

				FString Error;
				FURL URL = FURL();
				URL.Port = 7777;

				InitListen(NetDriver, UWorld::GetWorld(), URL, false, Error);
				SetWorld(NetDriver, UWorld::GetWorld());

				UWorld::GetWorld()->LevelCollections[0].NetDriver = NetDriver;
				UWorld::GetWorld()->LevelCollections[1].NetDriver = NetDriver;
			}
			GM->WarmupRequiredPlayerCount = 1;
			UWorld::GetWorld()->AuthorityGameMode->GameSession->MaxPlayers = 100;
			GetGameState()->PlayersLeft--;
			GetGameState()->OnRep_PlayersLeft();
			GM->bWorldIsReady = true;
		}

		return ReadyToStartMatch(GM);
	}

	static APawn* (*SpawnDefaultPawnFor)(AFortGameModeAthena* GM, AController* NewPlayer, AActor* StartSpot);
	APawn* SpawnDefaultPawnForHook(AFortGameModeAthena* GM, AController* NewPlayer, AActor* StartSpot) {
		if (NewPlayer && StartSpot) {
			FTransform Transform = StartSpot->GetTransform();
			return GM->SpawnDefaultPawnAtTransform(NewPlayer, Transform);
		}
	}

	static void (*HandleStartingNewPlayer)(AFortGameModeAthena*, AFortPlayerControllerAthena*);
	void HandleStartingNewPlayerHook(AFortGameModeAthena* GM, AFortPlayerControllerAthena* PC) {
		auto PS = (AFortPlayerStateAthena*)PC->PlayerState;
		PC->bHasServerFinishedLoading = true;
		PC->OnRep_bHasServerFinishedLoading();
		PS->bHasStartedPlaying = true;
		PS->OnRep_bHasStartedPlaying();
		PC->OverriddenBackpackSize = 5;
		return HandleStartingNewPlayer(GM, PC);
	}

}