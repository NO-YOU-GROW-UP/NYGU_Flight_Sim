// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Math/UnrealMathUtility.h"
#include "PlaneMovementComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NYGU_FLIGHT_SIM_API UPlaneMovementComponent : public UActorComponent
{
	GENERATED_BODY()

		/** Gravity 981 Default */
		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Physics, meta = (AllowPrivateAccess = "true"))
		float Gravity;
	    
		/*Drag Multiplier Between 0 and 1 */
	    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Physics, meta = (AllowPrivateAccess = "true"))
		float Drag;
		
		/*Current forward thrust of Plane can set above 0 to start in the air*/
		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Physics, meta = (AllowPrivateAccess = "true"))
		float CurrentSpeed;
		
		/*Speed Plane is attempting to reach based on throttle setting Current speed will change to this*/
		UPROPERTY(BlueprintReadOnly, Category = Physics, meta = (AllowPrivateAccess = "true"))
		float ProjectedSpeed;

		/*Max speed the plane can attempt to go*/
		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Physics, meta = (AllowPrivateAccess = "true"))
		float MaxSpeed;

		/*Throttle Percentage 0 to 1*/
		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Physics, meta = (AllowPrivateAccess = "true"))
		float ThrottlePercentage;

		/*How Fast the throttle will change the speed over 1 second*/
		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Physics, meta = (AllowPrivateAccess = "true"))
		float ThrottleMultiplier;

		/*How Fast the throttle will change the speed over 1 second*/
		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Physics, meta = (AllowPrivateAccess = "true"))
		float EqualLiftSpeed;


		UFUNCTION()
		FVector GetGravityForce(float DeltaTime);

		
		UFUNCTION()
		FVector GetLiftForce(float DeltaTime);


		UFUNCTION()
		void UpdateLocation(float DeltaTime);

public:	
	// Sets default values for this component's properties
	UPlaneMovementComponent();

	/*Add axis input to change forward thrust -1 to 1 float input*/
	UFUNCTION(BlueprintCallable, Category = "Throttle")
	void AddThrottleInput(float ThrottleAxisInput);

	/*Set Throttle to Specific percentage float between 0 and 1*/
	UFUNCTION(BlueprintCallable, Category = "Throttle")
	void SetThrottlePercent(float ThrottlePercent);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
