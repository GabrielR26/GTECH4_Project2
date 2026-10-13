// Fill out your copyright notice in the Description page of Project Settings.


#include "TeleportationPipe.h"
#include <BaseObject.h>

// Sets default values
ATeleportationPipe::ATeleportationPipe()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	mesh->SetupAttachment(RootComponent);
	box = CreateDefaultSubobject<UBoxComponent>("Box");
	box->SetupAttachment(RootComponent);
}

FVector ATeleportationPipe::GetTeleportLocation()
{
	
	return GetActorLocation() + GetActorForwardVector() * teleportOffset.X
		+ GetActorRightVector() * teleportOffset.Y
		+ GetActorUpVector() * teleportOffset.Z;
}

// Called when the game starts or when spawned
void ATeleportationPipe::BeginPlay()
{
	Super::BeginPlay();
	InitEvent();
}

// Called every frame
void ATeleportationPipe::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATeleportationPipe::InitEvent()
{
	if (!box)
		return;
	box->OnComponentBeginOverlap.AddDynamic(this, &ATeleportationPipe::OnBoxBeginOverlap);
}

void ATeleportationPipe::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!destinationPipe || !OtherActor)
		return;

	ABaseObject* _object = Cast<ABaseObject>(OtherActor);

	if (!_object)
		return;
	_object->SetLocation(destinationPipe->GetTeleportLocation());
}

