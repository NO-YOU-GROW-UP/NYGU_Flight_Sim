// Fill out your copyright notice in the Description page of Project Settings.


#include "APlanePawn.h"

// Sets default values
AAPlanePawn::AAPlanePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

