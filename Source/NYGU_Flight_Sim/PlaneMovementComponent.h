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



		/***********************Physics Variables**********************/

		/*Current Velocity Vector including thrust gravity lift drag*/
		UPROPERTY(BlueprintReadOnly, Category = Physics, meta = (AllowPrivateAccess = "true"))
		FVector CurrentVelocity;

		/** Gravity 981 Default */
		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Physics, meta = (AllowPrivateAccess = "true"))
		float Gravity;
	    
		/*Drag Multiplier Between 0 and 1 */
	    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Physics, meta = (AllowPrivateAccess = "true"))
		float Drag;
		
		/*Current forward thrust of Plane can set above 0 to start in the air*/
		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Physics, meta = (AllowPrivateAccess = "true"))
		float CurrentForwardThrust;

		/*Max speed the plane can attempt to go*/
		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Physics, meta = (AllowPrivateAccess = "true"))
		float MaxThrust;

		/*Speed Plane is attempting to reach based on throttle setting Current speed will change to this*/
		UPROPERTY(BlueprintReadOnly, Category = Physics, meta = (AllowPrivateAccess = "true"))
		float ProjectedThrust;
		

		/*Speed at which lift equals gravity*/
		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Physics, meta = (AllowPrivateAccess = "true"))
		float EqualLiftSpeed;

		

		/*How quickly the plane can pitch*/
		UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = Physics, meta = (AllowPrivateAccess = "true"))
		float PitchSpeed;
		
		/*Current Pitch of the Plane*/
		UPROPERTY(BlueprintReadOnly, Category = Physics, meta = (AllowPrivateAccess = "true"))
		float CurrentPitch;
		

		/**************Plane Mechanical Variables**********/

		/*Throttle Percentage 0 to 1*/
		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Plane, meta = (AllowPrivateAccess = "true"))
		float ThrottlePercentage;

		/*How Fast the throttle will change the speed over 1 second*/
		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Plane, meta = (AllowPrivateAccess = "true"))
		float ThrottleMultiplier;
		
		/*How Fast the throttle will change the speed over 1 second*/
		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Plane, meta = (AllowPrivateAccess = "true"))
		float ThrustInterpSpeed;
		
		
		/****Physics Functions******/


		/*Calculate Forward thrust vector applied*/
		UFUNCTION(BlueprintCallable, Category = "Physics")
		FVector GetForwardThrust(float DeltaTime);

		/*Calculate Gravity vector to being applied*/
		UFUNCTION(BlueprintCallable, Category = "Physics")
		FVector GetGravityForce(float DeltaTime);

		
		UFUNCTION(BlueprintCallable, Category = "Physics")
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

	/*Add axis input to change pitch -1 to 1 float input*/
	UFUNCTION(BlueprintCallable, Category = "Throttle")
	void AddPitchInput(float PitchAxisInput);


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
