#ifndef MATRIX_ALGORITHM_GUARD_HPP
#define MATRIX_ALGORITHM_GUARD_HPP

#include "matrix.hpp"
#include <vector>
#include <cstddef>
#include <iostream>


template<typename T, typename U>
void dump_matrix(U& output_stream, const matrix<T>& mat)
{
	for (size_t i = 0; i < mat.rows(); ++i){
		for (size_t j = 0; j < mat.cols(); ++j)
			output_stream << mat[i][j] << " ";
		output_stream << '\n';
	}
}

template <typename T>
size_t select_pivot(const matrix<T>& mat, size_t j, size_t offset)
{
	for(size_t i = offset; i < mat.rows(); ++i){
		if (mat[i][j] != T(0))
			return i;
	}
	return matrix<T>::npos;
}

template <typename T>
void eliminate_column(matrix<T>& mat, size_t j, size_t pivot)
{
	mat.divide_row(pivot, mat[pivot][j], j);

	for (size_t i = 0; i < mat.rows(); ++i){
		if (i == pivot)
			continue;
		mat.add_scaled_row(i, pivot, -mat[i][j], j);
	}
}

template <typename T>
auto gauss_elimination(matrix<T>& mat)
	-> std::vector<bool>
{
	std::vector<bool> is_depended(mat.cols(), 0);
	size_t rank = 0;
	
	for (size_t j = 0; j < mat.cols(); ++j){
		size_t i = select_pivot(mat, j, rank);
		if (i == matrix<T>::npos)
			continue;
		is_depended[j] = true;
		mat.switch_rows(rank, i, j);
		eliminate_column(mat, j, rank);
		rank++;
	}
	return is_depended;
}

template <typename T>
auto homogenious_system_basis(matrix<T>& mat)
	->matrix<T>
{
	auto is_dependent = gauss_elimination(mat);
	std::vector<size_t> dep_vars, free_vars;

	for (size_t i = 0; i < is_dependent.size(); ++i)
		if (is_dependent[i])
			dep_vars.push_back(i);
		else
			free_vars.push_back(i);
	
	size_t rank = dep_vars.size();
	size_t dim = free_vars.size();

	if (dim == 0)
		return matrix<T>(1, mat.cols(), T(0));

	matrix<T> basis(dim, dim + rank, T(0));

	for (size_t j = 0; j < dim; ++j)
		for (size_t i = 0; i < rank; ++i)
			basis[j][dep_vars[i]] = -mat[i][free_vars[j]];
	
	for (size_t i = 0; i < dim; ++i)
		basis[i][free_vars[i]] = T(1);

	return basis;
	
}

#endif
