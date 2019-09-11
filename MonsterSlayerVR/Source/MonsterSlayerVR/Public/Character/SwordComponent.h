// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "ConstructorHelpers.h"
#include "BarghestCharacter.h"
#include "SwordComponent.generated.h"

/**
 * 
 */
UCLASS()
class MONSTERSLAYERVR_API USwordComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()
public:
	USwordComponent();
	
	void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
};
