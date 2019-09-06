// Fill out your copyright notice in the Description page of Project Settings.


#include "VRPlayerPawn.h"

// Sets default values
AVRPlayerPawn::AVRPlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//MotionControllerRegistry();
	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	auto RootScene = CreateDefaultSubobject<USceneComponent>(FName("PawnRoot"));
	RootComponent = RootScene;
	// Weird bug with Oculus spawning player too high up - temporary fix
	RootComponent->SetWorldLocation(FVector(0.f, 0.f, -70.f));

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(FName("Player Camera"));
	CameraComponent->SetupAttachment(RootComponent);
	

	LeftControllerComponent = CreateDefaultSubobject<UMotionControllerComponent>(FName("Motion L"));
	LeftControllerComponent->SetupAttachment(RootComponent);
	RightControllerComponent = CreateDefaultSubobject<UMotionControllerComponent>(FName("Motion R"));
	RightControllerComponent->SetupAttachment(RootComponent);

	LeftControllerComponent->SetTrackingSource(EControllerHand::Left);
	RightControllerComponent->SetTrackingSource(EControllerHand::Right);

	

	SwordComponent = CreateDefaultSubobject<USwordComponent>(FName("Sword"));
	SwordComponent->SetupAttachment(LeftControllerComponent, FName("rootGrip"));

	ShieldComponent = CreateDefaultSubobject<UShieldComponent>(FName("Shield"));
	ShieldComponent->SetupAttachment(RightControllerComponent, FName("rootGrip"));


	//ShieldComponent->SetWorldLocation(FVector(0.f, 5.f, 0.f));
}

AVRPlayerPawn::~AVRPlayerPawn()
{
	// Unregister controller
	//if (Controller)
	//	IModularFeatures::Get().UnregisterModularFeature(IMotionController::GetModularFeatureName(), Controller);
}

// Called when the game starts or when spawned
void AVRPlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	UHeadMountedDisplayFunctionLibrary::EnableHMD(true);
	UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(EHMDTrackingOrigin::Floor);

	SwordComponent->SetWorldRotation(FRotator(160.f, 0.f, 0.f)); // Hard-coded values that are appropriate for left handed use
	ShieldComponent->SetWorldRotation(FRotator(180.f, 0.f, 0.f)); // TODO make this change based on player's hand preference
	
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

