// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/SphereComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "TestPawn.generated.h"

UCLASS()
class MONSTERSLAYERVR_API ATestPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATestPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MousePitch(float axis);
	void MouseYaw(float axis);

	void MoveForward(float axis);
	void MoveRight(float axis);

private:

	FVector2D MouseInput;
	FVector2D PawnMovement;
	UCameraComponent* Camera = nullptr;

	
};
