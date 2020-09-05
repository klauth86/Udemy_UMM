// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveByPointsComponent.h"
#include "MoveByPointsProxy.h"

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
		//UE_LOG(LogTemp, Warning, TEXT("%s"), *location.ToString());
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

void UMoveByPointsComponent::Draw(FPrimitiveDrawInterface* PDI, const FSceneView* View, UMoveByPointsComponent* component, const FMatrix& LocalToWorld, const FLinearColor& LineColor, uint8 DepthPriorityGroup) {
	const int32 GrabHandleSize = 6;
	FVector OldKeyPos(0);

	const int32 NumPoints = component->Points.Num();

	for (int32 i = 0; i < NumPoints; i++) {
		PDI->DrawPoint(component->Points[i], LineColor, GrabHandleSize, DepthPriorityGroup);
	}
}

#if !UE_BUILD_SHIPPING
//~ Begin UPrimitiveComponent Interface.
FPrimitiveSceneProxy* UMoveByPointsComponent::CreateSceneProxy() { return new FMoveByPointsProxy(this); }
//~ End UPrimitiveComponent Interface.
#endif