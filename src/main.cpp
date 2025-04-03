#include <iostream>
#include <memory>
#include <SDL2/SDL.h>
#include<SDL2/SDL_image.h>

#include "ProgramContext.h"
#include "UserInterface.h"
#include "Viewport.h"
#include "Simulation/Scene.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);


    auto context = ProgramContext();
    auto ui = nsi::UserInterface(context);
    ui.BuildUI();

    std::cout << context.scene.camera.transform.axes() << std::endl;

    //context.scene.camera.Rotate(Vec3::Up,M_PIf32/2.f);
    Vec3 fwd2 = Quaternion{0.7071068f,0.7071068f,0,0} * Vec3::Forward;

    std::cout << context.scene.camera.transform.axes() << std::endl;
    //UP
    context.scene.AddSphere(Vec3(0,3,0),1.0f, Vec3(0,1,0));
    //LEFT
    context.scene.AddSphere(Vec3(3,0,0),1.0f, Vec3(1,0,0));
    //Forward
    context.scene.AddSphere(Vec3(0,0,5),1.0f, Vec3(0,0,1));


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
