// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TargetSpawner.generated.h"

UCLASS()
class TESTTASK_API ATargetSpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATargetSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FVector TargetLocation;

	// All these parameters available in BP
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
		int32 TargetsAmount = 15;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
		int32 RadiusSpawn = 2000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
		int32 TargetsIncreasePercent = 10;

	// No ClampMin to let spawn targets closer every round if it's needed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
		int32 RadiusIncreasePercent = 5;


public:
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AActor> TargetToSpawn;

	UFUNCTION()
		void SpawnTargets();

	// Getters and Setters in public section for all our game parametres
	FVector GetLocation() const { return TargetLocation; }
	void SetLocation(FVector& loc) { TargetLocation = loc; }

	int32 GetTargetAmount() const { return TargetsAmount; }
	void SetTargetAmount(int32 targets) { TargetsAmount = targets; }

	int32 GetRadiusSpawn() const { return RadiusSpawn; }
	void SetRadiusSpawn(int32 radius) { RadiusSpawn = radius; }

	int32 GetTargetIncreasePercent() const { return TargetsIncreasePercent; }
	void SetTargetIncreasePercent(int32 amount) { TargetsIncreasePercent = amount; }

	int32 GetRadiusIncreasePercent() const { return RadiusIncreasePercent; }
	void SetRadiusIncreasePercent(int32 radius) { RadiusIncreasePercent = radius; }
};
