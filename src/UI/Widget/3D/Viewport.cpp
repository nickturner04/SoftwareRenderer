//
// Created by s5614562 on 05/03/25.
//
#include "Viewport.h"

#include <iostream>
#include <SDL_mouse.h>

namespace nsi {

Viewport::Viewport(int x, int y, int w, int h,int x_internal, int y_internal,ProgramContext& context) {
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    screen = new  nsr::RenderScreen(context.renderer,x_internal,y_internal);;
    scene = &context.scene;
}

Viewport::~Viewport() {
    delete screen;
}



void Viewport::Draw(SDL_Renderer *renderer, MouseState mouse_state) {
    const SDL_Rect rect = { x, y, w, h };
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &rect);
    nsr::Camera & camera =  scene->camera;

    if(IsHovered(mouse_state.x, mouse_state.y)) {
        if(mouse_state.buttons & SDL_BUTTON_LEFT) {
            const Quaternion q1 = Quaternion::AxisAngle({1,0,0},mouse_state.dx);
            const Quaternion q2 = Quaternion::AxisAngle({0,1,0},mouse_state.dy);
            const Quaternion q3 = q1 * q2;
            //std::cout << q3 << '\n';
            std::cout << "Old Direction: " << camera.direction;
            camera.direction = q3 * camera.direction;
            std::cout << "New Direction: " << camera.direction << '\n';
        }
        else if(mouse_state.buttons & SDL_BUTTON(2)) {
            camera.origin.x += static_cast<float>(mouse_state.dx) * 0.01f;
            camera.origin.y += static_cast<float>(mouse_state.dy) * 0.01f;
        }
        else if(mouse_state.buttons & SDL_BUTTON(3)) {
            camera.origin.z += static_cast<float>(mouse_state.dy) * 0.01f;
        }
    }
    screen->Render(*scene);
    screen->CopyTexture(renderer, &rect);
}

void UserInterface::AddViewport(int x, int y, int w, int h,int x_internal, int y_internal) {
    auto *viewport = new Viewport(x,y,w,h,x_internal,y_internal,programContext);
    containers.push_back(viewport);
}


} // nsi