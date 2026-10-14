// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bumper.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

/// <summary>
/// A bumper that repulse object
/// </summary>
UCLASS()
class PROJECT2_API ABumper : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess))
	TObjectPtr<UStaticMeshComponent> meshComponent = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess))
	TObjectPtr<UBoxComponent> boxComponent = nullptr;

	// The impulse power
	UPROPERTY(EditAnywhere, Category = "Variable", meta = (ClampMin = 100, ClampMax = 10000))
	int power = 100;

public:	
	ABumper();

protected:
	void BeginPlay() override;

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* _overlappedComponent, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIndex, bool _bFromSweep, const FHitResult& _sweepResult);
};
