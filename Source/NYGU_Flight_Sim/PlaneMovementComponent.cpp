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
	ThrottleMultiplier = 2500.f;
	ProjectedThrust = 0;
	CurrentForwardThrust = 0;
	MaxThrust = 5000;
	EqualLiftSpeed = 3000;

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
	CurrentForwardThrust = FMath::FInterpTo(CurrentForwardThrust, ProjectedThrust, DeltaTime, Drag);

	//Add Thrust Force
	FVector Move =  DeltaTime * CurrentForwardThrust*GetOwner()->GetActorForwardVector();

	//Add Gravity Force
	Move += GetGravityForce(DeltaTime);

	//Add Lift Force
	Move += GetLiftForce(DeltaTime);

	//change location
	GetOwner()->AddActorWorldOffset(Move,true);
}


//Add change throttle up or down with input axis
void UPlaneMovementComponent::AddThrottleInput(float ThrottleAxisInput)
{
	//axis input -1 to 1 multiplied by the amount of speed change per second
	float ChangeInThrust = ThrottleAxisInput * ThrottleMultiplier * GetWorld()->GetDeltaSeconds();
 
	ProjectedThrust = FMath::Clamp<float>(ProjectedThrust + ChangeInThrust, 0, MaxThrust);
	ThrottlePercentage = ProjectedThrust / MaxThrust;
}

//Set throttle percent of total max speed
void UPlaneMovementComponent::SetThrottlePercent(float ThrottlePercent)
{

	ThrottlePercentage = FMath::Clamp<float>(ThrottlePercent, 0, 1);

	ProjectedThrust = MaxThrust * ThrottlePercent;

}

void UPlaneMovementComponent::AddPitchInput(float PitchAxisInput)
{
	CurrentPitch = FMath::FInterpTo(CurrentPitch, PitchAxisInput, GetWorld()->DeltaTimeSeconds,PitchSpeed);
	GetOwner()->AddActorLocalRotation(FQuat(FRotator(0,0,CurrentPitch*PitchSpeed*GetWorld()->DeltaTimeSeconds)), true);
}


/************************Physics***************************/

FVector UPlaneMovementComponent::GetGravityForce(float DeltaTime)
{
	return FVector(0,0, -1 * Gravity * DeltaTime);
}

FVector UPlaneMovementComponent::GetLiftForce(float DeltaTime)
{
	float Lift = FMath::Clamp<float>((CurrentForwardThrust / EqualLiftSpeed), 0, 1) * Gravity * DeltaTime;
	
	return FVector(0,0,Lift);
}



//UE_LOG(LogTemp, Warning, TEXT("The float value is: %f"), GetWorld()->GetDeltaSeconds());
//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, FString::Printf(TEXT("%f"), GetWorld()->TimeSeconds));