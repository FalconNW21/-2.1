#pragma once
#define MAINWINDOW

#include <SDL.h>
#include <SDL_ttf.h>
#include <stdexcept>


/*
файл отвечает за настройку SDL
*/


class MainWindow
{
    static SDL_Window* _window;
    static SDL_Renderer* _renderer;
    static int _w;
    static int _h;

public:
    static TTF_Font* _font;
    MainWindow() = delete;


    static void init(const char* title, int w, int h)
    {
        _w = w;
        _h = h;
        SDL_DisplayMode displaymode;
        SDL_GetCurrentDisplayMode(0, &displaymode);
        _window = SDL_CreateWindow(
            "WINDOW", (displaymode.w - w) / 2, (displaymode.h - h) / 2, w, h, SDL_WINDOW_SHOWN);
        if (!_window)
        {
            std::cout << "Window not created" << std::endl;
        }
        _renderer
            = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (!_renderer)
        {
            std::cout << "Renderer not created" << std::endl;
        }
        _font = TTF_OpenFont("arial.ttf", 40); 
        if (_font == nullptr)
        {
            std::cout << "Texture error" << std::endl;
        }
    }

    static void deinit()
    {
        SDL_DestroyRenderer(_renderer);
        SDL_DestroyWindow(_window);
    }


    static SDL_Window* window()
    {
        return _window;
    }

    static SDL_Renderer* renderer()
    {
        return _renderer;
    }

    static void fillBackground()
    {
        SDL_SetRenderDrawColor(_renderer, 238, 238, 232, 255); //Каррарский мрамор
        SDL_RenderFillRect(_renderer, nullptr);
    }


    static SDL_Rect drawText(const std::string& text, int x, int y)
    {

        if (text.empty())
        {
            return SDL_Rect{ 0, 0, 0, 0 };
        }
        // SDL_Color grey = { 128, 128, 128 };
        // SDL_Color beige = { 224, 207, 177 }; ЦВЕТА
        SDL_Surface* textSurface = TTF_RenderUTF8_Solid(_font, text.c_str(), { 0, 0, 0 }); // Создаем переменную для хранения  свойств фона?
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(_renderer, textSurface); // создаем переменную для хранения  данных о тексте?
        SDL_Rect destination{ x, y, textSurface->w, textSurface->h }; //координаты, где будем писать текст
        SDL_FreeSurface(textSurface); // Чистим фон???
        SDL_RenderCopy(_renderer, textTexture, nullptr, &destination); // Рисуем сам текст
        SDL_DestroyTexture(textTexture); //Чистим данные о тексте
        return destination;
    }


    static int w()
    {
        return _w;
    }

    static int h()
    {
        return _h;
    }
};

SDL_Window* MainWindow::_window = nullptr;
SDL_Renderer* MainWindow::_renderer = nullptr;
int MainWindow::_w = 0;
int MainWindow::_h = 0;
TTF_Font* MainWindow::_font = nullptr;


