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
	ProjectedSpeed = 0;
	CurrentSpeed = 0;
	MaxSpeed = 5000;
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
	CurrentSpeed = FMath::FInterpTo(CurrentSpeed, ProjectedSpeed, DeltaTime, Drag);

	//Add Thrust Force
	FVector Move =  DeltaTime * CurrentSpeed*GetOwner()->GetActorForwardVector();

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
	float ChangeInSpeed = ThrottleAxisInput * ThrottleMultiplier * GetWorld()->GetDeltaSeconds();
 
	ProjectedSpeed = FMath::Clamp<float>(ProjectedSpeed + ChangeInSpeed, 0, MaxSpeed);
	ThrottlePercentage = ProjectedSpeed / MaxSpeed;
}

//Set throttle percent of total max speed
void UPlaneMovementComponent::SetThrottlePercent(float ThrottlePercent)
{

	ThrottlePercentage = FMath::Clamp<float>(ThrottlePercent, 0, 1);

	ProjectedSpeed = MaxSpeed * ThrottlePercent;

}



FVector UPlaneMovementComponent::GetGravityForce(float DeltaTime)
{
	return FVector(0,0, -1 * Gravity * DeltaTime);
}

FVector UPlaneMovementComponent::GetLiftForce(float DeltaTime)
{
	float Lift = FMath::Clamp<float>( (CurrentSpeed / EqualLiftSpeed) * Gravity * DeltaTime , 0 , 1);
	
	return FVector(0,0,Lift);
}



//UE_LOG(LogTemp, Warning, TEXT("The float value is: %f"), GetWorld()->GetDeltaSeconds());
//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, FString::Printf(TEXT("%f"), GetWorld()->TimeSeconds));