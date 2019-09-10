// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BarghestAIController.h"
#include "BarghestAnimInstance.h"
#include "ConstructorHelpers.h"
#include "BarghestAnimHandler.h"
#include "Components/CapsuleComponent.h"
#include "BarghestCharacter.generated.h"

UCLASS()
class MONSTERSLAYERVR_API ABarghestCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABarghestCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:

	UFUNCTION()
	void Attack(AActor* ActorToAttack);

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	APawn* GetPlayerPawn() const;

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
		void OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);


	UPROPERTY(VisibleAnywhere)
		UAnimMontage* Montage = nullptr;

	UPROPERTY(VisibleAnywhere)
		UCapsuleComponent* TriggerCapsule = nullptr;

	float MaxHealth = 100.f;

	float CurrentHealth;
	
	bool OverlappingPlayerPawn = false;

	double TimeLastAttacked = 0.0;

	double AttackTimeDelay = 1.5;
};
