#ifndef MATRIX_HPP_GUARD
#define MATRIX_HPP_GUARD

#include <cstddef>
#include <vector>
#include <cassert>
#include <utility>
#include <iostream>

template<typename T>
class matrix_proxy {
private:
	typename std::vector<T>::iterator data_ptr;
public:
	matrix_proxy(typename std::vector<T>::iterator data) : data_ptr(data){}
	
	T& operator[] (size_t j)
	{
		return *(data_ptr + j);
	}

};

template<typename T>
class const_matrix_proxy {
private:
	typename std::vector<T>::const_iterator data_ptr;
public:
	const_matrix_proxy(typename std::vector<T>::const_iterator data) : data_ptr(data){}
	
	const T& operator[] (size_t j)
	{
		return *(data_ptr + j);
	}

};

template<typename T>
class matrix {
private:
	std::vector<T> data_;
	size_t rows_;
	size_t cols_;
public:

	static constexpr size_t npos = -1;

//----------- elements access ----------

	matrix_proxy<T> operator[] (size_t i)
	{
		assert(i < rows_);
		return matrix_proxy<T>(data_.begin() + i * cols_);
	}

	const_matrix_proxy<T> operator[] (size_t i) const
	{
		assert(i < rows_);
		return const_matrix_proxy<T>(data_.cbegin() + i * cols_);
	}

	T& at(size_t i, size_t j)
	{
		return (*this)[i][j];
	}

	const T& at(size_t i, size_t j) const
	{
		return (*this)[i][j];
	}

	size_t rows() const
	{
		return rows_;
	}

	size_t cols() const
	{
		return cols_;
	}
	
//---------- constructors  -----------

	matrix(size_t rows, size_t cols) : 
		data_(rows * cols), rows_(rows), cols_(cols){}

	matrix(size_t rows, size_t cols, const T& scalar) :
		data_(rows * cols, scalar), rows_(rows), cols_(cols){}

	static matrix<T> scalar_matrix(size_t n, const T& scalar)
	{
		matrix<T> mat(n, n, T(0));
		for (size_t i = 0; i < n; ++i)
			mat[i][i] = scalar;
		return mat;
	}

	static matrix<T> unit(size_t n)
	{
		return scalar_matrix(n, T(1));
	}

//---------- elemantary row operations ----------

	void switch_rows(size_t i, size_t j, size_t offset = 0)
	{
		for (size_t k = offset; k < cols_; ++k)
			std::swap(at(i, k), at(j, k));

	}

	void multiply_row(size_t i, T scalar, size_t offset = 0)
	{
		assert(scalar != T(0));

		for (size_t j = offset; j < cols_; ++j)
			at(i, j) *= scalar;
	}

	//for integer matrix algorithms

	void divide_row(size_t i, T scalar, size_t offset = 0)
	{
		assert(scalar != T(0));
		
		for (size_t j = offset; j < cols_; ++j)
			at(i, j) /= scalar;
		
	
	}

	void add_scaled_row(size_t to, size_t from, const T& scalar, size_t offset = 0)
	{
		assert(to != from);
		
		for (size_t j = offset; j < cols_; ++j)
			at(to, j) += at(from, j) * scalar;
	}


};

#endif
