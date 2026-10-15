// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Explosive.generated.h"

class UStaticMeshComponent;
class UBoxComponent;
class UFieldSystemComponent;

/// <summary>
/// An explosive that explode when activated/hited
/// </summary>
UCLASS()
class PROJECT2_API AExplosive : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess))
	TObjectPtr<UStaticMeshComponent> meshComponent = nullptr;	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess))
	TObjectPtr<UBoxComponent> boxComponent = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess))
	TObjectPtr<UFieldSystemComponent> fieldComponent = nullptr;

	// The explosion's power
	UPROPERTY(EditAnywhere, Category = "Variable", meta = (ClampMin = 10, ClampMax = 10000))
	int power = 100;
	// The explosion's radius
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Variable", meta = (ClampMin = 10, ClampMax = 1000))
	int radius = 100;

public:	
	AExplosive();

protected:
	void BeginPlay() override;
	void Tick(float DeltaTime) override;
	bool ShouldTickIfViewportsOnly() const override;

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* _overlappedComponent, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIndex, bool _bFromSweep, const FHitResult& _sweepResult);
};
