// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/SkeletalMeshActor.h"
#include "ConstructorHelpers.h"
#include "Materials/Material.h"
#include "Animation/BlendSpace1D.h"
#include "Animation/AnimSingleNodeInstance.h"
#include "BarghestSkeletalMeshActor.generated.h"

/**
 * 
 */
UCLASS()
class MONSTERSLAYERVR_API ABarghestSkeletalMeshActor : public ASkeletalMeshActor
{
	GENERATED_BODY()

public:
	ABarghestSkeletalMeshActor();
	
	void BeginPlay() override;

private:
	UPROPERTY()
		class UBlendSpace1D* MovementBlendSpace = nullptr;
};
