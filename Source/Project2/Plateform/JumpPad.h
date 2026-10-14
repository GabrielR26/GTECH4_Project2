// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JumpPad.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

/// <summary>
/// A pad that launch the player in showing direction
/// </summary>
UCLASS()
class PROJECT2_API AJumpPad : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess))
	TObjectPtr<UStaticMeshComponent> padComponent = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess))
	TObjectPtr<UBoxComponent> boxComponent = nullptr;

	// Force apply to launch the player
	UPROPERTY(EditAnywhere, Category = "Variable", meta = (ClampMin = 300, ClampMax = 1500))
	int launchForce = 500;
	
public:	
	AJumpPad();

protected:
	void BeginPlay() override;

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* _overlappedComponent, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIndex, bool _bFromSweep, const FHitResult& _sweepResult);
};
