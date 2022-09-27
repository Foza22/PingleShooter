// Fill out your copyright notice in the Description page of Project Settings.

#include "Target/Target.h"
#include "Components/SphereComponent.h"
#include "Target/TargetSpawner.h"
#include "TestTask/TestTaskProjectile.h"

// Sets default values
ATarget::ATarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Creating sphere component for target
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SphereComp->InitSphereRadius(30.0f);
	// Creating mesh component and enabling settings
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	StaticMeshComp->SetSimulatePhysics(true);
	StaticMeshComp->SetEnableGravity(false);

	// Attaching sphere and enabling collision
	SphereComp->SetupAttachment(RootComponent); 
	SetRootComponent(SphereComp);
	SphereComp->SetCollisionProfileName(FName("NoCollision"));

	// Attaching static mesh to sphere
	StaticMeshComp->AttachToComponent(SphereComp, FAttachmentTransformRules::KeepRelativeTransform);

	// Fitting static mesh to sphere
	StaticMeshComp->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
}