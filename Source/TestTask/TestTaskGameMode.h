// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TestTaskGameMode.generated.h"

UCLASS(minimalapi)
class ATestTaskGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATestTaskGameMode();

	virtual void StartPlay() override;

	// Function to change amount and radius for current round
	void SpawnTargets();

	// Function called every time, when destroyed targets amount = 10
	void StartNextRound();

	int32 GetCurrentRound() { return CurrentRound; }

	// Function for updating stat
	void GetUpdate();

private:
	int32 CurrentRound;
	FTimerHandle GameUpdateTimerHandle;
	class APlayerController* Controller;
	class ATT_PlayerState* TT_PlayerState;
};



