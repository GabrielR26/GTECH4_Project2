// Fill out your copyright notice in the Description page of Project Settings.

#include "Bumper.h"
#include "Components/BoxComponent.h"

ABumper::ABumper()
{
	// Create the mesh component	
	meshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = meshComponent;
	// Create the box component	
	boxComponent = CreateDefaultSubobject<UBoxComponent>("Box");
	boxComponent->SetupAttachment(RootComponent);
}

void ABumper::BeginPlay()
{
	Super::BeginPlay();

	if (boxComponent)
		boxComponent->OnComponentBeginOverlap.AddDynamic(this, &ABumper::BeginOverlap);
}

void ABumper::BeginOverlap(UPrimitiveComponent* _overlappedComponent, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIndex, bool _bFromSweep, const FHitResult& _sweepResult)
{
	FVector _impulseDirection = (_otherActor->GetActorLocation() - _sweepResult.ImpactPoint).GetSafeNormal(0.1f);
	_otherComp->AddImpulse(_impulseDirection * power * 100);
}