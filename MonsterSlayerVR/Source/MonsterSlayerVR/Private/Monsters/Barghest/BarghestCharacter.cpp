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
	if (ensure(AnimFinder.Succeeded()))
		Montage = AnimFinder.Object;

	auto AnimBlueprintFinder = ConstructorHelpers::FClassFinder<UBarghestAnimInstance>(TEXT("AnimBlueprint'/Game/QuadrapedCreatures/Barghest/Meshes/Barghest_BP'"));
	if(ensure(AnimBlueprintFinder.Succeeded()))
		GetMesh()->SetAnimInstanceClass(AnimBlueprintFinder.Class);

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

	// Work out movement speed for movement animation
	FVector Direction;
	float Length;
	GetVelocity().ToDirectionAndLength(Direction, Length);
	Length = Length * DeltaTime * 10.f;
	auto Anim = Cast<UBarghestAnimInstance>(GetMesh()->GetAnimInstance());
	if (!ensure(Anim)) { return; }
	Anim->SetSpeed(Length);

	if (GetPlayerPawn())
		Attack(GetPlayerPawn());

	
}

// Called to bind functionality to input
void ABarghestCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABarghestCharacter::Attack(AActor* ActorToAttack)
{
	auto ThisAttackTime = FPlatformTime::Seconds();
	if ((ThisAttackTime > TimeLastAttacked + AttackTimeDelay) && OverlappingPlayerPawn)
	{
		TimeLastAttacked = ThisAttackTime;
		PlayAnimMontage(Montage, 1.f, FName("bite_start"));
	}
	
}

void ABarghestCharacter::HitBySword()
{
	PlayAnimMontage(Montage, 1.f, FName("hit_start"));
	TimeLastAttacked = FPlatformTime::Seconds(); // Player attack disrupts monster's attacks
}

void ABarghestCharacter::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("overlap with %s on component %s"), *OtherActor->GetName(), *OtherComp->GetName());
	// Check that we are overlapping with the player pawn's collision capsule
	if (OtherActor == GetPlayerPawn() && Cast<UCapsuleComponent>(OtherComp))
	{
		OverlappingPlayerPawn = true;
	}
}

void ABarghestCharacter::OnOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	// Check that we are overlapping with the player pawn's collision capsule
	if (OtherActor == GetPlayerPawn() && Cast<UCapsuleComponent>(OtherComp))
	{
		OverlappingPlayerPawn = false;
	}
}

void ABarghestCharacter::OnCompHit(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Hit"));
}

APawn* ABarghestCharacter::GetPlayerPawn() const
{
	if (!GetWorld()->GetFirstPlayerController()) { return nullptr; }
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	return PlayerPawn;
	
}
