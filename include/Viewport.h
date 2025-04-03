//
// Created by s5614562 on 05/03/25.
//

#ifndef VIEWPORT_H
#define VIEWPORT_H
#include "Simulation/Scene.h"
#include "UserInterface.h"
#include "Render/SoftwareRenderer.h"

namespace nsi {

class Viewport : public Container{
    public:
    Viewport(int x, int y, int w, int h,int x_internal, int y_internal,ProgramContext & context);
    ~Viewport();
    void Draw(SDL_Renderer *renderer, MouseState mouse_state) override;
    nsr::Scene * scene = nullptr;
    nsr::RenderScreen * screen;
};

} // nsi

#endif //VIEWPORT_H
