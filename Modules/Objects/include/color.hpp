/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** color
*/

#pragma once

namespace Objects
{
    class color
    {
        public:
            int r;
            int g;
            int b;
            color() : r(0), g(0), b(0) {};
            color(int r, int g, int b) : r(r), g(g), b(b) {}
            color(const color &other) : r(other.r), g(other.g), b(other.b) {}
            color &operator=(const color &other);
            ~color() = default;
            color operator+(const color &other) const;
            color operator-(const color &other) const;
            color operator*(const color &other) const;
            color operator/(const color &other) const;
            bool operator==(const color &other) const;
            bool operator!=(const color &other) const;
            bool operator!() const;
    };
}