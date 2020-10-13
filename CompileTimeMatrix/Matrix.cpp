#ifndef  MATRIX_CPP
#define  MATRIX_CPP
#include "Matrix.hpp"
//The class has the standard constructor,copy constructor,move constructor,operators for moves and minus 
template<typename T, std::size_t M,std::size_t  N>
constexpr Matrix<T,M, N>::Matrix(T value)
{
	for (std::size_t m = 0; m < M; m++)
	{
		for (std::size_t n = 0; n < N; n++)
			data[m][n] = value;
	}
}

template<typename T, std::size_t M,std::size_t  N>
Matrix<T,M, N>::Matrix(const Matrix<T, M,N>& source) : data(source.data)
{

}

template<typename T,std::size_t M,std::size_t  N>
Matrix<T,M, N>::Matrix(Matrix<T,M, N>&& target) noexcept
{
	data = std::move(target.data);
}

template<typename T,std::size_t M, std::size_t  N>
Matrix<T,M, N>::~Matrix()
{
	//Deletion
}
//Matrix function modify each row by a function F
template<typename T,std::size_t M, std::size_t  N>
void Matrix<T,M, N>::modify(const std::function<T(T&)>& f)
{
	for (std::size_t m = 0; m < M; m++)
	{
		std::transform(data[m].begin(), data[m].end(), data[m].begin(), f);
	}
}

template<typename T, std::size_t M,std::size_t  N>
Matrix<T,M, N>& Matrix<T,M, N>::operator=(const Matrix<T,M, N>& source)
{
	if (this == &source)
		return *this;
	data = source.data;
	return *this;
}

template<typename T,std::size_t M, std::size_t  N>
Matrix<T, M,N>& Matrix<T,M, N>::operator=(Matrix<T,M, N>&& target) noexcept
{

	if (this == &target)
		return *this;
	data = std::move(target.data);
	return *this;
	// TODO: insert return statement here
}
//Row based access that is a write only
template<typename T,std::size_t M,std::size_t  N>
std::array<T,N>& Matrix<T,M,N>::operator[](std::size_t index)
{
	if (index < 0 || index >= M)
	{
		throw std::out_of_range("Out of range of matrix");
	}
	return data[index];
}
//Row based access that is read only
template<typename T,std::size_t M, std::size_t  N>
const std::array<T,N>& Matrix<T,M, N>::operator[](std::size_t index) const
{
	if (index < 0 || index >= M)
	{
		throw std::out_of_range("Out of range of matrix");
	}
	return data[index];
}
//This operator allow us to acess the matrix in a 2-D manner with a given row number and column number 
template<typename T, std::size_t M, std::size_t N>
T& Matrix<T, M, N>::operator()(std::size_t rownumber, std::size_t columnnumber)
{
	if (rownumber < 0 || rownumber >= M || columnnumber < 0 || columnnumber >= N)
	{
		throw std::out_of_range("Out of range of matrix in row or column");
	}
	return data[rownumber][columnnumber];
}
//This operator allow us to  read the matrix in a 2-D manner with a given row number and column number 

template<typename T, std::size_t M, std::size_t N>
const T& Matrix<T, M, N>::operator()(std::size_t rownumber, std::size_t columnnumber) const
{
	if (rownumber < 0 || rownumber >= M || columnnumber < 0 || columnnumber >= N)
	{
		throw std::out_of_range("Out of range of matrix in row or column");
	}
	return data[rownumber][columnnumber];
}
//Addtion operator to add two matricies and create a new matrix  to store the results
template<typename T,std::size_t M, std::size_t  N>
Matrix<T,M, N> Matrix<T,M, N>::operator+(const Matrix<T, M,N>& Matrix_2) const
{
	if (data.size() != Matrix_2.data.size() || data[0].size() != Matrix_2.data[0].size())
	{
		throw std::domain_error("The two Matrixs are not equal dimensions");
	}
	Matrix<T,M, N>newMatrix;
	for (std::size_t row =0;row < M; row++)
	{
		for(std::size_t column = 0; column < N; column++)
			newMatrix(row,column) = data[row][column] + Matrix_2(row,column);
	}
	return newMatrix;
}
//Addtion operator to subtract matricies and create a new matrix  to store the results

template<typename T,std::size_t M, std::size_t  N>
Matrix<T, M, N> Matrix<T, M, N>::operator-(const Matrix<T,M, N>& Matrix_2) const
{
	if (data.size() != Matrix_2.data.size() || data[0].size() != Matrix_2.data[0].size())
	{
		throw std::domain_error("The two Matrixs are not equal dimensions");
	}
	Matrix<T, M, N>newMatrix;
	for (std::size_t row = 0; row < M; row++)
	{
		for (std::size_t column = 0; column < N; column++)
			newMatrix(row, column) = data[row][column] - Matrix_2(row, column);
	}
	return newMatrix;
}
//Addtion operator to multiply matricies with a scalar number 

template<typename T, std::size_t M, std::size_t N>
Matrix<T, M, N> Matrix<T, M, N>::operator*(const T& a) const
{
	Matrix<T, M, N>newMatrix;
	for (std::size_t row = 0; row < M; row++)
	{
		for (std::size_t column = 0; column < N; column++)
			newMatrix(row, column) = data[row][column] * a;
	}
	return newMatrix;
}
//Unary minus operator
template<typename T,std::size_t M, std::size_t  N>
Matrix<T, M,N> Matrix<T,M, N>::operator-() const
{
	Matrix<T, M, N>newMatrix;
	for (std::size_t row = 0; row < M; row++)
	{
		for (std::size_t column = 0; column < N; column++)
			newMatrix(row, column) = -data[row][column];
	}
	return newMatrix;
}
//Print function 
template<typename T,std::size_t M, std::size_t N>
void Matrix<T,M, N>::Print() const
{
	for (std::size_t row = 0; row < M; row++)
	{
		for (std::size_t column = 0; column < N; column++)
			std::cout << data[row][column] << " ";
		std::cout << "\n";
	}
}
//Friend function to allow communative operations for scalar multiplication
template<typename T, std::size_t  M,std::size_t N, typename F>
Matrix<T,M,N> operator*(const F& a, const Matrix<T, M,N>& pt)
{
	Matrix<T,M, N>newMatrix;
	for (std::size_t row = 0; row < M; row++)
	{
		for (std::size_t column = 0; column < N; column++)
			newMatrix(row, column) = pt(row,column) * a;
	}
	return newMatrix;
}

#endif // ! Matrix_CPP
