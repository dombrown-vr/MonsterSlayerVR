// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/BlendSpace1D.h"
#include "Animation/AnimSingleNodeInstance.h"
#include "BarghestAnimHandler.generated.h"


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

	void SetAnimation(UBlendSpace1D* BlendSpaceToSet);

	void SetSpeed(float Speed);

private:
	UPROPERTY()
		USkeletalMeshComponent* Mesh = nullptr;

	UPROPERTY()
		UBlendSpace1D* Animation = nullptr; // TODO Make this more general
	
};
