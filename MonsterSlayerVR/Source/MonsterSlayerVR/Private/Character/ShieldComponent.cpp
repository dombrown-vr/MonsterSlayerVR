// Fill out your copyright notice in the Description page of Project Settings.

#include "ShieldComponent.h"


UShieldComponent::UShieldComponent()
{
	auto Mesh = ConstructorHelpers::FObjectFinder<USkeletalMesh>(TEXT("SkeletalMesh'/Game/Meshes/SK_Shield.SK_Shield'"));
	if (!ensure(Mesh.Succeeded())) { return; }
	SetSkeletalMesh(Mesh.Object);

//	GripLocation = Mesh.Object->FindSocket(FName(TEXT("rootGrip")))->GetSocketLocation(this);
}

FVector UShieldComponent::GetRelativeHandleLocation() const
{
	return GripLocation;
}