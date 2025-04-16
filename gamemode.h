#pragma once
#include "framework.h"
#include "hook.h"

namespace GM {
	bool (*ReadyToStartMatch)(AFortGameModeAthena*);
	bool ReadyToStartMatchHook(AFortGameModeAthena* GM) {
		bool Ready = false;
		if (!Ready) {
			std::cout << "ReadyToStartMatch called";
		}
	}
}