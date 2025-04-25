//
// Created by s5614562 on 05/03/25.
//

#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <string>
#include <unordered_map>
#include <vector>

#include "ProgramContext.h"
#include "Interface/GLViewport.h"

namespace nsi {

struct MouseState {
    int x;
    int y;
    int dx;
    int dy;
    Uint32 buttons;
};

struct Container {
    virtual ~Container() = default;

    int x;
    int y;
    int w;
    int h;

    virtual void Draw(SDL_Renderer * renderer,MouseState mouse_state) {};
    bool IsHovered(int mouseX, int mouseY) const;
};

class IconRegistry {
public:

    IconRegistry(ProgramContext &_context);

    ~IconRegistry();
    SDL_Texture * GetIcon(const std::string &iconPath);
    ProgramContext& context;
    std::unordered_map<std::string, SDL_Texture*> icons;
};

struct Button {
    Button(SDL_Texture* texture, std::string command);
    SDL_Texture* texture;
    std::string command;
};
struct Toolbar final : Container {
    void Draw(SDL_Renderer * renderer, MouseState mouse_state) override;
    void AddButton(IconRegistry& ir , const std::string &iconPath);
    int bw;
    int bh;
    std::vector<Button> buttons;
};

struct Picture final : Container {
    void Draw(SDL_Renderer * renderer, MouseState mouse_state) override;
    SDL_Texture* texture;
};



class UserInterface {
public:
    explicit UserInterface(ProgramContext& _programContext);
    ~UserInterface();
    void BuildUI();
    void Draw(MouseState mouse_state);
    void RegisterIcon(const std::string &iconPath) const;
    void AddPicture(const std::string &iconPath, int x, int y, int w, int h);
    void AddViewport(int x, int y, int w, int h, int x_internal, int y_internal);
    Toolbar * AddToolbar(int x, int y, int w, int h, int bw, int bh);

    ProgramContext& programContext;
    std::vector<Container*> containers;
    GLViewport m_viewport;
    IconRegistry* iconRegistry;
};

} // nsi

#endif //USERINTERFACE_H
