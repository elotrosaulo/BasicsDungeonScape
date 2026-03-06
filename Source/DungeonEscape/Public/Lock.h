// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "TriggerComponent.h"
#include "Components/StaticMeshComponent.h"

#include "Lock.generated.h"

UCLASS()
class DUNGEONESCAPE_API ALock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* RootComp;	// We will attach everything else to this component

	UPROPERTY(VisibleAnywhere)
	UTriggerComponent* TriggerComp;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* KeyItemMesh;	// Item that we place into the lock (it will be invisible at the start, and when we place it into the lock, it'll be visible

	UPROPERTY(EditAnywhere)
	FString KeyItemName;

	void SetIsKeyPlaced(bool NewIsKeyPlaced);
	bool GetIsKeyPlaced();

private:
	UPROPERTY(VisibleAnywhere)
	bool IsKeyPlaced = false;
};
