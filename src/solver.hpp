#ifndef SOLVER_HPP_GUARD
#define SOLVER_HPP_GUARD

#include "matrix.hpp"
#include "rational.hpp"
#include <iostream>
#include "matrix_algorithm.hpp"
#include <utility>

template <typename T>
void present_basis(std::ostream& output, const matrix<T>& basis)
{
        for (size_t i = 0; i < basis.rows(); ++i){
                output << "e" << i << " = (";
                for (size_t j = 0; j < basis.cols(); ++j) {
                        output << basis[i][j];
                        if (j + 1 != basis.cols())
                                output << ", ";
                }
                output << ")\n";
        }
}

template<typename T>
void solve_system(matrix<T>& mat)
{
	auto basis = homogenious_system_basis(mat);
	present_basis(std::cout, basis);
}

auto integer_to_rational_matrix(const matrix<int64_t>& mat)
	-> matrix<rational>;

auto normalize_rational_basis(const matrix<rational>& mat)
	-> matrix<int64_t>;

void solve_system(matrix<int64_t>& mat);

template <typename T>
auto read_data(std::istream& input, bool human)
	-> std::pair<matrix<T>, bool>
{
	if (human)
		std::cout << "enter number of rows and columns (m n)\n";
	size_t m, n;
	input >> m >> n;
	
	if (!input.good() || m * n == 0){
		return std::pair<matrix<T>, bool>(matrix<T>(1, 1), false);
	}
	
	if (human)
		std::cout << "enter system coefficients as a matrix\n";
	
	std::pair<matrix<T>, bool> result (matrix<T>(m, n), false);
	
	for (size_t i = 0; i < m; ++i){
		for (size_t j = 0; j < n; ++j){
			input >> result.first[i][j];
			if (!input.good()){
				return result;
			}
		}
	}
	result.second = true;
	return result;
	
}


#endif
