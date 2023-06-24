#ifndef VECTORHEADERDEF
#define VECTORHEADERDEF

#include <cassert>
#include <cmath>
#include <vector>

template<class T> class Vector
{
private:
	std::vector<T> mData; // data stored in vector
	int mSize; // size of vector

public:
    // copy constructor
  Vector(const Vector& otherVector)
    {
        mSize = otherVector.mSize;
        mData = otherVector.mData;
/*         mData = std::vector<T>(otherVector.mSize);
        for (int i = 0; i < otherVector.mSize; i++)
        {
            mData[i] = otherVector.mData[i];
        } */
    }

	Vector(int size)
    {
        assert(size > 0);

        mSize = size;
        mData = std::vector<T>(size, 0.0);
/*         mData = std::vector<T>(size);
        for (int i = 0; i < mSize; i++)
        {
            mData[i] = 0.0;
        } */
    }

	//~Vector()
    //{
    //    delete[] mData;
    //}

	int size() const
    {
        return mSize;
    }

	T& operator[](int i)
    {
        assert(i >= 0 && i < mSize);
        return mData[i];
    }

	T const& operator[] (int i) const
    {
        assert(i >= 0 && i < mSize);
        return mData[i];
    }

	// assignment operator
	Vector& operator=(const Vector& otherVector)
    {
        assert(mSize == otherVector.mSize);

        for (int i = 0; i < mSize; i++)
        {
            mData[i] = otherVector.mData[i];
        }
        return *this;
    }

    // overloading the unary - operator
	Vector operator-() const
    {
        Vector v(mSize);
        for (int i = 0; i < mSize; i++)
        {
            v[i] = -mData[i];
        }
        return v;
    }

    // overloading the binary + operator
	Vector operator+(const Vector& v1) const
    {
        assert(mSize == v1.mSize);

        Vector v(mSize);
        for (int i = 0; i < mSize; i++)
        {
            v[i] = mData[i] + v1.mData[i];
        }
        return v;
    }

    // overloading the binary - operator
	Vector operator-(const Vector& v1) const
    {
        assert(mSize == v1.mSize);

        Vector v(mSize);
        for (int i = 0; i < mSize; i++)
        {
            v[i] = mData[i] - v1.mData[i];
        }
        return v;
    }

	// scalar multiplication
	Vector operator*(double a) const
    {
        Vector v(mSize);
        for (int i = 0; i < mSize; i++)
        {
            v[i] = a*mData[i];
        }
        return v;
    }

	// p-norm method
	double CalculateNorm(int p = 2) const
    {
        double sum = 0.0;
        for (int i = 0; i < mSize; i++)
        {
            sum += pow(std::abs(mData[i]), p);
        }
        return pow(sum, 1.0 / ((double)(p)));
    }
};


#endif
