// Fill out your copyright notice in the Description page of Project Settings.

#include "SwordComponent.h"




USwordComponent::USwordComponent()
{
	auto SwordMesh = ConstructorHelpers::FObjectFinder<USkeletalMesh>(TEXT("SkeletalMesh'/Game/Meshes/SK_Sword.SK_Sword'"));
	if (!ensure(SwordMesh.Succeeded())) { return; }
	SetSkeletalMesh(SwordMesh.Object);

	SetGenerateOverlapEvents(true);
	SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	SetNotifyRigidBodyCollision(true);
	
	OnComponentBeginOverlap.AddDynamic(this, &USwordComponent::OnOverlapBegin);
}

void USwordComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{


}

void USwordComponent::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

}


