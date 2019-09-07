// Fill out your copyright notice in the Description page of Project Settings.

#include "BarghestCharacter.h"


// Sets default values
ABarghestCharacter::ABarghestCharacter()
{
	// TODO Move animation code to dedicated AnimationHandler class
	TriggerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Trigger Capsule"));
	TriggerCapsule->InitCapsuleSize(150.f, 100.f);
	TriggerCapsule->SetCollisionProfileName(TEXT("Trigger"));
	TriggerCapsule->SetupAttachment(RootComponent);

	TriggerCapsule->OnComponentBeginOverlap.AddDynamic(this, &ABarghestCharacter::OnOverlapBegin);
	TriggerCapsule->OnComponentEndOverlap.AddDynamic(this, &ABarghestCharacter::OnOverlapEnd);

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AIControllerClass = ABarghestAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorld;
	auto MeshFinder = ConstructorHelpers::FObjectFinder<USkeletalMesh>(TEXT("SkeletalMesh'/Game/Monsters/Barghest/Meshes/SK_BARGHEST.SK_BARGHEST'"));
	if(MeshFinder.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshFinder.Object);
		GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -95.f));
		GetMesh()->SetRelativeRotation(FRotator(0.f, 90.f, 0.f));
	}
	
	auto MovementBlendSpaceFinder = ConstructorHelpers::FObjectFinder<UBlendSpace1D>(TEXT("BlendSpace1D'/Game/Monsters/Barghest/Animations/BARGHEST_Skeleton_BlendSpace1D.BARGHEST_Skeleton_BlendSpace1D'"));
	if (ensure(MovementBlendSpaceFinder.Succeeded()))
		MovementBlendSpace = MovementBlendSpaceFinder.Object;
}

// Called when the game starts or when spawned
void ABarghestCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetMesh()->PlayAnimation(MovementBlendSpace, true);
	FVector BlendParams(0.f, 0.f, 0.f);
	GetMesh()->GetSingleNodeInstance()->SetBlendSpaceInput(BlendParams);
	
}

// Called every frame
void ABarghestCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	FVector Direction;
	float Length;
	GetVelocity().ToDirectionAndLength(Direction, Length);
	Length = Length / 600.f; // 600 is top movement speed
	FVector BlendParams(Length*100.f, 0.f, 0.f);
	GetMesh()->GetSingleNodeInstance()->SetBlendSpaceInput(BlendParams);

	TArray<AActor*> OverlappingComponents;
	GetMesh()->GetOverlappingActors(OverlappingComponents);
	for (auto Comp : OverlappingComponents)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is overlapping with %s"), *GetName(), *Comp->GetName());
	}

}

// Called to bind functionality to input
void ABarghestCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


}

void ABarghestCharacter::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap Begin"));
}

void ABarghestCharacter::OnOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap End"));
}

