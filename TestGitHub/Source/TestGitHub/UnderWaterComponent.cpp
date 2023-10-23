// Fill out your copyright notice in the Description page of Project Settings.


#include "UnderWaterComponent.h"
#include "GameFramework/Actor.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Controller.h"

bool UUnderWaterComponent::IsPlayerUnderwater(void)
{
    AActor* OwnerActor = GetOwner();
    if (OwnerActor)
    {
        FVector PlayerLocation = OwnerActor->GetActorLocation();
        FVector ActorForwardVector = OwnerActor->GetActorForwardVector();
        FVector TraceStart = PlayerLocation + (ActorForwardVector * 10.0f); // Décalage pour éviter les collisions avec le joueur lui-même
        FVector TraceEnd = PlayerLocation - FVector::UpVector * 200.0f; // Profondeur sous l'eau que vous souhaitez vérifier

        FHitResult HitResult;
        FCollisionQueryParams CollisionParams;
        CollisionParams.AddIgnoredActor(OwnerActor); // Ignorer le joueur lors du tracé de rayon

        // Tracez un rayon vers le bas à partir de la position du joueur
        if (GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, CollisionParams))
        {
            // Vérifiez si l'hit est sous l'eau
            if (HitResult.Location.Z < WaterSurfaceLevel)
            {
                // Le joueur est sous l'eau
                return true;
            }
        }
    }
    return false;
}

// Sets default values for this component's properties
UUnderWaterComponent::UUnderWaterComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


// Called when the game starts
void UUnderWaterComponent::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void UUnderWaterComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    // Obtenir l'acteur propriétaire du composant
    AActor* OwnerActor = GetOwner();
    if (OwnerActor)
    {
        // Vérifier si l'acteur est sous l'eau
        FVector ActorLocation = OwnerActor->GetActorLocation();
        if (IsPlayerUnderwater())
        {
            UE_LOG(LogTemp, Warning, TEXT("UNDER WATER"));
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("actor location f = %f"), ActorLocation.Z);
            //UE_LOG(LogTemp, Warning, TEXT("water surface level = %f"), WaterSurfaceLevel);
        }
    }
}

