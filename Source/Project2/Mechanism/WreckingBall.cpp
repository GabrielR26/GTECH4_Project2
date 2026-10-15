// Fill out your copyright notice in the Description page of Project Settings.

#include "WreckingBall.h"
#include "CableComponent.h"
#include <PhysicsEngine/PhysicsConstraintComponent.h>
#include "Kismet/KismetSystemLibrary.h"

AWreckingBall::AWreckingBall()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create the anchor component
	anchorComponent = CreateDefaultSubobject<UStaticMeshComponent>("Anchor");
	RootComponent = anchorComponent;
	// Create the ball component	
	ballComponent = CreateDefaultSubobject<UStaticMeshComponent>("Ball");
	ballComponent->SetupAttachment(RootComponent);
	// Create the cable component	
	cableComponent = CreateDefaultSubobject<UCableComponent>("Cable");
	cableComponent->SetupAttachment(RootComponent);
	// Create the physics constraint component	
	physicsConstraintsComponent = CreateDefaultSubobject<UPhysicsConstraintComponent>("PhysicsConstraints");
	physicsConstraintsComponent->SetupAttachment(RootComponent);
}

void AWreckingBall::BeginPlay()
{
	Super::BeginPlay();

	ballComponent->SetSimulatePhysics(false);
	
	// Attach cable to Anchor/Ball
	cableComponent->bAttachStart = true;
	cableComponent->SetAttachEndToComponent(ballComponent);
	cableComponent->bAttachEnd = true;
}

void AWreckingBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Draw debug wrecking radius
	if (!GetWorld()->IsGameWorld())
	{
		UKismetSystemLibrary::DrawDebugCircle(GetWorld(), GetActorLocation(), wreckingRadius * 0.5f, 16, FLinearColor::Red, 0.f, 2.f);
		return;
	}
}

bool AWreckingBall::ShouldTickIfViewportsOnly() const
{
	return true;
}

void AWreckingBall::Test()
{
	Activate();
}

void AWreckingBall::Activate()
{
	// "Awake" ball
	ballComponent->SetSimulatePhysics(true);
}

void AWreckingBall::Deactivate()
{
	//
}

#if WITH_EDITOR
void AWreckingBall::PostEditChangeProperty(FPropertyChangedEvent& _propertyChangedEvent)
{
	Super::PostEditChangeProperty(_propertyChangedEvent);

	const FName _propertyName = _propertyChangedEvent.GetPropertyName();

	if (_propertyName == GET_MEMBER_NAME_CHECKED(AWreckingBall, wreckingRadius))
	{
		if (ballComponent)
		{
			FVector _ballLocation = -GetActorRightVector() * wreckingRadius;
			ballComponent->SetRelativeLocation(_ballLocation);
		}
	}
}
#endif