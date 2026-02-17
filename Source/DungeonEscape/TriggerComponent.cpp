// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

// Constructor:
UTriggerComponent::UTriggerComponent()
{
	// Activate the call to TickComponent every frame:
	PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

	if (MoverActor)	// The same as if(MoverActor != nullptr), so checking if the address is not 'zero'
	{
		Mover = MoverActor->FindComponentByClass<UMover>();	// Similar to GetComponent<T>() in Unity

		if (Mover)	// The same as if(Mover != nullptr), so checking if the address is not 'zero'
		{
			UE_LOG(LogTemp, Display, TEXT("Succesfully found the Mover component"));
		}
		else
		{
			UE_LOG(LogTemp, Display, TEXT("Failed to find the Mover component"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("MoveActor is nullptr"));
	}

	if (IsPressurePlate)
	{
		OnComponentBeginOverlap.AddDynamic(this, &UTriggerComponent::OnOverlapBegin);
		OnComponentEndOverlap.AddDynamic(this, &UTriggerComponent::OnOverlapEnd);
	}
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTriggerComponent::Trigger(bool NewTriggerValue)
{
	IsTriggered = NewTriggerValue;
	
	if (Mover)	// The same as if(Mover != nullptr), so checking if the address is not 'zero'
	{
		Mover->SetShouldMove(IsTriggered);
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("%s doesn't have a Mover to trigger!"), *GetOwner()->GetActorNameOrLabel());
	}
}

void UTriggerComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->ActorHasTag("PressurePlateActivator"))
	{
		ActivatorCount++;

		if (!IsTriggered)
		{
			Trigger(true);
		}
	}
}

void UTriggerComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor->ActorHasTag("PressurePlateActivator"))
	{
		ActivatorCount--;

		if (IsTriggered && ActivatorCount == 0)
		{
			Trigger(false);
		}
	}
}
