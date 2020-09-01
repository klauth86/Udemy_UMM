#pragma once

#include "PrimitiveSceneProxy.h"
#include "MoveByPointsComponent.h"

class FMoveByPointsProxy final : public FPrimitiveSceneProxy {
public:
	SIZE_T GetTypeHash() const override {
		static size_t UniquePointer;
		return reinterpret_cast<size_t>(&UniquePointer);
	}

	FMoveByPointsProxy(UMoveByPointsComponent* component)
		: FPrimitiveSceneProxy(component)
#if WITH_EDITORONLY_DATA
		, LineColor(FLinearColor::Red)
#else
		, LineColor(FLinearColor::White)
#endif
		, Component(component)
	{}

	virtual void GetDynamicMeshElements(const TArray<const FSceneView*>& Views, const FSceneViewFamily& ViewFamily, uint32 VisibilityMap, FMeshElementCollector& Collector) const override {
		QUICK_SCOPE_CYCLE_COUNTER(STAT_SplineSceneProxy_GetDynamicMeshElements);

		if (IsSelected()) {
			return;
		}

		for (int32 ViewIndex = 0; ViewIndex < Views.Num(); ViewIndex++) {
			if (VisibilityMap & (1 << ViewIndex)) {
				const FSceneView* View = Views[ViewIndex];
				FPrimitiveDrawInterface* PDI = Collector.GetPDI(ViewIndex);

				const FMatrix& LocalToWorld = GetLocalToWorld();

				// Taking into account the min and maximum drawing distance
				const float DistanceSqr = (View->ViewMatrices.GetViewOrigin() - LocalToWorld.GetOrigin()).SizeSquared();
				if (DistanceSqr < FMath::Square(GetMinDrawDistance()) || DistanceSqr > FMath::Square(GetMaxDrawDistance())) {
					continue;
				}

				UMoveByPointsComponent::Draw(PDI, View, Component, LocalToWorld, LineColor, SDPG_World);
			}
		}
	}

	virtual FPrimitiveViewRelevance GetViewRelevance(const FSceneView* View) const override {
		FPrimitiveViewRelevance Result;
		Result.bDrawRelevance = true && !IsSelected() && IsShown(View) && View->Family->EngineShowFlags.Splines;
		Result.bDynamicRelevance = true;
		Result.bShadowRelevance = IsShadowCast(View);
		Result.bEditorPrimitiveRelevance = UseEditorCompositing(View);
		return Result;
	}

	virtual uint32 GetMemoryFootprint(void) const override { return sizeof *this + GetAllocatedSize(); }
	uint32 GetAllocatedSize(void) const { return FPrimitiveSceneProxy::GetAllocatedSize(); }

private:

	FLinearColor LineColor;

	UMoveByPointsComponent* Component;
};