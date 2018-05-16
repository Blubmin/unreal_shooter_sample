// Fill out your copyright notice in the Description page of Project Settings.

#include "ShooterGame.h"
#include "CinematicCamera.h"
#include "EngineUtils.h"
#include "CostFunctions.h"

#include <ceres/ceres.h>

ACinematicCamera::ACinematicCamera(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	PrimaryActorTick.bCanEverTick = true;
}

void ACinematicCamera::SetPlayer(TWeakObjectPtr<AShooterCharacter> NewTarget) {
	Target = TWeakObjectPtr<AShooterCharacter>(NewTarget.Get());
}

void ACinematicCamera::Tick(float DeltaTime) {
	if (!Target.IsValid()) {
		UE_LOG(LogTemp, Log, TEXT("INVALID"));
		return;
	};
	FVector position;
	FRotator rotation;
	Target->GetActorEyesViewPoint(position, rotation);

	double parameters[6];
	parameters[0] = position.X;
	parameters[1] = position.Y;
	parameters[2] = position.Z;
	parameters[3] = rotation.Pitch;
	parameters[4] = rotation.Yaw;
	parameters[5] = rotation.Roll;
	// Build the problem.
	ceres::Problem problem;

	// Set up the only cost function (also known as residual). This uses
	// auto-differentiation to obtain the derivative (jacobian).
	ceres::CostFunction* cost_function =
		new ceres::NumericDiffCostFunction<OneThirdsCostFunction, ceres::NumericDiffMethodType::CENTRAL, 1, 6>(new OneThirdsCostFunction(this));
	problem.AddResidualBlock(cost_function, NULL, parameters);
	cost_function = 
		new ceres::NumericDiffCostFunction<MovementCostFunction, ceres::NumericDiffMethodType::CENTRAL, 2, 6>(new MovementCostFunction(this));
	problem.AddResidualBlock(cost_function, NULL, parameters);

	// Run the solver!
	ceres::Solver::Options options;
	options.linear_solver_type = ceres::DENSE_QR;
	options.minimizer_progress_to_stdout = true;
	ceres::Solver::Summary summary;
	ceres::Solve(options, &problem, &summary);

	//UE_LOG(LogTemp, Log, TEXT("x : %lf -> %lf"), initial_x, x);
	GetCameraComponent()->SetRelativeLocationAndRotation(FVector(parameters[0], parameters[1], parameters[2]), FRotator(parameters[3], parameters[4], parameters[5]));
}