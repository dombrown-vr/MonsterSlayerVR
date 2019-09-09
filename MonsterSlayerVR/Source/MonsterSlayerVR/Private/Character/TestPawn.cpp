// Fill out your copyright notice in the Description page of Project Settings.

#include "TestPawn.h"


// Sets default values
ATestPawn::ATestPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USphereComponent* Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Root Component"));
	Sphere->InitSphereRadius(40.f);
	Sphere->SetCollisionProfileName(TEXT("Pawn"));
	RootComponent = Sphere;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);

	auto Sword = CreateDefaultSubobject<USwordComponent>(TEXT("Sword"));

	Sword->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	Sword->SetWorldRotation(FRotator(90.f, 0.f, 0.f));
	Sword->SetWorldLocation(FVector(100.f, 0.f, 0.f));
}

// Called when the game starts or when spawned
void ATestPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += MouseInput.X;
	NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch + MouseInput.Y,-80.f,+80.f);
	SetActorRotation(NewRotation);
}

// Called to bind functionality to input
void ATestPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MouseYaw", this, &ATestPawn::MouseYaw);
	PlayerInputComponent->BindAxis("MousePitch", this, &ATestPawn::MousePitch);

	PlayerInputComponent->BindAxis("MoveForward", this, &ATestPawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATestPawn::MoveRight);
}

void ATestPawn::MousePitch(float axis)
{
	MouseInput.Y = axis;
}

void ATestPawn::MouseYaw(float axis)
{
	MouseInput.X = axis;
}

void ATestPawn::MoveForward(float axis)
{
	PawnMovement.X = axis;
}

void ATestPawn::MoveRight(float axis)
{
	PawnMovement.Y = axis;
}

