// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Platefrom.generated.h"

class UStaticMeshComponent;

/// <summary>
/// A plateform moving between 2 location
/// </summary>
UCLASS()
class PROJECT2_API APlateform : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess))
	TObjectPtr<UStaticMeshComponent> meshComponent = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess))
	TObjectPtr<USceneComponent> startOffsetComponent = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess))
	TObjectPtr<USceneComponent> endOffsetComponent = nullptr;

	// The moving speed
	UPROPERTY(EditAnywhere, Category = "Variable", meta = (ClampMin = 1, ClampMax = 10))
	int moveSpeed = 4;
	// Can loop between location
	UPROPERTY(EditAnywhere, Category = "Variable")
	bool loop = false;

	FVector startOffsetLocation;
	FVector endOffsetLocation;
	FVector destination;
	bool changeState = false;
	bool atStart = true;

public:
	APlateform();

	UFUNCTION(BlueprintCallable)
	void ChangeState();

protected:
	void BeginPlay() override;
	void Tick(float DeltaTime) override;
	bool ShouldTickIfViewportsOnly() const override;

	void MovePlateform(const float _deltaTime);
};
