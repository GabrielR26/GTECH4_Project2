// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/BoxComponent.h>
#include "TeleportationPipe.generated.h"

UCLASS()
class PROJECT2_API ATeleportationPipe : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* mesh = nullptr;

	UPROPERTY(EditAnywhere)
	UBoxComponent* box = nullptr;


	UPROPERTY(EditAnywhere, Category = "Teleport")
	ATeleportationPipe* destinationPipe = nullptr;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Teleport")
	FVector teleportOffset;
	
public:	
	ATeleportationPipe();
	UFUNCTION(BlueprintCallable)
	FVector GetTeleportLocation();

private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void InitEvent();

	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
