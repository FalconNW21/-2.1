
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include "MainWindow.h"
#include "StateManager.h"
#include "SDL_SCOPE.h"
#include <locale.h>

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "");
    SDL_Scope sdl_scope;

    MainWindow::init("", 1500, 750);
    StateManager stateManager;
    stateManager.exec("NumInput");
    MainWindow::deinit();

    return 0;
}



