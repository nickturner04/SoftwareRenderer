//
// Created by s5614562 on 25/04/25.
//

#ifndef GLVIEWPORT_H
#define GLVIEWPORT_H
#include "ProgramContext.h"

namespace nsi {
//Real Time Rendering viewport
class GLViewport {
public:
    GLViewport(int _x, int _y, int _w, int _h,int _wInternal, int _hInternal,ProgramContext & _context);
    ~GLViewport() = default;

    void RenderScene();
private:
    ProgramContext & m_context;

    int m_x;
    int m_y;
    int m_w;
    int m_h;
    int m_wInternal;
    int m_hInternal;
};

} // nsi

#endif //GLVIEWPORT_H
