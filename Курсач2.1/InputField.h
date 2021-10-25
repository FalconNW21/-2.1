#pragma once
#include "State.h"
#include "MyString.h"
#include "MainWindow.h"
#include "StringManager.h"

/*
Здесь осуществляем ввод строк
*/

class InputField : public State
{

public:
 
    
    InputField(const std::string& message, const std::string& wayback, bool (*instruction)(const std::string&)) : message(message), wayback(wayback), instruction(instruction)
    {

    }



    std::string exec()
    {
        in.clear();
        redraw();

        SDL_StartTextInput();
        SDL_Event event;
        while (SDL_WaitEvent(&event))
        {
            switch (event.type)
            {
            case SDL_TEXTINPUT:
            {
                in += event.text.text;
                redraw();
                break;
            }
            case SDL_KEYUP:
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_BACKSPACE:
                {
                    if (in.size())
                    {
                        in.pop_back();
                        redraw();
                    }
                    break;
                }
                case SDLK_RETURN:
                {
                    if (!instruction(in))
                    {
                        MainWindow::drawText(StringManager::getError(), 100, 300);
                        SDL_RenderPresent(MainWindow::renderer());
                        break;
                    }
                    SDL_StopTextInput();
                    return wayback;
                }
                case SDLK_ESCAPE:
                {
                    SDL_StopTextInput();
                    return from;
                }
                }
                break;
            }

            case SDL_QUIT:
            {
                SDL_StopTextInput();
                return "Exit";
            }
            }
        }
        
    }


private:
    std::string in;
    std::string message;
    std::string wayback;
    bool (*instruction)(const std::string&);

    void redraw()
    {
        MainWindow::fillBackground();
        SDL_Rect rect = MainWindow::drawText(message, 100, 100);
        MainWindow::drawText(in, 100 , 100+ rect.h+10);
        SDL_RenderPresent(MainWindow::renderer());
    }
};
