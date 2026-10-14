// Fill out your copyright notice in the Description page of Project Settings.

#include "Explosive.h"
#include "Components/BoxComponent.h"
#include "Field/FieldSystemComponent.h"
#include "Kismet/KismetSystemLibrary.h"

AExplosive::AExplosive()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create the mesh component	
	meshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = meshComponent;
	// Create the box component	
	boxComponent = CreateDefaultSubobject<UBoxComponent>("Box");
	boxComponent->SetupAttachment(RootComponent);
	// Create the field component	
	fieldComponent = CreateDefaultSubobject<UFieldSystemComponent>("Field");
	fieldComponent->SetupAttachment(RootComponent);
}

void AExplosive::BeginPlay()
{
	Super::BeginPlay();

	if (boxComponent)
		boxComponent->OnComponentBeginOverlap.AddDynamic(this, &AExplosive::BeginOverlap);
}

void AExplosive::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Draw debug explosion radius
	if (!GetWorld()->IsGameWorld())
	{
		UKismetSystemLibrary::DrawDebugSphere(GetWorld(), GetActorLocation(), radius, 10, FLinearColor::Red, 0.f, 1.f);
		return;
	}
}

bool AExplosive::ShouldTickIfViewportsOnly() const
{
	return true;
}

void AExplosive::BeginOverlap(UPrimitiveComponent* _overlappedComponent, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIndex, bool _bFromSweep, const FHitResult& _sweepResult)
{
	// TODO how to explode ?

	fieldComponent->ApplyStrainField(true, GetActorLocation(), radius, power * 100, 1);
	fieldComponent->ApplyRadialVectorFalloffForce(true, GetActorLocation(), radius, power);
	fieldComponent->ApplyRadialForce(true, GetActorLocation(), power * 100);

	Destroy();
}