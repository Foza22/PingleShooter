// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestTaskProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS(config = Game)
class ATestTaskProjectile : public AActor
{
	GENERATED_BODY()

		/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		USphereComponent* CollisionComp;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		UProjectileMovementComponent* ProjectileMovement;
public:
	ATestTaskProjectile();

	/** called when projectile hits something */
	UFUNCTION()
		virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/** Returns CollisionComp subobject **/
	USphereComponent* GetCollisionComp() const { return CollisionComp; }
	/** Returns ProjectileMovement subobject **/
	UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }

	// Function to increase the amount of destroyed itemss
	void AddDestroyed();
};

