// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveByPointsComponent.h"

// Sets default values for this component's properties
UMoveByPointsComponent::UMoveByPointsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UMoveByPointsComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


}

void UMoveByPointsComponent::StartMovement(int32 currentTarget) {

}