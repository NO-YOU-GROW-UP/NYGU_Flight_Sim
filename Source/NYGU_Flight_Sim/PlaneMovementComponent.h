// copyright NO YOU GROW UP LLC

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Math/UnrealMathUtility.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlaneMovementComponent.generated.h"

UENUM()
enum EPlanePhysicsMode
{
	Realistic  UMETA(DisplayName = "Realistic"),
	Basic      UMETA(DisplayName = "Basic"),
};

class APlanePawn;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NYGU_FLIGHT_SIM_API UPlaneMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()

public:

	UPlaneMovementComponent();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void HandleImpact(const FHitResult& Hit, float TimeSlice = 0.f, const FVector& MoveDelta = FVector::ZeroVector)override;

	/*Add axis input to change forward thrust -1 to 1 float input*/
	UFUNCTION(BlueprintCallable, Category = PlaneControl)
	void AddThrottleInput(float ThrottleAxisInput);

	/*Set Throttle to Specific percentage float between 0 and 1*/
	UFUNCTION(BlueprintCallable, Category = PlaneControl)
	void SetThrottlePercent(float ThrottlePercent);

	/*Add axis input to change pitch -1 to 1 float input*/
	UFUNCTION(BlueprintCallable, Category = PlaneControl)
	void AddPitchInput(float PitchAxisInput);

	/*Add axis input to change roll -1 to 1 float input*/
	UFUNCTION(BlueprintCallable, Category = PlaneControl)
	void AddRollInput(float RollAxisInput);

	/*Add axis input to change yaw -1 to 1 float input*/
	UFUNCTION(BlueprintCallable, Category = PlaneControl)
	void AddYawInput(float YawAxisInput);

	/*Calculate Forward thrust vector applied*/
	UFUNCTION(BlueprintCallable, Category = "Physics")
	FVector GetForwardThrust(float DeltaTime);

	/*Calculate Drag vector to be applied*/
	UFUNCTION(BlueprintCallable, Category = "Physics")
	FVector GetDragForce(float DeltaTime);

	/*Calculate Gravity vector to be applied*/
	UFUNCTION(BlueprintCallable, Category = "Physics")
	FVector GetGravityForce(float DeltaTime);

	/*Calculate Lift vector to be applied*/
	UFUNCTION(BlueprintCallable, Category = "Physics")
	FVector GetLiftForce(float DeltaTime);


protected:

	/*Update Plane actor location in world*/
	UFUNCTION()
	virtual void UpdateLocation(float DeltaTime);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Physics, meta = (AllowPrivateAccess = "true"))
	TEnumAsByte<EPlanePhysicsMode> PhysicsMode = Realistic;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Physics, meta = (AllowPrivateAccess = "true"))
	bool bSimulatePhysicsOnImpact = true;

	/** Convert Simulation to game units decrease the unit to make game fit in game world */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Physics, meta = (AllowPrivateAccess = "true"))
	float WorldUnitMultiplier = 1.f;

	/** Mass in Kg of Plane */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Physics, meta = (AllowPrivateAccess = "true", ClampMin = "1", UIMin = "1"))
	float PlaneMass = 1000.f;
		
	/** Gravity 981 Default */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Physics, meta = (AllowPrivateAccess = "true"))
	float Gravity = 981.f;

	/** Air Density in kg/m^3 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Physics, meta = (AllowPrivateAccess = "true"))
	float AirDensity = 1.225f;

	/*Drag Coefficient Between 0 and 1 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Physics, meta = (AllowPrivateAccess = "true"))
	float Drag = 0.05f;

	/*Area of front of plane in M^2 to calculate drag force*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Physics, meta = (AllowPrivateAccess = "true"))
	float ForwardDragArea = 100.f;

	//Lift Coefficient Between 0 and 1 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Physics, meta = (AllowPrivateAccess = "true"))
	float Lift = 0.5f;

	//Lift Area of Wings */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Physics, meta = (AllowPrivateAccess = "true"))
	float WingArea = 46.f;

	/*Max speed the plane can attempt to go*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Physics, meta = (AllowPrivateAccess = "true"))
	float MaxThrust = 5000.f;

	/*Speed at which lift equals gravity*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Physics, meta = (AllowPrivateAccess = "true", ClampMin = "1", UIMin = "1"))
	float EqualLiftSpeed = 3000.f;

	/*Throttle Percentage 0 to 1*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Plane Control", meta = (AllowPrivateAccess = "true"))
	float StartingThrottlePercentage = 0.f;

	/*How Fast the throttle will change the speed over 1 second*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Plane Control", meta = (AllowPrivateAccess = "true"))
	float ThrottleMultiplier = 2500.f;
		
	/*How Fast the throttle will change the speed over 1 second*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Plane Control", meta = (AllowPrivateAccess = "true"))
	float ThrustInterpSpeed = 0.25f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Plane Control", meta = (AllowPrivateAccess = "true"))
	float MinSpeedToPitchAndRoll = 500.f;

	/*How quickly the plane can pitch*/
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Plane Control", meta = (AllowPrivateAccess = "true"))
	float PitchSpeed = 100.f;

	/*How quickly the plane can begin to pitch*/
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Plane Control", meta = (AllowPrivateAccess = "true"))
	float PitchInterpSpeed = 1.f;

	/*How quickly the plane can roll*/
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Plane Control", meta = (AllowPrivateAccess = "true"))
	float RollSpeed = 100.f;

	/*How quickly the plane can begin to roll*/
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Plane Control", meta = (AllowPrivateAccess = "true"))
	float RollInterpSpeed = 1.f;
		
	/*How quickly the plane can Yaw*/
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Plane Control", meta = (AllowPrivateAccess = "true"))
	float YawSpeed = 10.f;

	/*How quickly the plane can begin to Yaw*/
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Plane Control", meta = (AllowPrivateAccess = "true"))
	float YawInterpSpeed = 1.f;

	/*Throttle Percentage 0 to 1*/
	UPROPERTY(Transient, BlueprintReadOnly, Category = "Plane Control", meta = (AllowPrivateAccess = "true"))
	float ThrottlePercentage = 0.f;

	/*Speed Plane is attempting to reach based on throttle setting Current speed will change to this*/
	UPROPERTY(Transient, BlueprintReadOnly, Category = Physics, meta = (AllowPrivateAccess = "true"))
	float ProjectedThrust = 0.f;

	/*Current forward thrust of Plane can set above 0 to start in the air*/
	UPROPERTY(Transient, BlueprintReadOnly, Category = Physics, meta = (AllowPrivateAccess = "true"))
	float CurrentForwardThrust = 0.f;

	/*Current Velocity Vector including thrust gravity lift drag*/
	UPROPERTY(Transient, BlueprintReadOnly, Category = Physics, meta = (AllowPrivateAccess = "true"))
	FVector CurrentVelocity;

	UPROPERTY(Transient)
	float CurrentSpeed = 0.f;

	/*Current Yaw of the Plane*/
	UPROPERTY(Transient, BlueprintReadOnly, Category = "Plane Control", meta = (AllowPrivateAccess = "true"))
	float CurrentYaw = 0.f;

	/*Current Pitch of the Plane*/
	UPROPERTY(Transient, BlueprintReadOnly, Category = "Plane Control", meta = (AllowPrivateAccess = "true"))
	float CurrentPitch = 0.f;

	/*Current Roll of the Plane*/
	UPROPERTY(Transient, BlueprintReadOnly, Category = "Plane Control", meta = (AllowPrivateAccess = "true"))
	float CurrentRoll;

	UPROPERTY(Transient)
	APlanePawn* PlanePawn = nullptr;
		
};

