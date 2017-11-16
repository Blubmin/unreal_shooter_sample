// Fill out your copyright notice in the Description page of Project Settings.

#include "ShooterGame.h"
#include "PlayerCamera.h"

#include <ceres/ceres.h>

APlayerCamera::APlayerCamera(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	PrimaryActorTick.bCanEverTick = true;
}

void APlayerCamera::SetPlayer(TWeakObjectPtr<AShooterCharacter> NewTarget) {
	if (Target.IsValid()) Target->SwapMesh();
	Target = TWeakObjectPtr<AShooterCharacter>(NewTarget.Get());
	if (Target.IsValid()) Target->SwapMesh();
}

void APlayerCamera::Tick(float DeltaTime) {
	if (!Target.IsValid()) {
		UE_LOG(LogTemp, Log, TEXT("INVALID"));
		return;
	};
	FVector position;
	FRotator rotation;
	Target->GetActorEyesViewPoint(position, rotation);
	GetCameraComponent()->SetRelativeLocationAndRotation(position, rotation);


	double initial_x = 5.0;
	double x = initial_x;
	// Build the problem.
	ceres::Problem problem;

	// Set up the only cost function (also known as residual). This uses
	// auto-differentiation to obtain the derivative (jacobian).
	ceres::CostFunction* cost_function =
		new ceres::AutoDiffCostFunction<CostFunctor, 1, 1>(new CostFunctor);
	problem.AddResidualBlock(cost_function, NULL, &x);

	// Run the solver!
	ceres::Solver::Options options;
	options.linear_solver_type = ceres::DENSE_QR;
	options.minimizer_progress_to_stdout = true;
	ceres::Solver::Summary summary;
	ceres::Solve(options, &problem, &summary);

	UE_LOG(LogTemp, Log, TEXT("x : %d -> %d"), initial_x, x);
}