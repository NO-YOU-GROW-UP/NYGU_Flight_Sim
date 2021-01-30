// Fill out your copyright notice in the Description page of Project Settings.


#include "PlaneMovementComponent.h"



// Sets default values for this component's properties
UPlaneMovementComponent::UPlaneMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	/*Setup Physics Values*/
	Gravity = 981.f;
	Drag = 0.25f;
	ThrustMultiplier = 2500.f;
	ProjectedSpeed = 0;
	CurrentSpeed = 0;

	// ...
}


// Called when the game starts
void UPlaneMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPlaneMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	UpdateLocation(DeltaTime);
}

void UPlaneMovementComponent::UpdateLocation(float DeltaTime)
{
	
	//interp from Current Speed To Projected
	CurrentSpeed = FMath::FInterpTo(CurrentSpeed, ProjectedSpeed, DeltaTime, Drag);

	FVector Move =  DeltaTime * CurrentSpeed*GetOwner()->GetActorForwardVector();
	GetOwner()->AddActorWorldOffset(Move,true);
}

//UE_LOG(LogTemp, Warning, TEXT("The float value is: %f"), GetWorld()->GetDeltaSeconds());
//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, FString::Printf(TEXT("%f"), GetWorld()->TimeSeconds));