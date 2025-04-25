#include <iostream>
#include <memory>
#include <SDL2/SDL.h>
#include<SDL2/SDL_image.h>

#include "ProgramContext.h"
#include "UserInterface.h"
#include "Render/PolygonMesh.h"
#include "Simulation/Scene.h"
#include "Storage/WavefrontObject.h"

constexpr float turn = M_PIf32 * 2.f;

int main() {
    std::cout << "Testing Quaternions\n" << "Quaternion Test: " << TEST_QUATERNION() << std::endl;


    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);

    auto monkey = WavefrontObject("resources/meshes/cube.obj");

    auto context = nsi::ProgramContext(800,600);
    auto ui = nsi::UserInterface(context);
    ui.BuildUI();

    context.m_scene.camera.transform.Translate(-Vec3::Forward * 10.f);

    Quaternion sRotation = Quaternion::AxisAngle(Vec3(1,0,0), turn * .5);

    //UP
    //auto YSphere =  context.scene.AddSphere(Vec3(0,-3,0),1.0f, Vec3(0,1,0));
    //LEFT
    //auto XSphere =  context.scene.AddSphere(Vec3(3,0,0),1.0f, Vec3(1,0,0));
    //Forward
    //auto ZSphere = context.scene.AddSphere(Vec3(0,0,3),1.0f, Vec3(0,0,1));


    IMeshData& meshData = monkey;
    auto &mesh = context.m_scene.AddPointMesh(Vec3(0,0,0),monkey);
    mesh.transformation.Scale(2.f);
    mesh.transformation.Rotate(sRotation);


    bool programRunning = true;
    nsi::MouseState mouseState = {0,0,0};

    auto mouseXOld = 0;
    auto mouseYOld = 0;
    auto mouseXNew = 0;
    auto mouseYNew = 0;

    const float deltaTime = .01f;

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
