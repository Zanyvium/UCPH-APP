#ifndef MATRIXHEADERDEF
#define MATRIXHEADERDEF

#include <cassert>
#include <cmath>
#include <vector>

#include "Vector.hpp"


template<class T> class Matrix
{
private:
	std::vector<T> mData; // entries of matrix
	int mNumRows, mNumCols; // dimensions

public:
    // copy constructor
	Matrix(const Matrix& otherMatrix)
    {
        mNumRows = otherMatrix.mNumRows;
        mNumCols = otherMatrix.mNumCols;
        //mData = otherMatrix.mData;
        mData = std::vector<T>(otherMatrix.mNumRows*otherMatrix.mNumCols);
        for (int i = 0; i < mNumRows; i++)
        {
            for (int j = 0; j < mNumCols; j++)
            {
                mData[i*mNumCols+j] = otherMatrix.mData[i*mNumCols+j];
            }
        }
    }

	Matrix(int numRows, int numCols)
    {
        assert(numRows > 0);
        assert(numCols > 0);

        mNumRows = numRows;
        mNumCols = numCols;
        mData = std::vector<T>(mNumRows*mNumCols);
        for (int i = 0; i < mNumRows; i++)
        {
            for (int j = 0; j < mNumCols; j++)
            {
                mData[i*mNumCols+j] = 0.0;
            }
        }
    }

	//~Matrix()
    //{
    //    for (int i = 0; i < mNumRows; i++)
    //    {
    //        delete[] mData[i];
    //    }
    //    delete[] mData;
    //}

	int GetNumberOfRows() const
    {
        return mNumRows;
    }

	int GetNumberOfColumns() const
    {
        return mNumCols;
    }

	T& operator()(int i, int j)
    {
        assert(i >= 0);
        assert(i < mNumRows);
        assert(j >= 0);
        assert(j < mNumCols);

        return mData[i*mNumCols+j];
    }

	T const& operator()(int i, int j) const
    {
        assert(i >= 0);
        assert(i < mNumRows);
        assert(j >= 0);
        assert(j < mNumCols);

        return mData[i*mNumCols+j];
    }

	// overloaded assignment operator
	Matrix& operator=(const Matrix& otherMatrix)
    {
        assert(mNumRows == otherMatrix.mNumRows);
        assert(mNumCols == otherMatrix.mNumCols);

        for (int i = 0; i < mNumRows; i++)
        {
            for (int j = 0; j < mNumCols; j++)
            {
                mData[i*mNumCols+j] = otherMatrix.mData[i*mNumCols+j];
            }
        }
        return *this;
    }

	Matrix operator-() const // unary -
    {
        Matrix mat(mNumRows, mNumCols);
        for (int i = 0; i < mNumRows; i++)
        {
            for (int j = 0; j < mNumCols; j++)
            {
                mat(i,j) = -mData[i*mNumCols+j];
            }
        }
        return mat;
    }

	Matrix operator+(const Matrix& m1) const // binary +
    {
        assert(mNumRows == m1.mNumRows);
        assert(mNumCols == m1.mNumCols);

        Matrix mat(mNumRows, mNumCols);
        for (int i = 0; i < mNumRows; i++)
        {
            for (int j = 0; j < mNumCols; j++)
            {
                mat(i,j) = mData[i*mNumCols+j] + m1.mData[i*mNumCols+j];
            }
        }
        return mat;
    }

	Matrix operator-(const Matrix& m1) const // binary -
    {
        assert(mNumRows == m1.mNumRows);
        assert(mNumCols == m1.mNumCols);

        Matrix mat(mNumRows, mNumCols);
        for (int i = 0; i < mNumRows; i++)
        {
            for (int j = 0; j < mNumCols; j++)
            {
                mat(i,j) = mData[i*mNumCols+j] - m1.mData[i*mNumCols+j];
            }
        }
        return mat;
    }

	// scalar multiplication
	Matrix operator*(double a) const
    {
        Matrix mat(mNumRows, mNumCols);
        for (int i = 0; i < mNumRows; i++)
        {
            for (int j = 0; j < mNumCols; j++)
            {
                mat(i,j) = a*mData[i*mNumCols+j];
            }
        }
        return mat;
    }

    std::vector<T> const& getStorage() const;
}; // class Matrix


//matrix-vector multiplications
template<class T> Vector<T> operator*(const Matrix<T>& m, const Vector<T>& v)
{
    int original_vector_size = v.size();
	assert(m.GetNumberOfColumns() == original_vector_size);

	int new_vector_length = m.GetNumberOfRows();
	Vector<T> new_vector(new_vector_length);

	for (int i = 0; i < new_vector_length; i++)
	{
		for (int j = 0; j < original_vector_size; j++)
		{
			new_vector[i] += m(i,j)*v[j];
		}
	}

	return new_vector;
}

template<class T> Vector<T> operator*(const Vector<T>& v, const Matrix<T>& m)
{
	int original_vector_size = v.size();
	assert(m.GetNumberOfRows() == original_vector_size);

	int new_vector_length = m.GetNumberOfColumns();
	Vector<T> new_vector(new_vector_length);

	for (int i = 0; i < new_vector_length; i++)
	{
		for (int j = 0; j < original_vector_size; j++)
		{
			new_vector[i] += v[j]*m(j,i);
		}
	}

	return new_vector;
}

template<class T> std::vector<T> const& Matrix<T>::getStorage() const {
    return mData;
}

#endif
