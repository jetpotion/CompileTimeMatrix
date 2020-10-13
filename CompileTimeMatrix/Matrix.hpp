#ifndef MATRIX_HPP
#define MATRIX_HPP
#include <array>
#include <ostream>
#include <sstream>
#include <iostream>
#include <exception>
#include <functional>
//Matrix class that takes a type, and data fields for the size of the MxN matrix
template<typename T, const std::size_t M,const std::size_t N>
class Matrix
{
	using NestedMatrix = std::array<std::array<T, N>, M>; //Using alias to name the matrix type
private:
	NestedMatrix data = {{}};						//Matrix data that is modified
public:
	Matrix() = default;										//Empty constructor
	constexpr Matrix(T	 value);							//Constructor with values
	Matrix(const Matrix<T,M, N>& source);						//Copy constructor
	Matrix(Matrix<T,M, N>&& target) noexcept;					//Move constructor
	~Matrix();												//Destructor
	void modify(const std::function < T(T&)>& f);			//Modify function to transform 
	Matrix<T, M,N>& operator=(const Matrix<T,M, N>& source);	//Assignment operator
	Matrix<T,M, N>& operator=(Matrix<T, M,N>&& target) noexcept;		//Movement operator
	std::array<T,N>& operator[](std::size_t index);					//Used for modification hence only for write only 
	const std::array<T,N>& operator[](std::size_t index) const;		//Used for read only
	T& operator()(std::size_t rownumber, std::size_t columnnumber);	//This will allow us to do writes only
	const T& operator()(std::size_t rownumber, std::size_t columnnumber) const; //This will be for read only
	Matrix<T,M, N> operator+(const Matrix<T,M, N>& Matrix_2) const;		//Addition operator to add two Matrixs
	Matrix<T,M, N>  operator-(const Matrix<T,M,N>& Matrix_2) const;		//Subtract two Matrixs
	Matrix<T, M, N>  operator*(const T& a) const;						//Multiply matrix with a scalar
	Matrix<T,M, N> operator-() const;										//Unary minus
	template <typename T,std::size_t M, std::size_t N, typename F>		//Friend function to scale data 
	friend Matrix<T,M, N>  operator * (const F& a, const Matrix<T,M, N>& pt);	//operator for matrix scalar multiplication
	void Print() const;

};
#ifndef  MATRIX_CPP
#include "Matrix.cpp"
#endif // ! Matrix_CPP
#endif

