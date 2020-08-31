// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveablePlatform.h"
#include "Components/MoveByPointsComponent.h"
#include "Engine/CollisionProfile.h"

AMoveablePlatform::AMoveablePlatform() {
	PrimaryActorTick.bCanEverTick = true;
	SetMobility(EComponentMobility::Movable);

	MoveByPointsComponent = CreateDefaultSubobject<UMoveByPointsComponent>("MoveByPointsComponent");
	MoveByPointsComponent->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	MoveByPointsComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

void AMoveablePlatform::BeginPlay() {
	Super::BeginPlay();

	if (HasAuthority()) {
		SetReplicates(true);
		SetReplicateMovement(true);
		MoveByPointsComponent->StartMovement(0);
	}
}