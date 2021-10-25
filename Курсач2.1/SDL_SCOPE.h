#pragma once
#define SDL_SCOPE

#include <SDL.h>
#include <SDL_ttf.h>
#include <stdexcept>

/*
Запускаем SDL и проверям, всё ли корректно запустилось
*/

using namespace std;

class SDL_Scope
{
public:
    SDL_Scope()
    {
        if (SDL_Init(SDL_INIT_EVERYTHING))
        {
            throw runtime_error("SDL_Init error");
        }
        if (TTF_Init())
        {
            throw runtime_error("TTF_Init error");
        }
    }

    ~SDL_Scope()
    {
        SDL_Quit();
        TTF_Quit();
    }
};
