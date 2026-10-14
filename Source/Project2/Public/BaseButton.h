// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "BaseButton.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonPressed);
UCLASS()
class PROJECT2_API ABaseButton : public AActor, public IInteractable
{
	GENERATED_BODY()

	FOnButtonPressed onButtonPressed;
	
public:	
	ABaseButton();
	void Interact() override;
	FOnButtonPressed& OnButtonPressed() { return onButtonPressed; }

private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
