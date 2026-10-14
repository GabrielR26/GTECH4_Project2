// Fill out your copyright notice in the Description page of Project Settings.

#include "Platefrom.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

APlateform::APlateform()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create the mesh component
	meshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = meshComponent;
	// Create the start offset component
	startOffsetComponent = CreateDefaultSubobject<USceneComponent>("StartOffset");
	startOffsetComponent->SetupAttachment(RootComponent);
	// Create the end offset component
	endOffsetComponent = CreateDefaultSubobject<USceneComponent>("EndOffset");
	endOffsetComponent->SetupAttachment(RootComponent);
}

void APlateform::BeginPlay()
{
	Super::BeginPlay();

	// Save location (moving with actor :) )
	startOffsetLocation = startOffsetComponent->GetComponentLocation();
	endOffsetLocation = endOffsetComponent->GetComponentLocation();

	// Set Plateform at start offset
	SetActorLocation(startOffsetLocation);
	changeState = false;
}

void APlateform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//UKismetSystemLibrary::PrintString(GetWorld(), "TICK", true, true, FLinearColor::Blue, 3.f);

	// Draw debug between both location
	if (!GetWorld()->IsGameWorld())
	{
		UKismetSystemLibrary::DrawDebugLine(GetWorld(), startOffsetComponent->GetComponentLocation(), endOffsetComponent->GetComponentLocation(), FLinearColor::Green, 0.f, 2.f);
		return;
	}

	if (changeState)
		MovePlateform(DeltaTime);
}

bool APlateform::ShouldTickIfViewportsOnly() const
{
	return true;
}

void APlateform::MovePlateform(const float _deltaTime)
{
	const float _speed = moveSpeed * 100.f;
	FVector _actorLoc = GetActorLocation();

	// If reach destination
	if (FVector::Dist(_actorLoc, destination) < 1.f)
	{
		atStart = !atStart;
		if (!loop)
			changeState = false;
		else
			destination = atStart ? endOffsetLocation : startOffsetLocation;
		return;
	}

	FVector _interp = UKismetMathLibrary::VInterpTo_Constant(_actorLoc, destination, _deltaTime, _speed);
	SetActorLocation(_interp, true);
}

void APlateform::Activate()
{
	ChangeState();
}

void APlateform::Deactivate()
{
	ChangeState();
}

void APlateform::ChangeState()
{
	// Stop move during loop
	if (loop && changeState)
	{
		changeState = false;
		return;
	}

	changeState = true;
	destination = atStart ? endOffsetLocation : startOffsetLocation;
}
