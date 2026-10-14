// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerPlateformer.generated.h"

class UInputComponent;
class UInputAction;
struct FInputActionValue;
class UCameraComponent;
class UBoxComponent;

UCLASS()
class PROJECT2_API APlayerPlateformer : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess))
	TObjectPtr<UCameraComponent> cameraComponent = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess))
	TObjectPtr<UBoxComponent> boxInteractionComponent = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess))
	TObjectPtr<USceneComponent> offsetInteractableComponent = nullptr;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> moveAction = nullptr;
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> jumpAction = nullptr;
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> interactAction = nullptr;
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> lookAction = nullptr;

	AActor* interactable = nullptr;

public:
	APlayerPlateformer();

protected:
	void BeginPlay() override;
	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* _overlappedComponent, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIndex, bool _bFromSweep, const FHitResult& _sweepResult);

	void MoveInput(const FInputActionValue& Value);
	void JumpStartInput();
	void JumpEndInput();
	void InteractInput();
	void LookInput(const FInputActionValue& Value);
};
