// Copyright NO YOU GROW UP LLC All Rights Reserved.

#include "PlaneMovementComponent.h"
#include "APlanePawn.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UPlaneMovementComponent::UPlaneMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
}

// Called when the game starts
void UPlaneMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentForwardThrust = StartingThrottlePercentage * MaxThrust;
	ProjectedThrust = CurrentForwardThrust;
	PlanePawn = GetOwner<APlanePawn>();
}

void UPlaneMovementComponent::HandleImpact(const FHitResult& Hit, float TimeSlice /*= 0.f*/, const FVector& MoveDelta /*= FVector::ZeroVector*/)
{
	if (Hit.IsValidBlockingHit() && bSimulatePhysicsOnImpact)
	{
		//For now just start physics sim on crash
		if (PlanePawn->PlaneBodyMesh && PlanePawn->PlaneBodyMesh->IsSimulatingPhysics() == false)
		{
			PlanePawn->PlaneBodyMesh->SetSimulatePhysics(true);
		}
	}
}

void UPlaneMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateLocation(DeltaTime);
}

/*Updates Planes location with physics to be called every frame*/
void UPlaneMovementComponent::UpdateLocation(float DeltaTime)
{	
	if(PhysicsMode == Realistic)
	{
		//Add Thrust Force
		CurrentVelocity += GetForwardThrust(DeltaTime);

		//Add Drag Force
		CurrentVelocity += GetDragForce(DeltaTime);
	}
	else if (PhysicsMode == Basic) 
	{
		//Add Thrust Force
		CurrentVelocity = GetForwardThrust(DeltaTime);
	}

	//Add Gravity Force
	CurrentVelocity += GetGravityForce(DeltaTime);

	//Add Lift Force
	CurrentVelocity += GetLiftForce(DeltaTime);

	//limit fastest velocity to max thrust
	CurrentSpeed = CurrentVelocity.Size();
	if (CurrentSpeed > MaxThrust) 
	{ 
		//Decrease velocity to max thrust speed
		CurrentVelocity *= MaxThrust / CurrentSpeed;
	}

	CurrentVelocity *= WorldUnitMultiplier;

	FHitResult Hit;
	SafeMoveUpdatedComponent(CurrentVelocity, UpdatedComponent->GetComponentQuat(), true, Hit);
	if (Hit.bBlockingHit)
	{
		HandleImpact(Hit); //apply damage possibly here
		SlideAlongSurface(CurrentVelocity, 1.f, Hit.Normal, Hit, true);
	}	
}

/************************Physics***************************/
FVector UPlaneMovementComponent::GetForwardThrust(float DeltaTime)
{
	CurrentForwardThrust = FMath::FInterpTo(CurrentForwardThrust, ProjectedThrust, DeltaTime, ThrustInterpSpeed);
	return DeltaTime * CurrentForwardThrust * GetOwner()->GetActorForwardVector();
}

FVector UPlaneMovementComponent::GetDragForce(float DeltaTime)
{
	//find the amount of forward velocity based on current velocity
	FVector ActorForwardVector = GetOwner()->GetActorForwardVector();
	float velocity = FVector::DotProduct(CurrentVelocity, ActorForwardVector);
	
	//Drag force equation and convert to acceleration
	velocity = ((AirDensity * velocity * velocity * 0.5) * ForwardDragArea * Drag) / PlaneMass;
	 
	return ( ActorForwardVector * -1.f) * velocity * DeltaTime;
}

FVector UPlaneMovementComponent::GetGravityForce(float DeltaTime)
{
	return FVector(0.f,0.f, -1.f * Gravity * DeltaTime);
}

FVector UPlaneMovementComponent::GetLiftForce(float DeltaTime)
{
	float LiftForce = 0.f;
	
	if (PhysicsMode == Realistic) 
	{
		FVector ActorForwardVector = GetOwner()->GetActorForwardVector();
		float ForwardVelocity = FVector::DotProduct(CurrentVelocity, ActorForwardVector);

		//lift force equation
		LiftForce = Lift * (AirDensity * ForwardVelocity * ForwardVelocity * 0.5) * WingArea;

		//convert to acceleration
		LiftForce /= PlaneMass;

		LiftForce = FMath::Clamp<float>(LiftForce, 0, Gravity);
	}
	else if (PhysicsMode == Basic)
	{
		LiftForce = FMath::Clamp<float>((CurrentForwardThrust / EqualLiftSpeed), 0, 1) * Gravity;
	}
	
	return FVector(0,0,LiftForce*DeltaTime);
}

//Add change throttle up or down with input axis
void UPlaneMovementComponent::AddThrottleInput(float ThrottleAxisInput)
{
	//avoid divide by 0
	if (MaxThrust == 0.f) MaxThrust = 1.f;
	
	//axis input -1 to 1 multiplied by the amount of speed change per second
	float ChangeInThrust = ThrottleAxisInput * ThrottleMultiplier * GetWorld()->GetDeltaSeconds();

	ProjectedThrust = FMath::Clamp<float>(ProjectedThrust + ChangeInThrust, 0, MaxThrust);
	ThrottlePercentage = ProjectedThrust / MaxThrust;
}

//Set throttle percent of total max speed
void UPlaneMovementComponent::SetThrottlePercent(float ThrottlePercent)
{
	ThrottlePercentage = FMath::Clamp<float>(ThrottlePercent, 0.f, 1.f);
	ProjectedThrust = MaxThrust * ThrottlePercent;
}

void UPlaneMovementComponent::AddPitchInput(float PitchAxisInput)
{
	CurrentPitch = FMath::FInterpTo(CurrentPitch, PitchAxisInput, GetWorld()->DeltaTimeSeconds, PitchInterpSpeed);

	float AdjustedPitchSpeed = PitchSpeed;

	FRotator NewRotation = FRotator(CurrentPitch * AdjustedPitchSpeed * GetWorld()->DeltaTimeSeconds,0,0);

	FHitResult Hit;
	GetOwner()->AddActorLocalRotation(FQuat(NewRotation), true, &Hit);

	if (Hit.bBlockingHit)
	{
		HandleImpact(Hit); //apply damage possibly here
		SlideAlongSurface(CurrentVelocity, 1.f, Hit.Normal, Hit, true);
	}
}

void UPlaneMovementComponent::AddRollInput(float RollAxisInput)
{
	CurrentRoll = FMath::FInterpTo(CurrentRoll, RollAxisInput, GetWorld()->DeltaTimeSeconds, RollInterpSpeed);

	float AdjustedRollSpeed = RollSpeed;

	FRotator NewRotation = FRotator(0,0,CurrentRoll * AdjustedRollSpeed * GetWorld()->DeltaTimeSeconds);

	FHitResult Hit;
	GetOwner()->AddActorLocalRotation(FQuat(NewRotation), true, &Hit);

	if (Hit.bBlockingHit)
	{
		HandleImpact(Hit); //apply damage possibly here
		SlideAlongSurface(CurrentVelocity, 1.f, Hit.Normal, Hit, true);
	}
}

void UPlaneMovementComponent::AddYawInput(float YawAxisInput)
{
	CurrentYaw = FMath::FInterpTo(CurrentYaw, YawAxisInput, GetWorld()->DeltaTimeSeconds, YawInterpSpeed);

	FRotator NewRotation = FRotator(0,CurrentYaw * YawSpeed * GetWorld()->DeltaTimeSeconds, 0);

	GetOwner()->AddActorLocalRotation(FQuat(NewRotation), true);
}