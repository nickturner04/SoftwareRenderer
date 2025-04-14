//
// Created by s5614562 on 14/04/25.
//

#ifndef COMMANDS_H
#define COMMANDS_H
#include <functional>
#include <unordered_map>

#include "ProgramContext.h"

namespace nsi {

class Commands {


public:
    Commands();
    ProgramContext context;

    static void CmdsResetCamera(ProgramContext& context,...);
};

} // nsi

#endif //COMMANDS_H
