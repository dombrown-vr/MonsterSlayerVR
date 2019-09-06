// Fill out your copyright notice in the Description page of Project Settings.

#include "SwordComponent.h"




USwordComponent::USwordComponent()
{
	auto SwordMesh = ConstructorHelpers::FObjectFinder<USkeletalMesh>(TEXT("SkeletalMesh'/Game/Meshes/SK_Sword.SK_Sword'"));
	if (!ensure(SwordMesh.Succeeded())) { return; }
	SetSkeletalMesh(SwordMesh.Object);

	SetGenerateOverlapEvents(true);
	SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	
	
}

void USwordComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{


}

bool USwordComponent::ComponentOverlapMultiImpl(TArray<struct FOverlapResult>& OutOverlaps, const UWorld * InWorld, const FVector & Pos, const FQuat & Rot, ECollisionChannel TestChannel, const FComponentQueryParams & Params, const FCollisionObjectQueryParams & ObjectQueryParams) const
{
	UE_LOG(LogTemp, Warning, TEXT("OVERLAP"));

	return false;
}
