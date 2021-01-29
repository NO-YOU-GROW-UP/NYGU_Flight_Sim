// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "APlanePawn.generated.h"

UCLASS()
class NYGU_FLIGHT_SIM_API AAPlanePawn : public APawn
{
	GENERATED_BODY()
	
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

	/**********************************************************************************************/



	/*Camera Boom Behind Plane*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/*Third Person Camera*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* ThirdPersonCamera;

public:
	// Sets default values for this pawn's properties
	AAPlanePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
