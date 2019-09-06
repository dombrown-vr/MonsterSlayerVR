// Fill out your copyright notice in the Description page of Project Settings.

#include "VRPlayerPawn.h"


// Sets default values
AVRPlayerPawn::AVRPlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	UE_LOG(LogTemp, Warning, TEXT("VR Player Pawn Constructed"));
	auto Controllers = IModularFeatures::Get().GetModularFeatureImplementations<IMotionController>(IMotionController::GetModularFeatureName());
	if (!ensure(Controllers.Num() == 0)) 
	{
		UE_LOG(LogTemp, Warning, TEXT("No Motion Controllers Found"));
		return;
	}
	for (auto Controller : Controllers)
	{
		TArray<FMotionControllerSource> Sources;
		Controller->EnumerateSources(Sources);
		for (auto Source : Sources)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s"), *Source.SourceName.ToString());
		}

	}
}

// Called when the game starts or when spawned
void AVRPlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVRPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AVRPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

