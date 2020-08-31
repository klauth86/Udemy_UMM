// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveByPointsComponent.h"

// Sets default values for this component's properties
UMoveByPointsComponent::UMoveByPointsComponent() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	SetComponentTickEnabled(false);
	// ...
}

void UMoveByPointsComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CurrentIndex == INDEX_NONE) {
		SetComponentTickEnabled(false);
		return;
	}

	auto target = Points[CurrentIndex];
	TimeLeft -= DeltaTime;

	if (TimeLeft <= 0) {
		auto nextIndex = CurrentIndex + DeltaIndex;

		auto finishMovement = nextIndex >= Points.Num() - 1 || nextIndex <= 0;
		if (finishMovement) {
			DeltaIndex = -DeltaIndex;
		}

		if (finishMovement && !ThereAndBackAgain) {
			StartMovement(INDEX_NONE);
		}
		else {
			StartMovement(nextIndex);
		}
	}
	else {
		auto location = FMath::Lerp(Points[CurrentIndex], Points[CurrentIndex + DeltaIndex], 1 - TimeLeft / Times[CurrentIndex]);
		GetOwner()->SetActorLocation(location);
		UE_LOG(LogTemp, Warning, TEXT("%s"), *location.ToString());
	}
}

void UMoveByPointsComponent::StartMovement(int32 currentIndex) {

	SetComponentTickEnabled(false);

	if (CurrentIndex != currentIndex) {
		CurrentIndex = currentIndex;
		if (CurrentIndex != INDEX_NONE) {
			TimeLeft = DeltaIndex > 0 ? Times[CurrentIndex] : Times[CurrentIndex - 1];
		}
	}

	if (CurrentIndex != INDEX_NONE) {
		SetComponentTickEnabled(true);
	}
}