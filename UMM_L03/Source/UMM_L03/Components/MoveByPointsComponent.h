// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PrimitiveComponent.h"
#include "Components/MoveByPointsProxy.h"
#include "MoveByPointsComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UMM_L03_API UMoveByPointsComponent : public UPrimitiveComponent {

	GENERATED_BODY()

public:	

	static void Draw(FPrimitiveDrawInterface* PDI, const FSceneView* View, UMoveByPointsComponent* component, const FMatrix& LocalToWorld, const FLinearColor& LineColor, uint8 DepthPriorityGroup);

	UMoveByPointsComponent();

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	void StartMovement(int32 currentIndex);

#if !UE_BUILD_SHIPPING
	//~ Begin UPrimitiveComponent Interface.
	virtual FPrimitiveSceneProxy* CreateSceneProxy() override { return nullptr; }
	//~ End UPrimitiveComponent Interface.
#endif

protected:

	UPROPERTY(EditAnywhere, Category = "AMoveablePlatform")
		bool ThereAndBackAgain;

	UPROPERTY(EditAnywhere, Category = "AMoveablePlatform")
		TArray<FVector> Points;

	UPROPERTY(EditAnywhere, Category = "AMoveablePlatform")
		TArray<float> Times;

	float TimeLeft;

	int32 CurrentIndex = INDEX_NONE;

	int32 DeltaIndex = 1;
};
