// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "TT_PlayerState.generated.h"

UCLASS()
class TESTTASK_API ATT_PlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	// Called after every target destruction
	void AddDestroyed() { ++DestroyedTargets; }
	// Returns the total amount of destroyed
	int32 DestroyedAmount() const { return DestroyedTargets; }
	// On the beginningof every round we set destroyed amount to 0
	void ResetDestroyed() { DestroyedTargets = 0; }

private:
	int32 DestroyedTargets = 0;
};
