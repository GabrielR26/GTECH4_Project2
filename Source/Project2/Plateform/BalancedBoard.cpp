// Fill out your copyright notice in the Description page of Project Settings.

#include "BalancedBoard.h"
#include <PhysicsEngine/PhysicsConstraintComponent.h>

ABalancedBoard::ABalancedBoard()
{
	// Create the base component
	baseComponent = CreateDefaultSubobject<UStaticMeshComponent>("Base");
	RootComponent = baseComponent;
	// Create the board component	
	boardComponent = CreateDefaultSubobject<UStaticMeshComponent>("Board");
	boardComponent->SetupAttachment(RootComponent);
	// Create the physics constraint component	
	physicsConstraintsComponent = CreateDefaultSubobject<UPhysicsConstraintComponent>("PhysicsConstraints");
	physicsConstraintsComponent->SetupAttachment(RootComponent);
}

void ABalancedBoard::BeginPlay()
{
	Super::BeginPlay();

	// Set swing 2 motion
	if (swingLimit)
		physicsConstraintsComponent->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Limited, swingLimitAngle);
	else
		physicsConstraintsComponent->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Free, 0.f);

	// Locked other angular motion
	physicsConstraintsComponent->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 0.f);
	physicsConstraintsComponent->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 0.f);
}
