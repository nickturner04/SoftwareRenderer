//
// Created by s5614562 on 14/04/25.
//

#ifndef COMMANDS_H
#define COMMANDS_H
#include <any>
#include <functional>
#include <unordered_map>

#include "ProgramContext.h"

namespace nsi {

enum class ParamType {
    NSI_INT,NSI_FLOAT,NSI_FLOAT2,NSI_FLOAT3,NSI_STRING
};

union ParamValue {
    int intValue;
    float floatValue;
    Vec2 float2Value;
    Vec3 float3Value;
};

struct Parameter {
    explicit Parameter(std::string data);
    ParamType type;
    ParamValue value;
};

class Commands {


public:
    Commands();
    ProgramContext context;


    static void CmdsResetCamera(ProgramContext& context,std::vector<Parameter> parameters);
};

} // nsi

#endif //COMMANDS_H
