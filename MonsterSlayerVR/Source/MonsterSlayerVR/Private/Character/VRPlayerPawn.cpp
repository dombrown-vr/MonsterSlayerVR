// Fill out your copyright notice in the Description page of Project Settings.


#include "VRPlayerPawn.h"


// Sets default values
AVRPlayerPawn::AVRPlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	auto Controllers = IModularFeatures::Get().GetModularFeatureImplementations<IMotionController>(IMotionController::GetModularFeatureName());

	if ((Controllers.Num() == 0)) 
	{
		UE_LOG(LogTemp, Warning, TEXT("No Motion Controllers Found"));
		return;
	}

	FName Oculus("OculusInputDevice");

	for (auto Cont : Controllers)
	{
		// Find the Oculus input device
		if (Cont->GetMotionControllerDeviceTypeName() == Oculus)
		{
			Controller = Cont;
			UE_LOG(LogTemp, Warning, TEXT("Assigning Controller to %s"), *Cont->GetMotionControllerDeviceTypeName().ToString());
			
			// Get all source values and log to console (left hand, right hand etc.)
			TArray<FMotionControllerSource> Sources;
			Cont->EnumerateSources(Sources);
			for (auto Source : Sources)
			{
				UE_LOG(LogTemp, Warning, TEXT("Source Available: %s"), *Source.SourceName.ToString());
			}
		}		
	}

	if (Controller)
		IModularFeatures::Get().RegisterModularFeature(IMotionController::GetModularFeatureName(), Controller);
}

AVRPlayerPawn::~AVRPlayerPawn()
{
	if (Controller)
		IModularFeatures::Get().UnregisterModularFeature(IMotionController::GetModularFeatureName(), Controller);
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
	FRotator Orientation;
	FVector Location;
	if (Controller->GetControllerOrientationAndPosition(0, FName("Left"), Orientation, Location, 1.0f))
	{
		UE_LOG(LogTemp, Warning, TEXT("%s, %s"), *Orientation.ToString(), *Location.ToString());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not get controller orientation and position"));
	}
}

// Called to bind functionality to input
void AVRPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

