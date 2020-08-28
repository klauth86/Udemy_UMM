// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveablePlatform.h"

AMoveablePlatform::AMoveablePlatform() {
	PrimaryActorTick.bCanEverTick = true;
	SetMobility(EComponentMobility::Movable);
}

void AMoveablePlatform::BeginPlay() {
	Super::BeginPlay();

	if (HasAuthority()) 
	{
		SetReplicates(true);
		SetReplicateMovement(true);
	}
}

void AMoveablePlatform::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
	if (HasAuthority())
		SetActorLocation(DeltaSeconds * Velocity + GetActorLocation());
}