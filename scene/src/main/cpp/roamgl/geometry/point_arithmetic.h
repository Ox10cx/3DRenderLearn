//
// Created by gongxi on 2024/9/2.
//

#ifndef ASSIMPDEMO_POINT_ARITHMETIC_H
#define ASSIMPDEMO_POINT_ARITHMETIC_H

namespace geometry {

template <typename T>
point<T> operator+(point<T> const& lhs, point<T> const& rhs)
{
    return point<T>(lhs.x + rhs.x, lhs.y + rhs.y);
}

template <typename T>
point<T> operator+(point<T> const& lhs, T const& rhs)
{
return point<T>(lhs.x + rhs, lhs.y + rhs);
}

template <typename T>
point<T> operator-(point<T> const& lhs, point<T> const& rhs)
{
return point<T>(lhs.x - rhs.x, lhs.y - rhs.y);
}

template <typename T>
point<T> operator-(point<T> const& lhs, T const& rhs)
{
return point<T>(lhs.x - rhs, lhs.y - rhs);
}

template <typename T>
point<T> operator*(point<T> const& lhs, point<T> const& rhs)
{
return point<T>(lhs.x * rhs.x, lhs.y * rhs.y);
}

template <typename T>
point<T> operator*(point<T> const& lhs, T const& rhs)
{
return point<T>(lhs.x * rhs, lhs.y * rhs);
}

template <typename T>
point<T> operator/(point<T> const& lhs, point<T> const& rhs)
{
return point<T>(lhs.x / rhs.x, lhs.y / rhs.y);
}

template <typename T>
point<T> operator/(point<T> const& lhs, T const& rhs)
{
return point<T>(lhs.x / rhs, lhs.y / rhs);
}

template <typename T>
point<T>& operator+=(point<T>& lhs, point<T> const& rhs)
{
    lhs.x += rhs.x;
    lhs.y += rhs.y;
    return lhs;
}

template <typename T>
point<T>& operator+=(point<T>& lhs, T const& rhs)
{
    lhs.x += rhs;
    lhs.y += rhs;
    return lhs;
}

template <typename T>
point<T>& operator-=(point<T>& lhs, point<T> const& rhs)
{
    lhs.x -= rhs.x;
    lhs.y -= rhs.y;
    return lhs;
}

template <typename T>
point<T>& operator-=(point<T>& lhs, T const& rhs)
{
    lhs.x -= rhs;
    lhs.y -= rhs;
    return lhs;
}

template <typename T>
point<T>& operator*=(point<T>& lhs, point<T> const& rhs)
{
    lhs.x *= rhs.x;
    lhs.y *= rhs.y;
    return lhs;
}

template <typename T>
point<T>& operator*=(point<T>& lhs, T const& rhs)
{
    lhs.x *= rhs;
    lhs.y *= rhs;
    return lhs;
}

template <typename T>
point<T>& operator/=(point<T>& lhs, point<T> const& rhs)
{
    lhs.x /= rhs.x;
    lhs.y /= rhs.y;
    return lhs;
}

template <typename T>
point<T>& operator/=(point<T>& lhs, T const& rhs)
{
    lhs.x /= rhs;
    lhs.y /= rhs;
    return lhs;
}

}

#endif //ASSIMPDEMO_POINT_ARITHMETIC_H
