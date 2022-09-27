// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameDataUserWidget.generated.h"

// Forward declaration
class ATestTaskGameMode;
class ATT_PlayerState;

UCLASS()
class TESTTASK_API UGameDataUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    UFUNCTION(BlueprintCallable, Category = "UI")
        int32 GetCurrentRoundNum() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
        int32 GetDestroyedAmount() const;

private:
    // Cosmetic functions to clear code
    ATestTaskGameMode* GetTTGameMode() const;
    ATT_PlayerState* GetTTPlayerState() const;
};
