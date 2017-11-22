#include <Test.h>

#undef GOOGLE_GLOG_DLL_DECL
#define GOOGLE_GLOG_DLL_DECL 
#include <glog/logging.h>

#define CERES_MSVC_USE_UNDERSCORE_PREFIXED_BESSEL_FUNCTIONS
#include <ceres/ceres.h>

struct CostFunctor {
	template <typename T>
	bool operator()(const T* const x, T* residual) const {
		residual[0] = T(10.0) - x[0];
		return true;
	}
};

int main(int argc, char* argv[]) {
	LOG(INFO) << "TEST" << std::endl;
	thesis::TestClassForUnrealToLinkTo::DoTheThing(1, 2);

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

	return 0;
}