#include <iostream>
#include <memory>
#include <SDL2/SDL.h>
#include<SDL2/SDL_image.h>

#include "ProgramContext.h"
#include "UserInterface.h"
#include "Viewport.h"
#include "Render/PolygonMesh.h"
#include "Simulation/Scene.h"
#include "Storage/WavefrontObject.h"

constexpr float turn = M_PIf32 * 2.f;

int main() {
    std::cout << "Testing Quaternions\n" << "Quaternion Test: " << TEST_QUATERNION() << std::endl;


    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);

    auto monkey = WavefrontObject("resources/meshes/monkey.obj");

    auto monkeyMesh = nsr::PolygonMesh(monkey);

    auto context = ProgramContext();
    auto ui = nsi::UserInterface(context);
    ui.BuildUI();

    Vec3 axis = (Vec3::Forward + Vec3::Up).normalized();
    context.scene.camera.transform.Translate(-Vec3::Forward * 20.f);

    Quaternion sRotation = Quaternion::AxisAngle(Vec3::Forward, turn * (.25 * .5) );

    //UP
    auto YSphere =  context.scene.AddSphere(Vec3(0,-3,0),1.0f, Vec3(0,1,0));
    //LEFT
    auto XSphere =  context.scene.AddSphere(Vec3(3,0,0),1.0f, Vec3(1,0,0));
    //Forward
    auto ZSphere = context.scene.AddSphere(Vec3(0,0,3),1.0f, Vec3(0,0,1));

    context.scene.AddSphere(Vec3(-6,-4.5,0),1.0f, Vec3(1,1,1));


    context.scene.AddTriangle(Vec3(0,0,0),Tri(Vec3(2.5,2.5,0),Vec3(-2.5,2.5f,0),Vec3(0,-2.5f,0)),Vec3(1,1,0));

    Transformation shapes;
    //shapes.Rotate(sRotation);

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

        //context.scene.camera.Rotate(Vec3::Up,deltaTime);

        auto [x, y, z] = shapes.axes();
        //std::cout << x << ", " << y << ", " << z << std::endl;
        YSphere.shape.transform = (y.normalized()) * 3.f;
        ZSphere.shape.transform = (z.normalized()) * 3.f;
        XSphere.shape.transform = x.normalized() * 3.f;
        ui.Draw({mouseXNew, mouseYNew, mouseXdelta, mouseYdelta,mouseState.buttons});
    }
    return 0;
}
