#pragma once
#include "State.h"
#include <vector>
#include <string>
#include "StringManager.h"
#include "MainWindow.h"

/*
Файл отвечает за выбор строк
*/


class StringChooseMenu : public State
{
public:
 
    StringChooseMenu( int type,  const std::string& wayback ) :  type(type), wayback(wayback)
    {
    }

    std::string exec()
    {
        MainWindow::fillBackground();
        MainWindow::drawText("Выберите строку с которой работать:", 100, 100);

        std::vector<int> realindexes;
        std::vector <MyString*> items = StringManager::getStrings();
       std::vector <SDL_Rect> rect;

       for (int i = 0; i < items.size(); i++)
       {
           if (items[i]->type() == type && items[i]->str)
           {
               realindexes.push_back(i);
               rect.push_back(MainWindow::drawText(std::to_string (realindexes.size() ) + "). " + items[i]->str, 100, 250 + realindexes.size() * 60));
           }
       }
       if (realindexes.empty())
       {
           MainWindow::drawText("Строк этого типа нет, ", 100, 150);
           MainWindow::drawText("нажмите Escape", 100, 200);
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
                for (int i = 0; i < realindexes.size(); i++)
                {
                    if (SDL_PointInRect(&point, &rect[i]))
                    {
                        StringManager::setCurrentString(realindexes[i]);
                        return wayback;
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
    int type;
  std::string wayback;
};
