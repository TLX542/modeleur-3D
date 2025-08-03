/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** color
*/

#include "color.hpp"

namespace Objects
{
    color &color::operator=(const color &other)
    {
        if (this != &other)
        {
            r = other.r;
            g = other.g;
            b = other.b;
        }
        return *this;
    }
    color color::operator+(const color &other) const
    {
        return color(r + other.r, g + other.g, b + other.b);
    }
    color color::operator-(const color &other) const
    {
        return color(r - other.r, g - other.g, b - other.b);
    }
    color color::operator*(const color &other) const
    {
        return color(r * other.r, g * other.g, b * other.b);
    }
    color color::operator/(const color &other) const
    {
        return color(r / other.r, g / other.g, b / other.b);
    }
    bool color::operator==(const color &other) const
    {
        return (r == other.r && g == other.g && b == other.b);
    }
    bool color::operator!=(const color &other) const
    {
        return !(*this == other);
    }
    bool color::operator!() const
    {
        return (r == 0 && g == 0 && b == 0);
    }
}