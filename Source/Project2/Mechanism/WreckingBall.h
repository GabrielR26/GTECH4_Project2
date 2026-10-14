// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WreckingBall.generated.h"

class UStaticMeshComponent;
class UCableComponent;
class UPhysicsConstraintComponent;

/// <summary>
/// A Wrecking ball to smash smt
/// </summary>
UCLASS()
class PROJECT2_API AWreckingBall : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess))
	TObjectPtr<UStaticMeshComponent> anchorComponent = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess))
	TObjectPtr<UStaticMeshComponent> ballComponent = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess))
	TObjectPtr<UCableComponent> cableComponent = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess))
	TObjectPtr<UPhysicsConstraintComponent> physicsConstraintsComponent = nullptr;

	// The distance between anchor and ball
	UPROPERTY(EditAnywhere, Category = "Variable", meta = (ClampMin = 100, ClampMax = 10000))
	int wreckingRadius = 1000;
	
public:	
	AWreckingBall();

	UFUNCTION(BlueprintCallable)
	void Activate();

protected:
	void BeginPlay() override;
	void Tick(float DeltaTime) override;
	bool ShouldTickIfViewportsOnly() const override;

#if WITH_EDITOR
	void PostEditChangeProperty(FPropertyChangedEvent& _propertyChangedEvent) override;
#endif
};
