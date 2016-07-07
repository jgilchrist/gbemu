#pragma once

#include "definitions.h"

#include <string>
#include <vector>

class Gameboy;
class CPU;

static const char* PROMPT = "> ";

enum class CommandType {
    Step,

    Registers,

    Steps,
    Exit,
    Help,

    Unknown,
};

using Args = std::vector<std::string>;

struct Command {
    CommandType type;
    Args args;
};

class Debugger {
public:
    Debugger(Gameboy& inGameboy);

    void cycle();

private:
    Command get_command() const;

    bool execute(Command command);

    /* Commands */
    bool command_step(Args args);
    void command_registers(Args args);
    void command_steps(Args args);
    void command_exit(Args args);
    void command_help(Args args);

    Command parse(std::string input) const;
    CommandType parse_command(std::string cmd) const;


    int steps = 0;
    uint counter = 0;

    Gameboy& gameboy;
};
