//
// Created by s5614562 on 06/03/25.
//

#ifndef SOFTWARERENDERER_H
#define SOFTWARERENDERER_H
#include <SDL_render.h>

#include "Simulation/Scene.h"

namespace nsr {

class SoftwareRenderer {

};

enum class RenderMode {
    FULL,POINT_LIST,BOUNDING_VOLUME
};

class RenderScreen {
public:
    RenderScreen(SDL_Renderer * renderer, int _width, int _height);
    ~RenderScreen();

    Uint32 ColourFormat(Vec3 colour) const;
    Uint32 ColourFormat(Uint8 r, Uint8 g, Uint8 b, Uint8 a) const;

    void Render(const Scene& scene) const;
    void CopyTexture(SDL_Renderer * renderer, const SDL_Rect * dst) const;
    static Uint8 floatToUint8(float f);
private:


    SDL_Texture *texture;
    int width, height;
};


void RenderToTexture(SDL_Texture * _texture, Scene _scene);

} // nsr

#endif //SOFTWARERENDERER_H
