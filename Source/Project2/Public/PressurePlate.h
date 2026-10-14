// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Activable.h>
#include <Components/BoxComponent.h>
#include "PressurePlate.generated.h"

UCLASS()
class PROJECT2_API APressurePlate : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* mesh = nullptr;

	UPROPERTY(EditAnywhere)
	UBoxComponent* box = nullptr;

	UPROPERTY(EditAnywhere)
	TArray<AActor*> activableObjects;
	
	UPROPERTY(EditAnywhere)
	float pressOffset = 0;

	FVector beginLocation;
	int objectOnPlate = 0;
	
public:	
	APressurePlate();
	bool IsPressed() { return objectOnPlate > 0; }

private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void InitEvent();
	void InitBeginLocation();

	void PressPlate();
	void AllObjectsBehaviour();

	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
