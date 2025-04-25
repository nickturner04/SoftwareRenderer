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
    ProgramContext() = delete;
    ProgramContext(int width, int height);
    ~ProgramContext();

    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    SDL_GLContext m_glContext;
    int windowWidth, windowHeight;
    nsr::Scene m_scene;
};

}





#endif //PROGRAMCONTEXT_H
