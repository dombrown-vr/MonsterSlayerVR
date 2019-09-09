// Fill out your copyright notice in the Description page of Project Settings.

#include "BarghestAnimHandler.h"


// Sets default values for this component's properties
UBarghestAnimHandler::UBarghestAnimHandler()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	auto MovementBlendSpaceFinder = ConstructorHelpers::FObjectFinder<UBlendSpace1D>(TEXT("BlendSpace1D'/Game/Monsters/Barghest/Animations/BARGHEST_Skeleton_BlendSpace1D.BARGHEST_Skeleton_BlendSpace1D'"));
	if (ensure(MovementBlendSpaceFinder.Succeeded()))
		SetAnimation(MovementBlendSpaceFinder.Object);
	

	// ...
}


// Called when the game starts
void UBarghestAnimHandler::BeginPlay()
{
	Super::BeginPlay();
	Mesh->PlayAnimation(Animation, true);
	Animation->
	
}


// Called every frame
void UBarghestAnimHandler::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// TODO Update the blendspace to reflect this state machine implementation

	
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

void UBarghestAnimHandler::SetAnimationState(EBarghestAnimState NewState)
{
	AnimState = NewState;

	if (AnimState == EBarghestAnimState::Idle)
	{
		FVector BlendParams(0.f, 0.f, 0.f);
		Mesh->GetSingleNodeInstance()->SetBlendSpaceInput(BlendParams);
	}
	else if (AnimState == EBarghestAnimState::Running)
	{
		FVector BlendParams(25.f, 0.f, 0.f);
		Mesh->GetSingleNodeInstance()->SetBlendSpaceInput(BlendParams);
	}
	else if (AnimState == EBarghestAnimState::Attacking)
	{
		FVector BlendParams(50.f, 0.f, 0.f);
		Mesh->GetSingleNodeInstance()->SetBlendSpaceInput(BlendParams);
	}
}


	

