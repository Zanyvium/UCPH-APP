#ifndef VECTOROLDHEADERDEF
#define VECTOROLDHEADERDEF

#include <cassert>
#include <cmath>

class VectorOld
{
private:
	double* mData; // data stored in vector
	int mSize; // size of vector

public:
    // copy constructor
  VectorOld(const VectorOld& otherVector)
    {
        mSize = otherVector.size();
        mData = new double [mSize];
        for (int i = 0; i < mSize; i++)
        {
            mData[i] = otherVector.mData[i];
        }
    }

	VectorOld(int size)
    {
        assert(size > 0);

        mSize = size;
        mData = new double [mSize];
        for (int i = 0; i < mSize; i++)
        {
            mData[i] = 0.0;
        }
    }

	~VectorOld()
    {
        delete[] mData;
    }

	int size() const
    {
        return mSize;
    }

    //[] operator allowing both reading and writing of and to indices (index i)
	double& operator[](int i) {
        assert(i >= 0 && i < mSize);
        return mData[i];
    }
    //[] operator allowing only reading of indices (index i)
	double const& operator[] (int i)const {
        assert(i >= 0 && i < mSize);
        return mData[i];
    }

	// assignment operator
	VectorOld& operator=(const VectorOld& otherVector)
    {
        assert(mSize == otherVector.mSize);

        for (int i = 0; i < mSize; i++)
        {
            mData[i] = otherVector.mData[i];
        }
        return *this;
    }

    // overloading the unary - operator
	VectorOld operator-() const
    {
        VectorOld v(mSize);
        for (int i = 0; i < mSize; i++)
        {
            v[i] = -mData[i];
        }
        return v;
    }

    // overloading the binary + operator
	VectorOld operator+(const VectorOld& v1) const {
        assert(mSize == v1.mSize);

        VectorOld v(mSize);
        for (int i = 0; i < mSize; i++)
        {
            v[i] = mData[i] + v1.mData[i];
        }
        return v;
    }

    // overloading the binary - operator
	VectorOld operator-(const VectorOld& v1) const
    {
        assert(mSize == v1.mSize);

        VectorOld v(mSize);
        for (int i = 0; i < mSize; i++)
        {
            v[i] = mData[i] - v1.mData[i];
        }
        return v;
    }

	// scalar multiplication
	VectorOld operator*(double a) const
    {
        VectorOld v(mSize);
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