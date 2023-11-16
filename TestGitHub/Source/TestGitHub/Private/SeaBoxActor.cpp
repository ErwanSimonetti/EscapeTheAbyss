// Fill out your copyright notice in the Description page of Project Settings.


#include "SeaBoxActor.h"

// Sets default values
ASeaBoxActor::ASeaBoxActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASeaBoxActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASeaBoxActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ASeaBoxActor::isSeaOverlappingWithPlayer()
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

