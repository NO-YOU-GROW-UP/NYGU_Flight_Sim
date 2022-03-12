// Copyright NO YOU GROW UP LLC All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlaneMovementComponent.h"
#include "GameFramework/Character.h"
#include "APlanePawn.generated.h"

UCLASS()
class NYGU_FLIGHT_SIM_API APlanePawn : public APawn
{
	GENERATED_BODY()
public:
	// Sets default values for this pawn's properties
	APlanePawn();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/* Plane Meshes Body Glass Ailerons Flaps and Rudder */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Plane, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* PlaneBodyMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Plane, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Glass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Plane, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* LeftAileron;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Plane, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* RightAileron;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Plane, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* LeftElevator;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Plane, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* RightElevator;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Plane, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* LeftRudder;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Plane, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* RightRudder;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Plane, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* LeftFlaps;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Plane, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* RightFlaps;

protected:

	/*Camera Boom Behind Plane*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/*Third Person Camera*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* ThirdPersonCamera;

	/*Plane Movement Component*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UPlaneMovementComponent* PlaneMovementComponent;

};
