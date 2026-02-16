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
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
