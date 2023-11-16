// Fill out your copyright notice in the Description page of Project Settings.

#include "RiverBoxActor.h"
#include "Components/BoxComponent.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include <string>
#include <iostream>

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

bool AARiverBoxActor::isRiverOverlappingWithPlayer()
{
	TSet<AActor*> OverlappingActors;
	CollisionBox->GetOverlappingActors(OverlappingActors);
	APlayerCameraManager* camManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	UPrimitiveComponent* CameraPrimitiveComponent = Cast<UPrimitiveComponent>(camManager->GetViewTarget()->GetRootComponent());
	FVector PointToCheck = CameraPrimitiveComponent->GetComponentTransform().GetLocation();
	bool CameraIsInsideBox = false;
	
	if (CameraPrimitiveComponent && CollisionBox) {
		PointToCheck.Y -= 225;
		
		CameraIsInsideBox = CollisionBox->Bounds.GetBox().IsInside(PointToCheck);
		if (CameraIsInsideBox)
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, "camera inside box");
	}
	for (int i = 0; i < OverlappingActors.Array().Num(); i += 1) {
		FString OverlappingActor = OverlappingActors.Array()[i]->GetActorLabel();

		if (OverlappingActor == "Player" && CameraIsInsideBox)
			return true;
	}
	return false;
}

