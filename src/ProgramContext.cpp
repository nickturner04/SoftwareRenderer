//
// Created by s5614562 on 05/03/25.
//

#include "ProgramContext.h"
namespace nsi {

ProgramContext::ProgramContext(){
    window = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
    windowWidth = 800;
    windowHeight = 600;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    scene = nsr::Scene();
}
ProgramContext::ProgramContext(const int width, const int height) {
    windowWidth = width;
    windowHeight = height;
    window = SDL_CreateWindow("Window",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}
ProgramContext::~ProgramContext() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
}
}



