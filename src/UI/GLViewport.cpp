#include "Interface/GLViewport.h"
#include <ngl/ShaderLib.h>
//
// Created by s5614562 on 25/04/25.
//
constexpr auto PBR = "PBR";

namespace nsi {

GLViewport::GLViewport(int _x, int _y, int _w, int _h,int _wInternal, int _hInternal,ProgramContext & _context): m_context(_context) {
    m_x = _x;
    m_y = _y;
    m_w = _w;
    m_h = _h;
    m_wInternal = _wInternal;
    m_hInternal = _hInternal;

    constexpr auto vertexShader = "PBRVertex";
    constexpr auto fragmentShader = "PBRFragment";

    ngl::ShaderLib::createShaderProgram(PBR);
    ngl::ShaderLib::attachShader(vertexShader,ngl::ShaderType::VERTEX);
    ngl::ShaderLib::attachShader(fragmentShader,ngl::ShaderType::FRAGMENT);

    ngl::ShaderLib::loadShaderSource(vertexShader,"resources/shaders/PBRVertex.glsl");
    ngl::ShaderLib::loadShaderSource(fragmentShader,"resources/shaders/PBRFragment.glsl");

    ngl::ShaderLib::compileShader(vertexShader);
    ngl::ShaderLib::compileShader(fragmentShader);

    ngl::ShaderLib::attachShaderToProgram(PBR,vertexShader);
    ngl::ShaderLib::attachShaderToProgram(PBR,fragmentShader);

    ngl::ShaderLib::linkProgramObject(PBR);

}


void GLViewport::RenderScene() {

}

}