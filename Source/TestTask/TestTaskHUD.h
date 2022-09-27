// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TestTaskHUD.generated.h"

UCLASS()
class ATestTaskHUD : public AHUD
{
	GENERATED_BODY()

public:
	ATestTaskHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

protected:
	// We need to choose class in Blueprint
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UUserWidget> PlayerHUDWidgetClass;

	virtual void BeginPlay() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

