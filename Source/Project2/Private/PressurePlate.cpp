// Fill out your copyright notice in the Description page of Project Settings.


#include "PressurePlate.h"

APressurePlate::APressurePlate()
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	mesh->SetupAttachment(RootComponent);
	box = CreateDefaultSubobject<UBoxComponent>("Box");
	box->SetupAttachment(RootComponent);
}

void APressurePlate::BeginPlay()
{
	Super::BeginPlay();
	InitBeginLocation();
	InitEvent();
}

void APressurePlate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APressurePlate::InitEvent()
{
	if (!box)
		return;

	box->OnComponentBeginOverlap.AddDynamic(this, &APressurePlate::OnBoxBeginOverlap);
	box->OnComponentEndOverlap.AddDynamic(this, &APressurePlate::OnBoxEndOverlap);
}

void APressurePlate::InitBeginLocation()
{
	if (!mesh)
		return;
	beginLocation = mesh->GetComponentLocation();
}

void APressurePlate::PressPlate()
{
	if (!mesh)
		return;
	FVector _newLocation = IsPressed() ? beginLocation - FVector(0, 0, pressOffset) : beginLocation;
	mesh->SetWorldLocation(_newLocation);
}

void APressurePlate::AllObjectsBehaviour()
{
	for (AActor* _actor : activableObjects)
	{
		if (!_actor)
			continue;
		IActivable* _activable = Cast<IActivable>(_actor);
		if (!_activable)
			continue;

		if(IsPressed())
			_activable->Activate();
		else
			_activable->Deactivate();
	}
}

void APressurePlate::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	objectOnPlate++;
	if (objectOnPlate == 1)
	{
		AllObjectsBehaviour();
		PressPlate();
	}
}

void APressurePlate::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	objectOnPlate--;
	if (objectOnPlate == 0)
	{
		AllObjectsBehaviour();
		PressPlate();
	}
}

