// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BalancedBoard.generated.h"

class UStaticMeshComponent;
class UPhysicsConstraintComponent;

/// <summary>
/// A board that balanced in side or another by physics interaction
/// </summary>
UCLASS()
class PROJECT2_API ABalancedBoard : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess))
	TObjectPtr<UStaticMeshComponent> baseComponent = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess))
	TObjectPtr<UStaticMeshComponent> boardComponent = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess))
	TObjectPtr<UPhysicsConstraintComponent> physicsConstraintsComponent = nullptr;

	// Enable or not the swing limit
	UPROPERTY(EditAnywhere, Category = "Variable")
	bool swingLimit = false;
	// The limit angle of the swing
	UPROPERTY(EditAnywhere, Category = "Variable", meta = (ClampMin = 0, ClampMax = 90))
	float swingLimitAngle = 45.f;
	
public:	
	ABalancedBoard();

protected:
	void BeginPlay() override;
};
