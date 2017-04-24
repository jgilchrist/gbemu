#pragma once

#include "definitions.h"

#include <string>
#include <vector>

class Gameboy;
class CPU;

static const char* PROMPT = "> ";

enum class CommandType {
    Step,
    Run,

    BreakAddr,
    BreakValue,

    Registers,
    Flags,
    Memory,
    MemoryCell,
    Steps,

    Log,

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
    Debugger(Gameboy& inGameboy, bool should_debug);

    void cycle();

private:
    Gameboy& gameboy;
    Command last_command;

    Command get_command();

    bool execute(Command command);

    /* Commands */
    bool command_step(Args args);

    void command_registers(Args args);
    void command_flags(Args args);
    void command_memory(Args args);
    void command_memory_cell(Args args);

    void command_breakaddr(Args args);
    void command_breakvalue(Args args);

    void command_log(Args args);

    void command_steps(Args args);
    void command_exit(Args args);
    void command_help(Args args);

    Command parse(std::string input);
    CommandType parse_command(std::string cmd);

    bool enabled;

    int steps = 0;
    uint counter = 0;

    u16 breakpoint_addr = 0;
    u16 breakpoint_value_addr = 0;
    u8 breakpoint_value = 0;
    bool debugger_enabled = true;
};
