// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupActor.h"
#include <Components/SceneComponent.h>
#include <Components/StaticMeshComponent.h>
#include <Components/SphereComponent.h>
#include "BaseEquippable.h"
#include <Components/SphereComponent.h>
#include <GameFramework/Pawn.h>

// Sets default values
APickupActor::APickupActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(rootComp);

	sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	sphereComp->SetupAttachment(rootComp);

	staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh Component"));
	staticMesh->SetupAttachment(sphereComp);	
}

// Called when the game starts or when spawned
void APickupActor::BeginPlay()
{
	Super::BeginPlay();

	FActorSpawnParameters params;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GetWorld()->SpawnActor<ABaseEquippable>(equippableItem, params);
}

// Called every frame
void APickupActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickupActor::Interact(AActor* callerActor)
{
	FActorSpawnParameters paramTemp;
	paramTemp.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::Undefined;
	paramTemp.TransformScaleMethod = ESpawnActorScaleMethod::MultiplyWithRoot;
	paramTemp.Owner = callerActor;
	paramTemp.Instigator = Cast<APawn>(callerActor);

	GetWorld()->SpawnActor<ABaseEquippable>(equippableItem, GetActorTransform(), paramTemp)->OnEquipped();
}

