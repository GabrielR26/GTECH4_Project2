// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "BaseObject.generated.h"

UCLASS()
class PROJECT2_API ABaseObject : public AActor, public IInteractable
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* mesh = nullptr;
	
public:	
	ABaseObject();
	void Interact();
	void SetLocation(FVector _newLocation);
	void SimulatePhysics(bool _simulate)
	{
		if (!mesh)
			return;
		mesh->SetSimulatePhysics(_simulate);
	}

private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
