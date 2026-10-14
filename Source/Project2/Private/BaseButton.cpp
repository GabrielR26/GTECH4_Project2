// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseButton.h"
#include "Activable.h"

// Sets default values
ABaseButton::ABaseButton()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseButton::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseButton::Interact()
{
	onButtonPressed.Broadcast();
	for (AActor* _actor : activableObjects)
	{
		if (!_actor)
			continue;
		IActivable* _activable = Cast<IActivable>(_actor);
		if (!_activable)
			continue;

		_activable->Activate();
	}
}