#include "solver.hpp"

auto integer_to_rational_matrix(const matrix<int64_t>& mat)
	-> matrix<rational>
{
	matrix<rational> result(mat.rows(), mat.cols());
	for (size_t i = 0; i < mat.rows(); ++i)
		for (size_t j = 0; j < mat.cols(); ++j)
			result[i][j] = mat[i][j];
	return result;
}

uint64_t row_den_lcm(const matrix<rational>& mat, size_t i)
{
	uint64_t res = 1;
	
	for (size_t j = 0; j < mat.cols(); ++j){
		res = lcm(res, i64abs(mat[i][j].denominator()));
	}
	return res;
}

auto normalize_rational_basis(const matrix<rational>& mat)
	-> matrix<int64_t>
{
	matrix<int64_t> result(mat.rows(), mat.cols());

	for (size_t i = 0; i < mat.rows(); ++i){
		int64_t common_den = row_den_lcm(mat, i);
		for (size_t j = 0; j < mat.cols(); ++j){
			rational tmp = mat[i][j] * common_den;
			result[i][j] = tmp.numerator();
		}
	}

	return result;
}

void solve_system(matrix<int64_t>& mat)
{
	auto rational_matrix = integer_to_rational_matrix(mat);
	auto basis = homogenious_system_basis(rational_matrix);
	auto normalized_basis = normalize_rational_basis(basis);
	present_basis(std::cout, normalized_basis);
}
