#include "Vector2.h"
namespace YunutyEngine
{
    template<typename real>
    const Vector2<real> Vector2<real>::zero = Vector2<real>(0, 0);
    template<typename real>
    const Vector2<real> Vector2<real>::right = Vector2<real>(1, 0);
    template<typename real>
    const Vector2<real> Vector2<real>::left = Vector2<real>(-1, 0);
    template<typename real>
    const Vector2<real> Vector2<real>::up = Vector2<real><real>(0, 1);
    template<typename real>
    const Vector2<real> Vector2<real>::down = Vector2<real>(0, -1);
}
