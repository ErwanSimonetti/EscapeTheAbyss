// Fill out your copyright notice in the Description page of Project Settings.


#include "RiverBoxActor.h"
#include "Components/BoxComponent.h"
#include "Engine/Engine.h"

// Sets default values
AARiverBoxActor::AARiverBoxActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	CollisionBox->SetBoxExtent(FVector(32.f, 32.f, 32.f));
	CollisionBox->SetCollisionProfileName("Trigger");
	RootComponent = CollisionBox;

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AARiverBoxActor::OnOverlapBegin);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &AARiverBoxActor::OnOverlapEnd);
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

void AARiverBoxActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, "Overlap Begin Function Called");
	TSet<AActor*> OverlappingActors;
	CollisionBox->GetOverlappingActors(OverlappingActors);
	FString OverlappingActor = OverlappingActors.Array()[0]->GetActorLabel();
	if (OverlappingActor == "Player")
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, "Overlapping Actor is player");
	else
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, "Overlapping Actor is NOT player");
}

void AARiverBoxActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "Overlap End Function Called");
}

