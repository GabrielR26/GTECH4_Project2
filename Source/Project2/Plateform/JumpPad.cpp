// Fill out your copyright notice in the Description page of Project Settings.

#include "JumpPad.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"

AJumpPad::AJumpPad()
{
	// Create the pad component
	padComponent = CreateDefaultSubobject<UStaticMeshComponent>("Pad");
	RootComponent = padComponent;
	// Create the box component	
	boxComponent = CreateDefaultSubobject<UBoxComponent>("Box");
	boxComponent->SetupAttachment(RootComponent);
}

void AJumpPad::BeginPlay()
{
	Super::BeginPlay();

	if (boxComponent)
		boxComponent->OnComponentBeginOverlap.AddDynamic(this, &AJumpPad::BeginOverlap);
}

void AJumpPad::BeginOverlap(UPrimitiveComponent* _overlappedComponent, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIndex, bool _bFromSweep, const FHitResult& _sweepResult)
{
	ACharacter* _chara = Cast<ACharacter>(_otherActor);
	if (!_chara)
		return;

	// Launch the player forward + up * force
	const FVector _forward = GetActorForwardVector();
	const FVector _launchVector = (_forward + FVector::UpVector) * launchForce;
	_chara->LaunchCharacter(_launchVector, true, true);
}