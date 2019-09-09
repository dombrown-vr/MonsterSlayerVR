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

	auto AnimFinder = ConstructorHelpers::FObjectFinder<UAnimMontage>(TEXT("AnimMontage'/Game/Monsters/Barghest/Animations/BARGHEST_MONTAGE.BARGHEST_MONTAGE'"));
	if (AnimFinder.Succeeded())
		Montage = AnimFinder.Object;

	auto AnimBlueprintFinder = ConstructorHelpers::FObjectFinder<UAnimBlueprint>(TEXT("AnimBlueprint'/Game/QuadrapedCreatures/Barghest/Meshes/Barghest_BP.Barghest_BP'"));
	GetMesh()->SetAnimInstanceClass(AnimBlueprintFinder.Object->GeneratedClass);
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
	Length = Length / 6.f;
	auto Anim = Cast<UBarghestAnimInstance>(GetMesh()->GetAnimInstance());
	if (!ensure(Anim)) { return; }
	Anim->SetSpeed(Length);
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
		PlayAnimMontage(Montage, 1.f, FName("bite_start"));
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
