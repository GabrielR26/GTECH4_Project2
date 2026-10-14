// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerPlateformer.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

APlayerPlateformer::APlayerPlateformer()
{
	// Create the camera component	
	cameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	cameraComponent->SetupAttachment(RootComponent);
	// Create the box component	for interaction
	boxInteractionComponent = CreateDefaultSubobject<UBoxComponent>("BoxInteraction");
	boxInteractionComponent->SetupAttachment(RootComponent);
	// Create the offset component for interactable
	offsetInteractableComponent = CreateDefaultSubobject<USceneComponent>("OffsetInteractable");
	offsetInteractableComponent->SetupAttachment(RootComponent);
}

void APlayerPlateformer::BeginPlay()
{
	Super::BeginPlay();

	// Bind Overlap event
	if (boxInteractionComponent)
		boxInteractionComponent->OnComponentBeginOverlap.AddDynamic(this, &APlayerPlateformer::BeginOverlap);
}

void APlayerPlateformer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* _input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (_input != nullptr)
	{
		// Bind move action
		_input->BindAction(moveAction, ETriggerEvent::Triggered, this, &APlayerPlateformer::MoveInput);
		// Bind jump action
		_input->BindAction(jumpAction, ETriggerEvent::Started, this, &APlayerPlateformer::JumpStartInput);
		_input->BindAction(jumpAction, ETriggerEvent::Completed, this, &APlayerPlateformer::JumpEndInput);
		// Bind interact action
		_input->BindAction(interactAction, ETriggerEvent::Triggered, this, &APlayerPlateformer::InteractInput);
		// Bind look action
		_input->BindAction(lookAction, ETriggerEvent::Triggered, this, &APlayerPlateformer::LookInput);
	}
}

void APlayerPlateformer::BeginOverlap(UPrimitiveComponent* _overlappedComponent, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIndex, bool _bFromSweep, const FHitResult& _sweepResult)
{
	//if (_otherActor->) is interface interactable
	// II->Interaction(...)
}

void APlayerPlateformer::MoveInput(const FInputActionValue& Value)
{
	FVector2D _moveVector = Value.Get<FVector2D>();

	AddMovementInput(GetActorRightVector(), _moveVector.X);
	AddMovementInput(GetActorForwardVector(), _moveVector.Y);
}

void APlayerPlateformer::JumpStartInput()
{
	Jump();
}

void APlayerPlateformer::JumpEndInput()
{
	StopJumping();
}

void APlayerPlateformer::InteractInput()
{
	// Interaction
}

void APlayerPlateformer::LookInput(const FInputActionValue& Value)
{
	FVector2D _lookVector = Value.Get<FVector2D>();

	AddControllerYawInput(-_lookVector.X);
	AddControllerPitchInput(_lookVector.Y);
}
