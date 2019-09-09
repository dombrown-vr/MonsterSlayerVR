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
		MovementAnim = MovementBlendSpaceFinder.Object;
	
	auto AnimMontageFinder = ConstructorHelpers::FObjectFinder<UAnimMontage>(TEXT("AnimMontage'/Game/Monsters/Barghest/Animations/BARGHEST_MONTAGE.BARGHEST_MONTAGE'"));
	if (ensure(AnimMontageFinder.Succeeded()))
		AnimMontage = AnimMontageFinder.Object;

	// ...
}


// Called when the game starts
void UBarghestAnimHandler::BeginPlay()
{
	Super::BeginPlay();
	Mesh->PlayAnimation(MovementAnim, true);
	
}


// Called every frame
void UBarghestAnimHandler::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UBarghestAnimHandler::SetMeshComponent(USkeletalMeshComponent* MeshToSet)
{
	Mesh = MeshToSet;
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
		auto AnimInstance = Mesh->GetAnimInstance();
		if (!ensure(AnimInstance)) { return; }
		AnimInstance->Montage_Play(AnimMontage);
		//AnimInstance->Montage_JumpToSection(FName(""))
		//FVector BlendParams(50.f, 0.f, 0.f);
		//Mesh->GetSingleNodeInstance()->SetBlendSpaceInput(BlendParams);
	}
}


	

