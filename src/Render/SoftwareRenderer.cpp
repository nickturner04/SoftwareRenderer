//
// Created by s5614562 on 06/03/25.
//

#include "Render/SoftwareRenderer.h"

#include <iostream>

#include "Simulation/Scene.h"

namespace nsr {

RenderScreen::RenderScreen(SDL_Renderer * renderer, const int _width, const int _height) {
    this->texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, _width, _height);
    this->width = _width;
    this->height = _height;
}
RenderScreen::~RenderScreen() {
    SDL_DestroyTexture(this->texture);
}

void RenderScreen::CopyTexture(SDL_Renderer *renderer, const SDL_Rect *dst) const {
    SDL_RenderCopy(renderer, this->texture, nullptr, dst);
}

Uint8 RenderScreen::floatToUint8(const float f) {
    return static_cast<Uint8>(f * 255);
}


Uint32 RenderScreen::ColourFormat(Vec3 colour) const{
    SDL_PixelFormat *format = SDL_AllocFormat(SDL_PIXELFORMAT_ARGB8888);
    const Uint32 result = SDL_MapRGB(format, floatToUint8(colour.x), floatToUint8(colour.y), floatToUint8(colour.z));
    SDL_FreeFormat(format);
    return result;
}

Uint32 RenderScreen::ColourFormat(Uint8 r, Uint8 g, Uint8 b, Uint8 a) const{
    SDL_PixelFormat *format = SDL_AllocFormat(SDL_PIXELFORMAT_ARGB8888);
    const Uint32 result = SDL_MapRGBA(format, r, g, b,a);
    SDL_FreeFormat(format);
    return result;
}



void RenderScreen::Render(const Scene &scene) const {
    void * pixelAddress;
    int pitch = this->width * static_cast<int>(sizeof(Uint32));
    SDL_LockTexture(texture,nullptr,&pixelAddress, & pitch);
    //Do Drawing

    auto * pixel = static_cast<Uint32*>(pixelAddress);
    //memset(pixel, 0, this->width * this->height * sizeof(Uint32));

    auto [transform, dimensions] = scene.camera;

    auto [xAxis, yAxis, zAxis] = transform.axes();

    Vec3 corner = transform.position - (xAxis * dimensions.x * .5f) - (yAxis * dimensions.y * .5f) + (zAxis * dimensions.z);

    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {

            //std::cout << "FORWARD: " << forward << " UP: " << up << " RIGHT: " << right << '\n';
            const auto screenX = static_cast<float>(i) / static_cast<float>(width);
            const auto screenY = static_cast<float>(j) / static_cast<float>(height);
            const auto fh = dimensions.y;
            const auto fw = dimensions.x;

            auto worldPoint = corner + xAxis * (fw * screenX)  + yAxis * (fh * screenY ) + zAxis;
            const auto dir = (worldPoint - transform.position).normalized();

            if(const auto hit = scene.Trace(transform.position, dir); hit.hit.hit) {
                const auto colour = scene.Shade(hit);
                *(pixel + (j * width + i)) = ColourFormat(colour * (zAxis.dot(hit.hit.normal.normalized())));
            }
            else {
                *(pixel + (j * width + i)) = 0xFF000000;
            }
        }
    }

    SDL_UnlockTexture(texture);
}



}
