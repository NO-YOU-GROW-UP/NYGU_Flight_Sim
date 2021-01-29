// Fill out your copyright notice in the Description page of Project Settings.


#include "APlanePawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
// Sets default values
AAPlanePawn::AAPlanePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	/*Plane Mesh Body Setup*/
	PlaneBodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlaneBody"));
	PlaneBodyMesh->SetupAttachment(RootComponent);
	
	/*Glass Setup*/
	Glass = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Glass"));
	Glass->SetupAttachment(PlaneBodyMesh);
	

	/*Ailerons Setup*/
	LeftAileron = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftAileron"));
	LeftAileron->SetupAttachment(PlaneBodyMesh,FName("aileronL"));
	RightAileron = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightAileron"));
	RightAileron->SetupAttachment(PlaneBodyMesh, FName("aileronR"));

	/*Flaps Setup*/
	LeftFlaps = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftFlaps"));
	LeftFlaps->SetupAttachment(PlaneBodyMesh, FName("flapsL"));
	RightFlaps = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightFlaps"));
	RightFlaps->SetupAttachment(PlaneBodyMesh, FName("flapsR"));


	/*Elevator Setup*/
	LeftElevator = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftElevator"));
	LeftElevator->SetupAttachment(PlaneBodyMesh, FName("elevatorL"));
	RightElevator = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightElevator"));
	RightElevator->SetupAttachment(PlaneBodyMesh, FName("elevatorR"));



	/*Rudder Setup*/
	LeftRudder = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftRudder"));
	LeftRudder->SetupAttachment(PlaneBodyMesh, FName("rudderL"));
	RightRudder = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightRudder"));
	RightRudder->SetupAttachment(PlaneBodyMesh, FName("rudderR"));






	/*Camera Boom Setup*/
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CamaraBoom"));
	CameraBoom->SetupAttachment(PlaneBodyMesh);
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SocketOffset = FVector(0.f, 0.f, 300);
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->bEnableCameraRotationLag = true;


	/*Third Person Camera Setup*/
	ThirdPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdPersonCamera"));
	ThirdPersonCamera->SetupAttachment(CameraBoom);
	ThirdPersonCamera->bUsePawnControlRotation = false;
	
	




}

// Called when the game starts or when spawned
void AAPlanePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAPlanePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAPlanePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

