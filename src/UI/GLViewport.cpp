#include "Interface/GLViewport.h"

#include <complex>
#include <ngl/ShaderLib.h>
#include <ngl/VAOPrimitives.h>
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

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);

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

    //Set Default shader properties

    ngl::ShaderLib::use(PBR);
    ngl::ShaderLib::setUniform("camPos", m_camera.getViewMatrix());
    ngl::ShaderLib::setUniform("lightPosition", 0.0f, 2.0f, 2.0f);
    ngl::ShaderLib::setUniform("lightColor", 400.0f, 400.0f, 400.0f);
    ngl::ShaderLib::setUniform("exposure", 2.2f);
    ngl::ShaderLib::setUniform("albedo", 0.950f, 0.71f, 0.29f);

    ngl::ShaderLib::setUniform("metallic", 1.02f);
    ngl::ShaderLib::setUniform("roughness", 0.38f);
    ngl::ShaderLib::setUniform("ao", 0.2f);
    ngl::VAOPrimitives::createTrianglePlane("floor", 20, 20, 1, 1, ngl::Vec3::up());

    ngl::ShaderLib::use(ngl::nglCheckerShader);
    ngl::ShaderLib::setUniform("lightDiffuse", 1.0f, 1.0f, 1.0f, 1.0f);
    ngl::ShaderLib::setUniform("checkOn", true);
    ngl::ShaderLib::setUniform("lightPos", 0.0f, 2.0f, 2.0f);
    ngl::ShaderLib::setUniform("colour1", 0.9f, 0.9f, 0.9f, 1.0f);
    ngl::ShaderLib::setUniform("colour2", 0.6f, 0.6f, 0.6f, 1.0f);
    ngl::ShaderLib::setUniform("checkSize", 60.0f);

}

void GLViewport::loadMatricesToShader(ngl::Mat4 &view, ngl::Mat4 &project ) {
    struct transform {
        ngl::Mat4 MVP;
        ngl::Mat4 NM;
        ngl::Mat4 M;
    };
    transform t;
    t.MVP = project * view;
    t.NM = view;
    t.M = ngl::Mat4();
    ngl::ShaderLib::use(PBR);
    ngl::ShaderLib::setUniformBuffer("TransformUBO",sizeof(transform),&t.MVP.m_00 );
}


void GLViewport::RenderScene() {
    glViewport(m_x, m_y, m_w, m_h);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    ngl::Mat4 project = m_camera.getProjectionMatrix();
    ngl::Mat4 view = m_camera.getViewMatrix();
    ngl::Mat3 normalMatrix = view;
    normalMatrix.inverse().transpose();

    loadMatricesToShader(view,project);
    ngl::VAOPrimitives::draw(ngl::teapot);
    auto tx = ngl::Mat4::translate(0.f,-0.45f,0.f);

    ngl::ShaderLib::use(ngl::nglCheckerShader);
    ngl::ShaderLib::setUniform("MVP", project * view * tx);
    ngl::ShaderLib::setUniform("normalMatrix", normalMatrix);


    ngl::ShaderLib::use(ngl::nglColourShader);

    ngl::VAOPrimitives::draw("floor");
}

}