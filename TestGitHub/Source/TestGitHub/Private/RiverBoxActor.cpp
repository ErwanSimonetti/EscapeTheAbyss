// Fill out your copyright notice in the Description page of Project Settings.

#include "RiverBoxActor.h"
#include "Components/BoxComponent.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AARiverBoxActor::AARiverBoxActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	CollisionBox->SetBoxExtent(FVector(32.f, 32.f, 32.f));
	CollisionBox->SetCollisionProfileName("Trigger");
	RootComponent = CollisionBox;
}

// Called when the game starts or when spawned
void AARiverBoxActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AARiverBoxActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AARiverBoxActor::isRiverOverlapping()
{
	TSet<AActor*> OverlappingActors;
	CollisionBox->GetOverlappingActors(OverlappingActors);

	for (int i = 0; i < OverlappingActors.Array().Num(); i += 1) {
		FString OverlappingActor = OverlappingActors.Array()[i]->GetActorLabel();

		if (OverlappingActor == "Player")
			return true;
	}
	return false;
}

