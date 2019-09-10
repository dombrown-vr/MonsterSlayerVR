// Fill out your copyright notice in the Description page of Project Settings.

#include "BarghestAIController.h"




void ABarghestAIController::Tick(float DeltaTime)
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto Barghest = GetPawn();
	if (PlayerPawn && Barghest)
	{	
		auto BarghestLocation = Barghest->GetActorLocation();
		auto PlayerLocation = PlayerPawn->GetActorLocation();
		auto Difference = BarghestLocation - PlayerLocation;
		Difference = Difference.GetSafeNormal();
		auto Rotation = Difference.Rotation();
		Barghest->SetActorRotation(FRotator(0.f,Rotation.Yaw, 0.f));
		MoveToActor(PlayerPawn, 50.f,true,true,false);
	}
}