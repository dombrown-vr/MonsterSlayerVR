// Fill out your copyright notice in the Description page of Project Settings.

#include "BarghestAnimHandler.h"


// Sets default values for this component's properties
UBarghestAnimHandler::UBarghestAnimHandler()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	

	// ...
}


// Called when the game starts
void UBarghestAnimHandler::BeginPlay()
{
	Super::BeginPlay();
	Mesh->PlayAnimation(Animation, true);
	FVector BlendParams(0.f, 0.f, 0.f);
	Mesh->GetSingleNodeInstance()->SetBlendSpaceInput(BlendParams);
	
}


// Called every frame
void UBarghestAnimHandler::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UBarghestAnimHandler::SetMeshComponent(USkeletalMeshComponent* MeshToSet)
{
	Mesh = MeshToSet;
}

void UBarghestAnimHandler::SetAnimation(UBlendSpace1D* BlendSpaceToSet)
{
	Animation = BlendSpaceToSet;
}

void UBarghestAnimHandler::SetSpeed(float Speed)
{
}
