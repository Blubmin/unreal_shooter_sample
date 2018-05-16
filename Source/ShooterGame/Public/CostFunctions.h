#pragma once

#include <algorithm>

#include "ShooterTypes.h"
#include "Engine.h"
#include "Camera/CameraActor.h"
#include "Camera/CameraComponent.h"
#include "Player/ShooterCharacter.h"
#include "ThesisCameraActor.h"

struct OneThirdsCostFunction {
	FPerspectiveMatrix projection;
	AShooterCharacter* candidate;

	OneThirdsCostFunction(AThesisCameraActor* actor) : projection(0, 0, 0, 0) {
		FVector2D size;
		GEngine->GameViewport->GetViewportSize(size);
		projection = FPerspectiveMatrix(actor->GetCameraComponent()->FieldOfView / 2, size.X, size.Y, GEngine->NearClipPlane);
		candidate = actor->Target.Get()->GetTopCandidate();
	}

	void SetCandidate(AShooterCharacter* candidate) {
		this->candidate = candidate;
	}

	bool operator()(const double* const x, double* residual) const {
		if (candidate == nullptr) {
			return false;
		}

		FVector look_at_point = FTransform(FRotator(x[3], x[4], x[5])).TransformVector(FVector(1, 0, 0));
		FLookAtMatrix view(FVector(x[0], x[1], x[2]), look_at_point, FVector(0, 1, 0));

		TArray<FVector> positions;
		candidate->GetPositions(positions);

		FTransform pv(projection * view);

		FVector center(0, 0, 0);
		for (auto& position : positions) {
			center += pv.TransformVector(position);
		}
		center /= (double) positions.Num();
		FVector2D xy(center.X, center.Y);

		residual[0] = FVector2D::DistSquared(xy, FVector2D(-.33, -.33));
		residual[0] = std::min(residual[0], (double) FVector2D::DistSquared(xy, FVector2D(.33, -.33)));
		residual[0] = std::min(residual[0], (double) FVector2D::DistSquared(xy, FVector2D(.33, .33)));
		residual[0] = std::min(residual[0], (double) FVector2D::DistSquared(xy, FVector2D(-.33, .33)));

		return true;
	}
};

struct MovementCostFunction {
	FVector previousDisplacement;
	FVector targetPos;

	MovementCostFunction(AThesisCameraActor* actor) {
		if (actor->Target.Get() != nullptr)
			targetPos = actor->Target.Get()->GetActorLocation();
		FVector cameraPos = actor->GetActorLocation();
		previousDisplacement = cameraPos - targetPos;
	}

	bool operator()(const double* const x, double* residual) const {
		FVector newPos(x[0], x[1], x[2]);
		residual[0] = FVector::DistSquared(newPos - targetPos, previousDisplacement);
		residual[1] = newPos.Size() -5;
		return true;
	}
};