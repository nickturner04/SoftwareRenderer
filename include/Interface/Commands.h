//
// Created by s5614562 on 14/04/25.
//

#ifndef COMMANDS_H
#define COMMANDS_H
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

class Command {
public:
    virtual ~Command() = default;
    std::vector<Parameter> m_Parameters;
    uint32_t m_minParameters;

    virtual void Execute(ProgramContext& context, std::vector<Parameter> parameters) = 0;

private:
    [[nodiscard]] bool CheckParameters(const std::vector<Parameter>& parameters) const;
};

void SplitString(const std::string& s, char delim, std::vector<std::string>& elems);

class Commands {
public:
    Commands();
    ~Commands();
    ProgramContext context;
    std::unordered_map<std::string, Command*> commands;

    void ExecuteCommand(ProgramContext& context ,std::string_view command) {

    }

    static void ResetCamera(ProgramContext& context);
};



} // nsi

#endif //COMMANDS_H
