// Fill out your copyright notice in the Description page of Project Settings.

#include "BarghestCharacter.h"


// Sets default values
ABarghestCharacter::ABarghestCharacter()
{

	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AIControllerClass = ABarghestAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorld;

	// TODO Move animation code to dedicated AnimationHandler class
	TriggerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Trigger Capsule"));
	TriggerCapsule->InitCapsuleSize(120.f, 100.f);
	TriggerCapsule->SetCollisionProfileName(TEXT("Trigger"));
	TriggerCapsule->SetupAttachment(RootComponent);
 	
	TriggerCapsule->OnComponentBeginOverlap.AddDynamic(this, &ABarghestCharacter::OnOverlapBegin);
	TriggerCapsule->OnComponentEndOverlap.AddDynamic(this, &ABarghestCharacter::OnOverlapEnd);

	auto MeshFinder = ConstructorHelpers::FObjectFinder<USkeletalMesh>(TEXT("SkeletalMesh'/Game/Monsters/Barghest/Meshes/SK_BARGHEST.SK_BARGHEST'"));
	if(MeshFinder.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshFinder.Object);
		GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -95.f));
		GetMesh()->SetRelativeRotation(FRotator(0.f, 90.f, 0.f));
	}
	AnimHandler = CreateDefaultSubobject<UBarghestAnimHandler>("Anim Handler");
	AnimHandler->SetMeshComponent(GetMesh());
}

// Called when the game starts or when spawned
void ABarghestCharacter::BeginPlay()
{
	Super::BeginPlay();

	
	CurrentHealth = MaxHealth;
}

// Called every frame
void ABarghestCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Direction;
	float Length;
	GetVelocity().ToDirectionAndLength(Direction, Length);

	if (OverlappingPlayerPawn)
	{
		AnimHandler->SetAnimationState(EBarghestAnimState::Attacking);
	}
	else 
	{
		if (Length > 0)
		{
			AnimHandler->SetAnimationState(EBarghestAnimState::Running);
		}
		else if (Length == 0)
		{
			AnimHandler->SetAnimationState(EBarghestAnimState::Idle);
		}
	}
	
}

// Called to bind functionality to input
void ABarghestCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABarghestCharacter::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor == GetPlayerPawn() && OtherActor)
	{
		OverlappingPlayerPawn = true;
	}
}

void ABarghestCharacter::OnOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == GetPlayerPawn() && OtherActor)
	{
		OverlappingPlayerPawn = false;
	}
}
APawn* ABarghestCharacter::GetPlayerPawn() const
{
	if (!GetWorld()->GetFirstPlayerController()) { return nullptr; }
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	return PlayerPawn;
	
}
