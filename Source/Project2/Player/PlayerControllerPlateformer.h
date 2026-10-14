// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerControllerPlateformer.generated.h"

class UInputMappingContext;

UCLASS()
class PROJECT2_API APlayerControllerPlateformer : public APlayerController
{
	GENERATED_BODY()
	
protected:
	/** Input Mapping Contexts */
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> inputMapping = nullptr;

protected:
	virtual void SetupInputComponent() override;
};
