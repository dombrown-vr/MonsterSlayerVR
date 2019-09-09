// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/BlendSpace1D.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimSingleNodeInstance.h"
#include "ConstructorHelpers.h"
#include "BarghestAnimHandler.generated.h"


UENUM()
enum class EBarghestAnimState : uint8
{
	Idle,
	Running,
	Attacking,
	Dieing
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MONSTERSLAYERVR_API UBarghestAnimHandler : public UActorComponent
{
	GENERATED_BODY()

public:	


	// Sets default values for this component's properties
	UBarghestAnimHandler();



protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetMeshComponent(USkeletalMeshComponent* MeshToSet);

	void SetAnimationState(EBarghestAnimState NewState);

private:


	UPROPERTY(VisibleAnywhere)
		USkeletalMeshComponent* Mesh = nullptr;

	UPROPERTY(VisibleAnywhere)
		UAnimMontage* AnimMontage = nullptr;

	UPROPERTY(VisibleAnywhere)
		UBlendSpace1D* MovementAnim = nullptr; // TODO Make this more general
	
	EBarghestAnimState AnimState = EBarghestAnimState::Idle;

	
};
