// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestTaskProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Target/Target.h"
#include "TT_PlayerState.h"
#include "TestTaskGameMode.h"

ATestTaskProjectile::ATestTaskProjectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &ATestTaskProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	// I changed speed for my game, so you can hit as expected
	ProjectileMovement->InitialSpeed = 6000.0f;
	ProjectileMovement->MaxSpeed = 6000.0f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void ATestTaskProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		// If projectile hit Target, it destroy it and quit from function
		if (OtherActor->IsA<ATarget>())
		{
			OtherActor->Destroy();
			Destroy();

			AddDestroyed();
			return;
		}

		// In other situation it act by default
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());

		Destroy();
	}
}

void ATestTaskProjectile::AddDestroyed()
{
	const auto Controller = GetWorld()->GetPlayerControllerIterator()->Get();
	if (!Controller) return;

	// Here we get access to PlayerState
	const auto PlayerState = Cast<ATT_PlayerState>(Controller->PlayerState);
	if (!PlayerState) return;

	// And increase amount of destroyed items
	PlayerState->AddDestroyed();

	// Debug information in output log
	UE_LOG(LogTemp, Display, TEXT("%i"), PlayerState->DestroyedAmount());
}