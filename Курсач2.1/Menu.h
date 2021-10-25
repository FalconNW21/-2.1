/*
Рисуем меню из items
Выбор пунктов
В зависимости от выбранного пункта возвращаем определенный элемент из wayback
*/

#pragma once
#include "State.h"
#include <vector>
#include <string>
#include "MainWindow.h"


class Menu : public State
{
public:
    Menu(const std::vector<std::string>& items, const std::vector<std::string>& wayback) : items(items), wayback(wayback)
    {
    }

    std::string exec()
    {


        std::vector<SDL_Rect> rect(items.size());
        MainWindow::fillBackground();
        int i;
        for (i = 0; i < items.size(); i++)
        {
            rect[i] = MainWindow::drawText(items[i], 100, 100 + i * 60);
        }
        SDL_RenderPresent(MainWindow::renderer());

        SDL_Event event;
        while (SDL_WaitEvent(&event))
        {
            switch (event.type)
            {
            case SDL_MOUSEBUTTONUP:
            {
                SDL_Point point{ event.button.x, event.button.y };
                for (i = 0; i < items.size(); i++)
                {
                    if (SDL_PointInRect(&point, &rect[i]))
                    {
                        return wayback[i];
                    }
                }
                break;
            }
            case SDL_KEYUP:
            {
                switch (event.key.keysym.sym)
                {
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
    std::vector<std::string> items;
    std::vector<std::string> wayback;
};
