// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "ConstructorHelpers.h"
#include "ShieldComponent.generated.h"


/**
 * 
 */
UCLASS()
class MONSTERSLAYERVR_API UShieldComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()
public:
	UShieldComponent();
	
	FVector GetRelativeHandleLocation() const;
private:
	FVector GripLocation;
};
