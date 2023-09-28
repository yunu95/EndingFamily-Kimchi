#pragma once
#include <iostream>
#include "Object.h"
namespace YunutyEngine
{
    template<typename real>
    class Vector : Object
    {
    protected:
        real* vectorArray;
        unsigned int vectorSize;
        Vector(real* vectorArray, unsigned int vectorSize) : vectorArray(vectorArray), vectorSize(vectorSize) {}
    public:
        static real Dot(const Vector& lhs, const Vector& rhs)
        {
            return 0;
        }

        static Vector Project(const Vector& vector, const Vector& onNormal)
        {
            return *this;
        }

        static Vector Lerp(const Vector& a, const Vector& b, float t)
        {
            return *this;
        }

        real Magnitude()const
        {
            return 0;
        }

        real MagnitudeSqr()const
        {
            return 0;
        }

        Vector Normalized()const
        {
            return *this;
        }
        //Vector operator*(const float& scalar)const;
        //Vector& operator*=(const float& scalar);
        //Vector operator+(const Vector& rhs)const;
        //Vector operator-(const Vector& rhs)const;
        Vector& operator=(const Vector& rhs)
        {
            for (unsigned int i = 0; i < vectorSize; i++)
                vectorArray[i] = i < rhs.vectorSize ? rhs.vectorArray[i] : 0;
            return *this;
        }
        template<typename SubVector>
        operator SubVector()const
        {
            static_assert(std::is_base_of<Vector, SubVector>::value, "only derived classes from vector are allowed");
            SubVector ret;
            (Vector)ret = *this;
            return ret;
        }
        template<class SubVector>
        operator const SubVector& ()const
        {
            return *this;
        }
    };
}

