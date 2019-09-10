// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BarghestAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class MONSTERSLAYERVR_API UBarghestAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:

	void SetSpeed(float SpeedToSet);

protected:
	UPROPERTY(BlueprintReadOnly, Category = Animation)
		float Speed = 0.f;
	
};
