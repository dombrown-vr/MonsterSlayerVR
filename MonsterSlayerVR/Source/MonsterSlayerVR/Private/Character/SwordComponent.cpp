// Fill out your copyright notice in the Description page of Project Settings.

#include "SwordComponent.h"




USwordComponent::USwordComponent()
{
	auto SwordMesh = ConstructorHelpers::FObjectFinder<USkeletalMesh>(TEXT("SkeletalMesh'/Game/Meshes/SK_Sword.SK_Sword'"));
	if (!ensure(SwordMesh.Succeeded())) { return; }
	SetSkeletalMesh(SwordMesh.Object);
}