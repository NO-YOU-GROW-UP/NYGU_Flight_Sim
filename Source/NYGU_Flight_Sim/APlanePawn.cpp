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

	LeftAileron = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftAileron"));
	LeftAileron->SetupAttachment(PlaneBodyMesh,FName("aileronL"));
	RightAileron = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightAileron"));
	RightAileron->SetupAttachment(PlaneBodyMesh, FName("aileronR"));



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

