// Fill out your copyright notice in the Description page of Project Settings.


#include "GameDataUserWidget.h"
#include "TestTask/TestTaskGameMode.h"
#include "TT_PlayerState.h"

int32 UGameDataUserWidget::GetCurrentRoundNum() const
{
	// Get game mode and call function GetCurrentRound from there
	const auto GameMode = GetTTGameMode();
	return GameMode ? GameMode->GetCurrentRound() : 0;
}

int32 UGameDataUserWidget::GetDestroyedAmount() const
{
	// Get player state and get fuction DestroyedAmount from there
	const auto PlayerState = GetTTPlayerState();
	return PlayerState->DestroyedAmount();
}

ATestTaskGameMode* UGameDataUserWidget::GetTTGameMode() const
{
	// Getting game mode and casting it to our class
	return GetWorld() ? Cast<ATestTaskGameMode>(GetWorld()->GetAuthGameMode()) : nullptr;
}

ATT_PlayerState* UGameDataUserWidget::GetTTPlayerState() const
{
	// Getting player state. If it fail we return nullptr
	const auto Controller = GetWorld()->GetPlayerControllerIterator()->Get();
	if (!Controller) return nullptr;

	const auto PlayerState = Cast<ATT_PlayerState>(Controller->PlayerState);
	if (!PlayerState) return nullptr;

	return PlayerState;
}
