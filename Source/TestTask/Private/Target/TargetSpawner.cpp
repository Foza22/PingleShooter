// Fill out your copyright notice in the Description page of Project Settings.


#include "Target/TargetSpawner.h"
#include "Target/Target.h"
#include "Components/BoxComponent.h"
#include "TestTask/TestTaskCharacter.h"

// Sets default values
ATargetSpawner::ATargetSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATargetSpawner::BeginPlay()
{
	Super::BeginPlay();
}

void ATargetSpawner::SpawnTargets()
{
	//// If no parametes passed to function we spawn default amount of targets in default radius
	//TargetsAmount = targets;
	//RadiusSpawn = radius;

	for (int i = 0; i < TargetsAmount; ++i)
	{
		// Get Random location in given radius for every target
		// We attach spawner to FirstPerson in blueprints so it spawning around our character
		TargetLocation = GetActorLocation();
		TargetLocation.X = TargetLocation.X + (FMath::RandBool() ? (FMath::Rand() % RadiusSpawn) : (-FMath::Rand() % RadiusSpawn));
		TargetLocation.Y = TargetLocation.Y + (FMath::RandBool() ? (FMath::Rand() % RadiusSpawn) : (-FMath::Rand() % RadiusSpawn));
		TargetLocation.Z = 500 + FMath::Rand() % 300;
		GetWorld()->SpawnActor<AActor>(TargetToSpawn, TargetLocation, GetActorRotation());
	}
}