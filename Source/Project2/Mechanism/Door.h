// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

class UStaticMeshComponent;
class UPhysicsConstraintComponent;

/// <summary>
/// A double door/trap that can be opened by physics
/// </summary>
UCLASS()
class PROJECT2_API ADoor : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess))
	TObjectPtr<UStaticMeshComponent> door1Component = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess))
	TObjectPtr<UStaticMeshComponent> door2Component = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess))
	TObjectPtr<UPhysicsConstraintComponent> physicsConstraints0Component = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess))
	TObjectPtr<UPhysicsConstraintComponent> physicsConstraints1Component = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess))
	TObjectPtr<UPhysicsConstraintComponent> physicsConstraints2Component = nullptr;

	// Can be breakable by physics
	UPROPERTY(EditAnywhere, Category = "Variable")
	bool isBreakable = false;
	// Linear breakable treshold
	UPROPERTY(EditAnywhere, Category = "Variable", meta = (ClampMin = 500.f, ClampMax = 500000.f, EditCondition = isBreakable))
	float breakLimit = 2000.f;

public:
	ADoor();

	UFUNCTION(BlueprintCallable)
	void OpenDoor();

protected:
	void BeginPlay() override;
};
