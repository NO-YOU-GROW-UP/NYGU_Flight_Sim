// Fill out your copyright notice in the Description page of Project Settings.


#include "PlaneMovementComponent.h"



// Sets default values for this component's properties
UPlaneMovementComponent::UPlaneMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	/*Setup Physics Variables Defaults*/
	Gravity = 981.f;
	Drag = 0.25f;
	ProjectedThrust = 0;
	CurrentForwardThrust = 0;
	MaxThrust = 5000;
	EqualLiftSpeed = 3000;


	/*Plane Control Variable Defaults*/
	ThrottleMultiplier = 2500.f;
	ThrustInterpSpeed = 0.25f;
	PitchSpeed = 100.f;
	PitchInterpSpeed = 1.f;
	RollSpeed = 100.f;
	RollInterpSpeed = 1.f;
	YawSpeed = 100.f;
	YawInterpSpeed = 1.f;
	// ...
}




// Called when the game starts
void UPlaneMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentForwardThrust = ThrottlePercentage * MaxThrust;
	ProjectedThrust = CurrentForwardThrust;
	// ...
	
}


// Called every frame
void UPlaneMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	UpdateLocation(DeltaTime);
}

/*Updates Planes location with physics to be called every frame*/
void UPlaneMovementComponent::UpdateLocation(float DeltaTime)
{
	
	//interp from Current Speed To Projected
	

	//Add Thrust Force
	CurrentVelocity = GetForwardThrust(DeltaTime);

	//Add Drag Force
	//CurrentVelocity += GetDragForce(DeltaTime);

	//Add Gravity Force
	CurrentVelocity += GetGravityForce(DeltaTime);

	//Add Lift Force
	CurrentVelocity += GetLiftForce(DeltaTime);

	//change location
	GetOwner()->AddActorWorldOffset(CurrentVelocity,true);
}




/************************Physics***************************/

FVector UPlaneMovementComponent::GetForwardThrust(float DeltaTime)
{

	CurrentForwardThrust = FMath::FInterpTo(CurrentForwardThrust, ProjectedThrust, DeltaTime, ThrustInterpSpeed);
	return DeltaTime * CurrentForwardThrust * GetOwner()->GetActorForwardVector();

}

FVector UPlaneMovementComponent::GetDragForce(float DeltaTime)
{
	return (GetOwner()->GetActorForwardVector() * -1) * CurrentForwardThrust * DeltaTime;
}

FVector UPlaneMovementComponent::GetGravityForce(float DeltaTime)
{
	return FVector(0,0, -1 * Gravity * DeltaTime);
}

FVector UPlaneMovementComponent::GetLiftForce(float DeltaTime)
{
	float Lift = FMath::Clamp<float>((CurrentForwardThrust / EqualLiftSpeed), 0, 1) * Gravity * DeltaTime;
	
	return FVector(0,0,Lift);
}


/*****************PLANE CONTROL***********************/


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
	CurrentPitch = FMath::FInterpTo(CurrentPitch, PitchAxisInput, GetWorld()->DeltaTimeSeconds, PitchInterpSpeed);

	FRotator NewRotation = FRotator(CurrentPitch * PitchSpeed * GetWorld()->DeltaTimeSeconds,0,0);

	GetOwner()->AddActorLocalRotation(FQuat(NewRotation), true);

}

void UPlaneMovementComponent::AddRollInput(float RollAxisInput)
{
	CurrentRoll = FMath::FInterpTo(CurrentRoll, RollAxisInput, GetWorld()->DeltaTimeSeconds, RollInterpSpeed);

	FRotator NewRotation = FRotator(0,0,CurrentRoll * RollSpeed * GetWorld()->DeltaTimeSeconds);

	GetOwner()->AddActorLocalRotation(FQuat(NewRotation), true);
}

void UPlaneMovementComponent::AddYawInput(float YawAxisInput)
{
	CurrentYaw = FMath::FInterpTo(CurrentYaw, YawAxisInput, GetWorld()->DeltaTimeSeconds, YawInterpSpeed);

	FRotator NewRotation = FRotator(0,CurrentYaw * YawSpeed * GetWorld()->DeltaTimeSeconds, 0);

	GetOwner()->AddActorLocalRotation(FQuat(NewRotation), true);

}