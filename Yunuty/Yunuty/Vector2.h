#pragma once
#include "Vector.h"
namespace YunutyEngine
{
    template<typename real>
    class Vector2 : public Vector<real>
    {
    private:
        real xy[2] = { 0 };
    public:
        real& x=xy[0];
        real& y=xy[1];
        Vector2() :Vector2<real>(0, 0) {}
        Vector2(real x, real y) :Vector<real>(xy, 2)
        {
            this->x = xy[0]=x;
            this->y = xy[1]=y;
        }
        static const Vector2 zero;
        static const Vector2 right;
        static const Vector2 left;
        static const Vector2 up;
        static const Vector2 down;

        Vector2& operator=(const Vector2& rhs) {
            Vector<real>::operator=(((Vector<real>)rhs));
            return *this;
        }
    };
    typedef Vector2<float> Vector2f;
    typedef Vector2<double> Vector2d;
};
//
//template<typename real>
//YunutyEngine::Vector2<real>::Vector2<real>(real x, real y) :Vector<real>(xy,2), x(x), y(y)
//{
//};
//template<typename real>
//YunutyEngine::Vector2<real>::Vector2<real>() : Vector2<real>(0, 0)
//{
//};
