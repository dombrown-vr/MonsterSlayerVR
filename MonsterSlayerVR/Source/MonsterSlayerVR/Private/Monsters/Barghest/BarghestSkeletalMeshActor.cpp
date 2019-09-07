// Fill out your copyright notice in the Description page of Project Settings.

#include "BarghestSkeletalMeshActor.h"



ABarghestSkeletalMeshActor::ABarghestSkeletalMeshActor()
{
	auto BarghestSkeleton = ConstructorHelpers::FObjectFinder<USkeletalMesh>(TEXT("SkeletalMesh'/Game/QuadrapedCreatures/Barghest/Meshes/SK_BARGHEST.SK_BARGHEST'"));
	if (ensure(BarghestSkeleton.Succeeded()))
		GetSkeletalMeshComponent()->SetSkeletalMesh(BarghestSkeleton.Object, true);
	

	auto MovementBlendSpaceFinder = ConstructorHelpers::FObjectFinder<UBlendSpace1D>(TEXT("BlendSpace1D'/Game/Monsters/Barghest/Animations/BARGHEST_Skeleton_BlendSpace1D.BARGHEST_Skeleton_BlendSpace1D'"));
	if (ensure(MovementBlendSpaceFinder.Succeeded()))
		MovementBlendSpace = MovementBlendSpaceFinder.Object;

}
void ABarghestSkeletalMeshActor::BeginPlay()
{
	Super::BeginPlay();

	auto Mesh = GetSkeletalMeshComponent();
	if (ensure(Mesh && MovementBlendSpace))
	{
		Mesh->PlayAnimation(MovementBlendSpace, true);
		FVector BlendParams(0.f, 0.f, 0.f);
		Mesh->GetSingleNodeInstance()->SetBlendSpaceInput(BlendParams);
	}

}