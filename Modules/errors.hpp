/*
** EPITECH PROJECT, 2025
** exect
** File description:
** expect
*/

#pragma once
#include "string.h"
#include "iostream"
#include <memory>

class Error_Division: public std::exception
{
    public:
        const char *what() const noexcept override { return "Division by zero";
        };
};

class Error_factory: public std::exception
{
    public:
        const char *what() const noexcept override { return "Probleme de factory";
        };
};

class Error_Dyn: public std::exception
{
    public:
        const char *what() const noexcept override { return "dl";
        };
};

class Error_ptr: public std::exception
{
    public:
        const char *what() const noexcept override { return "pointeur null";
        };
};


class Error_Sfml: public std::exception
{
    public:
        const char *what() const noexcept override { return "Problème dans le file sfml.cpp";
        };
};


class Error_Sdl: public std::exception
{
    public:
        const char *what() const noexcept override { return "Problème dans le file sdl.cpp";
        };
};


class Error_Ncurses: public std::exception
{
    public:
        const char *what() const noexcept override { return "Probleme dans le file ncurses.cpp";
        };
};