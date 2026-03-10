// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();

	/*
	POINTERS:
	float MyFloat = 10.0f;
	float* FloatPtr = &MyFloat;
	
	float Result = *FloatPtr + 5.0f; // This should be 10 + 5 = 15
	UE_LOG(LogTemp, Display, TEXT("Result is %f"), Result);

	*FloatPtr = 30.0f;
	UE_LOG(LogTemp, Display, TEXT("MyFloat is %f"), MyFloat);
	UE_LOG(LogTemp, Display, TEXT("*FLoatPtr is %f"), *FloatPtr);

	UE_LOG(LogTemp, Display, TEXT("&MyFloat is %p"), &MyFloat);
	UE_LOG(LogTemp, Display, TEXT("FLoatPtr is %p"), FloatPtr);

	// -- 
	FVector MyVector = FVector(1.0f, 1.0f, 1.0f);
	FVector* MyVectorPtr = &MyVector;

	(*MyVectorPtr).X = 5.0f; // This is the old version to do this
	MyVectorPtr->Y = 6.0f;	 // This is more standard
	MyVectorPtr->Z = 7.0f;

	UE_LOG(LogTemp, Display, TEXT("MyVector params are %s"), *MyVectorPtr->ToCompactString());
	*/

	//AActor* MyOwner = GetOwner();
	//UE_LOG(LogTemp, Display, TEXT("%s is at location %s"), *GetOwner()->GetActorNameOrLabel(), *StartLocation.ToCompactString());

	StartLocation = GetOwner()->GetActorLocation();
	SetShouldMove(false);
}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector CurrentLocation = GetOwner()->GetActorLocation();
	ReachedTarget = CurrentLocation.Equals(TargetLocation);

	if (!ReachedTarget)
	{
		float Speed = MoveOffset.Length() / MoveTime;	// Speed = Distance / Time.    Length() give us the magnitude of the Vector.
		FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);

		GetOwner()->SetActorLocation(NewLocation);

		//UE_LOG(LogTemp, Display, TEXT("Mover is moving"));
	}
}

bool UMover::GetShouldMove()
{
	return ShouldMove;
}

void UMover::SetShouldMove(bool NewShouldMove)
{
	ShouldMove = NewShouldMove;

	if (ShouldMove)
	{
		// Target Location is start location + move offset	
		TargetLocation = StartLocation + MoveOffset;
	}
	else
	{
		// Target Location is start location
		TargetLocation = StartLocation;
	}
}
