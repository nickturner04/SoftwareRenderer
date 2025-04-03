#include <iostream>
#include <memory>
#include <SDL2/SDL.h>
#include<SDL2/SDL_image.h>

#include "ProgramContext.h"
#include "UserInterface.h"
#include "Simulation/Scene.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);


    auto context = ProgramContext();
    auto ui = nsi::UserInterface(context);
    ui.BuildUI();
    context.scene.AddSphere(Vec3(-2,0,5),1.0f, Vec3(1.f,0,0));
    context.scene.AddSphere(Vec3(2,0,5),1.0f, Vec3(0,0,1.f));
    context.scene.AddSphere(Vec3(0,0,5),1.0f, Vec3(0,1.f,0));


    context.scene.AddTriangle(Vec3(-1,2,5),Tri(Vec3(-.5f,-.5f,0),Vec3(0,.5f,0),Vec3(.5f,-.5f,0)),Vec3(1,0,0));



    bool programRunning = true;
    nsi::MouseState mouseState = {0,0,0};

    auto mouseXOld = 0;
    auto mouseYOld = 0;
    auto mouseXNew = 0;
    auto mouseYNew = 0;

    while (programRunning) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                programRunning = false;
            }
        }
        mouseXOld = mouseXNew;
        mouseYOld = mouseYNew;
        mouseState.buttons = SDL_GetMouseState(&mouseXNew, &mouseYNew);

        const auto mouseXdelta = mouseXNew - mouseXOld;
        const auto mouseYdelta = mouseYNew - mouseYOld;


        ui.Draw({mouseXNew, mouseYNew, mouseXdelta, mouseYdelta,mouseState.buttons});
    }
    return 0;
}
