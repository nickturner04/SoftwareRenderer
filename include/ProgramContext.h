//
// Created by s5614562 on 05/03/25.
//

#ifndef PROGRAMCONTEXT_H
#define PROGRAMCONTEXT_H
#include <SDL_render.h>
#include <SDL_video.h>

#include "Simulation/Scene.h"

namespace nsi {

class ProgramContext {
public:
    ProgramContext();
    ProgramContext(int width, int height);
    ~ProgramContext();

    SDL_Window *window;
    SDL_Renderer *renderer;
    int windowWidth, windowHeight;
    nsr::Scene scene;
};

}





#endif //PROGRAMCONTEXT_H
