// Fill out your copyright notice in the Description page of Project Settings.

#include "BarghestPawn.h"


// Sets default values
ABarghestPawn::ABarghestPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABarghestPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABarghestPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABarghestPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

