// Fill out your copyright notice in the Description page of Project Settings.


#include "VRPlayerPawn.h"

// Sets default values
AVRPlayerPawn::AVRPlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//MotionControllerRegistry();

	auto RootScene = CreateDefaultSubobject<USceneComponent>(FName("PawnRoot"));
	RootComponent = RootScene;
	UE_LOG(LogTemp, Warning, TEXT("Pawn Root Component = %s"), *RootComponent->GetName());
	LeftControllerComponent = CreateDefaultSubobject<UMotionControllerComponent>(FName("Motion L"));
	LeftControllerComponent->SetupAttachment(RootComponent);
	RightControllerComponent = CreateDefaultSubobject<UMotionControllerComponent>(FName("Motion R"));
	RightControllerComponent->SetupAttachment(RootComponent);

	LeftControllerComponent->SetTrackingSource(EControllerHand::Left);
	RightControllerComponent->SetTrackingSource(EControllerHand::Right);

	LeftContMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(FName("Left Mesh"));

	auto LeftMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Meshes/LeftTouchController.LeftTouchController'"));

	LeftContMeshComp->SetStaticMesh(LeftMesh.Object);
	LeftContMeshComp->SetupAttachment(LeftControllerComponent);
}

AVRPlayerPawn::~AVRPlayerPawn()
{
	// Unregister controller
	if (Controller)
		IModularFeatures::Get().UnregisterModularFeature(IMotionController::GetModularFeatureName(), Controller);
}

// Called when the game starts or when spawned
void AVRPlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	UHeadMountedDisplayFunctionLibrary::EnableHMD(true);
	UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(EHMDTrackingOrigin::Eye);
	
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

void AVRPlayerPawn::MotionControllerRegistry()
{
	// Look for available motion controllers
	auto AvailableControllers = IModularFeatures::Get().GetModularFeatureImplementations<IMotionController>(IMotionController::GetModularFeatureName());
	if ((AvailableControllers.Num() == 0))
	{
		UE_LOG(LogTemp, Warning, TEXT("No Motion Controllers Found"));
		return;
	}

	FName Oculus("OculusInputDevice");

	for (auto Cont : AvailableControllers)
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
	if (!Controller)
	{
		UE_LOG(LogTemp, Error, TEXT("Unable to find %s"), *Oculus.ToString());
	}
	// Register controller
	if (Controller)
		IModularFeatures::Get().RegisterModularFeature(IMotionController::GetModularFeatureName(), Controller);
}

