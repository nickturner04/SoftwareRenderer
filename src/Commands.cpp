#include "Interface/Commands.h"
//
// Created by s5614562 on 14/04/25.
//
namespace nsi {
Commands::Commands() {

}

Commands::~Commands() {
    for (const auto& pair: commands) {
        delete pair.second;
    }
}


void SplitString(const std::string &s, char delim, std::vector<std::string> &elems) {
    s.find(delim);
}


bool Command::CheckParameters(const std::vector<Parameter>& parameters) const {
    if(parameters.size() < m_minParameters)return false;
    return true;
}

void Commands::ResetCamera(ProgramContext &context) {
    context.m_scene.camera.Reset();
}



}