//
// Created by s5614562 on 05/03/25.
//

#include "ProgramContext.h"
#include <ngl/NGLInit.h>
namespace nsi {

ProgramContext::ProgramContext(const int width, const int height) {
    windowWidth = width;
    windowHeight = height;
    m_window = SDL_CreateWindow("Window",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    m_glContext = SDL_GL_CreateContext(m_window);
    SDL_GL_MakeCurrent(m_window, m_glContext);
    SDL_GL_SetSwapInterval(1);
    ngl::NGLInit::initialize();
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
}
ProgramContext::~ProgramContext() {
    SDL_DestroyWindow(m_window);
    SDL_DestroyRenderer(m_renderer);
}
}



