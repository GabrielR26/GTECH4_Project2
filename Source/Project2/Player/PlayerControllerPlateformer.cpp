// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerControllerPlateformer.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

void APlayerControllerPlateformer::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputLocalPlayerSubsystem* _subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	_subsystem->ClearAllMappings();
	_subsystem->AddMappingContext(inputMapping, 0);
}
