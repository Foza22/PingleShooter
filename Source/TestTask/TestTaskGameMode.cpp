// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestTaskGameMode.h"
#include "TestTaskHUD.h"
#include "TestTaskCharacter.h"
#include "Target/Target.h"
#include "Target/TargetSpawner.h"
#include "TT_PlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

ATestTaskGameMode::ATestTaskGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class and PlayerState
	HUDClass = ATestTaskHUD::StaticClass();
	PlayerStateClass = ATT_PlayerState::StaticClass();
}

void ATestTaskGameMode::StartPlay()
{
	Super::StartPlay();

	// On the beginning of the game we set numebr round to 1 and spawn targets
	CurrentRound = 1;
	SpawnTargets();
	
	// Get access to our Destroyed Target functions
	Controller = GetWorld()->GetPlayerControllerIterator()->Get();
	if (!Controller) return;

	TT_PlayerState = Cast<ATT_PlayerState>(Controller->PlayerState);
	if (!TT_PlayerState) return;

	// Setting timer to Update info of Destroyed Targets every second
	GetWorldTimerManager().SetTimer(GameUpdateTimerHandle, this, &ATestTaskGameMode::GetUpdate, 1.0f, true);
}

void ATestTaskGameMode::GetUpdate()
{
	// There is only check
	if (TT_PlayerState->DestroyedAmount() >= 10) { StartNextRound(); TT_PlayerState->ResetDestroyed(); }
}

void ATestTaskGameMode::StartNextRound()
{
	// On the beginning of the round we find and destroy all targets
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATarget::StaticClass(), FoundActors);

	for (AActor* ActorFound : FoundActors)
	{
		ActorFound->Destroy();
	}

	// Increase current round number and spawn new targets
	++CurrentRound;

	SpawnTargets();
}

void ATestTaskGameMode::SpawnTargets()
{
	// Get access to our spawner
	AActor* TargetSpawnerToFind = UGameplayStatics::GetActorOfClass(GetWorld(), ATargetSpawner::StaticClass());
	ATargetSpawner* ActorSpawnerReference = Cast<ATargetSpawner>(TargetSpawnerToFind);
	
	// Get all our parameters and change them in loop depending on round number
	int32 amount = ActorSpawnerReference->GetTargetAmount();
	int32 radius = ActorSpawnerReference->GetRadiusSpawn();
	int32 amountInc = ActorSpawnerReference->GetTargetIncreasePercent();
	int32 radiusInc = ActorSpawnerReference->GetRadiusIncreasePercent();

	// Applying our changed values if it's not the first round
	if (CurrentRound > 1)
	{
		amount += (amount * (amountInc / 100.0));
		radius += (radius * (radiusInc / 100.0));

		ActorSpawnerReference->SetTargetAmount(amount);
		ActorSpawnerReference->SetRadiusSpawn(radius);
	}

	// Or don't set value and increase it in loop every round
	// And change SpawnTargets function in spawner to take parameters

	/*for (int i = 1; i < GetCurrentRound(); ++i)
	{
		amount += (amount * (amountInc/100.0));
		radius += (radius * (radiusInc/100.0));
	}*/

	// After all changes spawn new targets with changed values
	ActorSpawnerReference->SpawnTargets();
	// Alternative version
	//ActorSpawnerReference->SpawnTargets(amount,radius);
}
