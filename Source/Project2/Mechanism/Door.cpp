// Fill out your copyright notice in the Description page of Project Settings.

#include "Door.h"
#include <PhysicsEngine/PhysicsConstraintComponent.h>

ADoor::ADoor()
{
	// Create the door1 component	
	door1Component = CreateDefaultSubobject<UStaticMeshComponent>("Door1");
	RootComponent = door1Component;
	// Create the door2 component	
	door2Component = CreateDefaultSubobject<UStaticMeshComponent>("Door2");
	door2Component->SetupAttachment(RootComponent);
	// Create the physics constraint central component	
	physicsConstraints0Component = CreateDefaultSubobject<UPhysicsConstraintComponent>("PhysicsConstraints0");
	physicsConstraints0Component->SetupAttachment(RootComponent);
	// Create the physics constraint door1 component	
	physicsConstraints1Component = CreateDefaultSubobject<UPhysicsConstraintComponent>("PhysicsConstraints1");
	physicsConstraints1Component->SetupAttachment(RootComponent);
	// Create the physics constraint door2 component	
	physicsConstraints2Component = CreateDefaultSubobject<UPhysicsConstraintComponent>("PhysicsConstraints2");
	physicsConstraints2Component->SetupAttachment(RootComponent);
}

void ADoor::BeginPlay()
{
	Super::BeginPlay();

	door1Component->SetMaterial(0, closeMaterial);
	door2Component->SetMaterial(0, closeMaterial);
	
	float _breakLimit = isBreakable ? breakLimit : 9999999.f;
	physicsConstraints0Component->SetLinearBreakable(true, _breakLimit);
}

void ADoor::Activate()
{
	physicsConstraints0Component->BreakConstraint();

	door1Component->SetMaterial(0, openMaterial);
	door2Component->SetMaterial(0, openMaterial);
}

void ADoor::Deactivate()
{
	//
}
