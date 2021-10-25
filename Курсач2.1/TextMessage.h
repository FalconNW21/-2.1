/*
Фалй отвечает за вывод сообщения
 выводим текст из message
 Выход будет на enter (Ждем, пока нажмут enter)
При выходе возвращаем сам wayback
*/


#pragma once
#include "State.h"
#include "MainWindow.h"
#include <iostream>
#include "StringManager.h"


class TextMessage : public State
{
public:
    TextMessage(const std::string& message, const std::string& wayback, std::string(*getMessage)() = nullptr) : message(message), wayback(wayback), getMessage(getMessage)
    {

    }

    std::string exec()
    {

        MainWindow::fillBackground();
        std::string text = message;
        if (getMessage)
        {
            text += getMessage();
        }
        SDL_Rect rect = MainWindow::drawText(text, 100, 100);
        SDL_RenderPresent(MainWindow::renderer());


        SDL_Event event;
        while (SDL_WaitEvent(&event))
        {

            switch (event.type)
            {
            case SDL_MOUSEBUTTONUP:
            {
                SDL_Point point{ event.button.x, event.button.y };
                if (SDL_PointInRect(&point, &rect))
                {
                    return wayback;
                }
                break;
            }
            case SDL_KEYDOWN:
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_RETURN:
                {
                    return wayback;
                }
                case SDLK_ESCAPE:
                {
                    return from;
                }
                }
                break;
            }
            case SDL_QUIT:
            {
                return "Exit";
            }
            }
        }

        return "Exit";
    }


private:
    std::string message;
    std::string wayback;
    std::string(*getMessage)();
};
