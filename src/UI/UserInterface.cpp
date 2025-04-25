#include "UserInterface.h"

#include <iostream>
#include <ostream>
#include <utility>
#include <SDL_image.h>
//
// Created by s5614562 on 05/03/25.
//
namespace nsi {

IconRegistry::IconRegistry(ProgramContext& _context): context(_context) {
    icons = std::unordered_map<std::string, SDL_Texture *>();
}

IconRegistry::~IconRegistry() {
    for (auto item : icons) {
        SDL_DestroyTexture(item.second);
    }
}

SDL_Texture * IconRegistry::GetIcon(const std::string &iconPath) {
    const std::string iconDir = "resources/ui/icons/";
    const std::string path = iconDir + iconPath;
    if(!icons.contains(path)) {
        SDL_Surface *surface = IMG_Load(path.c_str());
        SDL_Texture *texture = SDL_CreateTextureFromSurface(context.m_renderer, surface);
        SDL_FreeSurface(surface);
        icons.insert(std::pair(iconPath, texture));
        return texture;
    }
    return icons[path];
}

bool Container::IsHovered(const int mouseX, const int mouseY) const {
    if(mouseX >= x && mouseX <= w && mouseY >= y && mouseY <= h) {
        return true;
    }
    return false;
}


void Picture::Draw(SDL_Renderer * renderer, const MouseState mouse_state) {
    const SDL_Rect rect = {this->x, this->y, this->w, this->h };
    if(IsHovered(mouse_state.x, mouse_state.y)) {
        //std::cout << mouse_state.x << " " << mouse_state.y << std::endl;
    }
    SDL_RenderCopy(renderer, this->texture, nullptr, &rect);
}

bool RectIsHovered(const SDL_Rect rect , const int mouseX, const int mouseY) {

    if(mouseX >= rect.x && mouseX <= rect.x + rect.w && mouseY >= rect.y && mouseY <= rect.y + rect.h) {
        return true;
    }
    return false;
}

void Toolbar::Draw(SDL_Renderer *renderer, const MouseState mouse_state) {
    const SDL_Rect rect = {this->x, this->y, this->w * this->bw, this->h * this->bh};

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &rect);

    auto row = 0;
    for (int i = 0; i < this->buttons.size(); ++i) {
        SDL_Rect dst = {this->x + (this->bw * (i % w)),this->y + (this->bh * row),this->bw,this->bh};
        if((i + 1) % w == 0) {
            row += 1;
        }
        SDL_RenderCopy(renderer,this->buttons[i].texture,nullptr,&dst);
        if(RectIsHovered(dst,mouse_state.x, mouse_state.y)) {
            SDL_SetRenderDrawColor(renderer, 219, 200, 53, 255);
        }
        else {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        }

        SDL_RenderDrawRect(renderer,&dst);
    }
}

Button::Button(SDL_Texture *texture, std::string command) {
    this->texture = texture;
    this->command = std::move(command);
}


void Toolbar::AddButton(IconRegistry& ir, const std::string &iconPath) {
    const auto texture = ir.GetIcon(iconPath);
    buttons.emplace_back(texture,"setCamera 0 0 -20");
}



UserInterface::UserInterface(ProgramContext& _programContext): programContext(_programContext) {
    containers = std::vector<Container *>();
    iconRegistry = new IconRegistry(programContext);
}

UserInterface::~UserInterface() {
    for (const auto item : containers) {
        delete item;
    }
    delete iconRegistry;
}


void UserInterface::RegisterIcon(const std::string &iconPath) const {
    iconRegistry->GetIcon(iconPath);
}

void UserInterface::AddPicture(const std::string &iconPath, const int x, const int y, const int w, const int h) {
    const auto icon =  iconRegistry->GetIcon(iconPath);
    const auto picture = new Picture();
    picture->x = x;
    picture->y = y;
    picture->w = w;
    picture->h = h;
    picture->texture = icon;
    containers.push_back(picture);
}

Toolbar * UserInterface::AddToolbar(int x, int y, int w, int h, int bw, int bh) {
    const auto toolbar = new Toolbar();
    toolbar->x = x;
    toolbar->y = y;
    toolbar->w = w;
    toolbar->h = h;
    toolbar->bw = bw;
    toolbar->bh = bh;
    containers.push_back(toolbar);
    return toolbar;
}



void UserInterface::Draw(const MouseState mouse_state) const {
    const auto renderer = programContext.m_renderer;
    SDL_RenderClear(renderer);


    SDL_SetRenderDrawColor(renderer, 168, 167, 165, 255);
    SDL_RenderFillRect(renderer, nullptr);

    for(const auto item : containers) {
        item->Draw(renderer,mouse_state);
    }
    SDL_RenderPresent(renderer);
}

void UserInterface::BuildUI() {
    AddPicture("open.bmp",0,0,64,64);
    AddViewport(64,64,800-64,600-64, 400, 300);
    const auto tb = AddToolbar(0,65,2,32,32,32);
    for (int i = 0; i < 10; ++i) {
        tb->AddButton(*iconRegistry,"new.bmp");
    }
}


}
