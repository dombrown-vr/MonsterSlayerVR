// Fill out your copyright notice in the Description page of Project Settings.

#include "BarghestCharacter.h"


// Sets default values
ABarghestCharacter::ABarghestCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AIControllerClass = ABarghestAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorld;
	auto Mesh = ConstructorHelpers::FObjectFinder<USkeletalMesh>(TEXT("SkeletalMesh'/Game/Monsters/Barghest/Meshes/SK_BARGHEST.SK_BARGHEST'"));
	if(Mesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(Mesh.Object);
		GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -95.f));
		GetMesh()->SetRelativeRotation(FRotator(0.f, 90.f, 0.f));
	}
	
}

// Called when the game starts or when spawned
void ABarghestCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABarghestCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABarghestCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

