// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerPlateformer.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Interactable.h"
#include "BaseObject.h"
#include "Kismet/KismetSystemLibrary.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

APlayerPlateformer::APlayerPlateformer()
{
	// Create the camera component	
	cameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	cameraComponent->SetupAttachment(RootComponent);
	// Create the handle component for grab
	handleComponent = CreateDefaultSubobject<UPhysicsHandleComponent>("PhysicsHandle");
}

void APlayerPlateformer::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerPlateformer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isGrabing)
	{
		const FVector _targetLoc = cameraComponent->GetComponentLocation() + (cameraComponent->GetForwardVector() * 250.f);
		handleComponent->SetTargetLocation(_targetLoc);
	}
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
	if (isGrabing)
	{
		handleComponent->ReleaseComponent();
		isGrabing = false;
		return;
	}

	const FVector _start = cameraComponent->GetComponentLocation();
	const FVector _end = _start + (cameraComponent->GetForwardVector() * 250.f);
	FHitResult _hit;
	bool _res = UKismetSystemLibrary::LineTraceSingle(GetWorld(), _start, _end, ETraceTypeQuery::TraceTypeQuery1, false, TArray<AActor*>(), EDrawDebugTrace::ForDuration, _hit, true);
	if (_res)
	{
		bool _isInteractable = _hit.GetActor()->Implements<UInteractable>();
		if (_isInteractable)
		{
			IInteractable* _interactableActor = Cast<IInteractable>(_hit.GetActor());
			_interactableActor->Interact();

			ABaseObject* _object = Cast<ABaseObject>(_hit.GetActor());
			if (_object)
			{
				handleComponent->GrabComponent(_hit.Component.Get(), NAME_None, _hit.Location, true);
				isGrabing = true;
			}
		}
	}
}

void APlayerPlateformer::LookInput(const FInputActionValue& Value)
{
	FVector2D _lookVector = Value.Get<FVector2D>();

	AddControllerYawInput(-_lookVector.X);
	AddControllerPitchInput(_lookVector.Y);
}
