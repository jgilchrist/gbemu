#pragma once

#include "definitions.h"
#include "options.h"

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
    Debugger(Gameboy& inGameboy, Options& inOptions);

    void set_enabled(bool enabled);
    void cycle();

private:
    Gameboy& gameboy;
    Options& options;

    Command last_command;

    auto get_command() -> Command;

    auto execute(const Command& command) -> bool;

    /* Commands */
    auto command_step(Args args) -> bool;

    void command_registers(const Args& args);
    void command_flags(const Args& args);
    void command_memory(Args args);
    void command_memory_cell(Args args);

    void command_breakaddr(Args args);
    void command_breakvalue(Args args);

    static void command_log(Args args);

    void command_steps(const Args& args);
    static void command_exit(const Args& args);
    static void command_help(const Args& args);

    auto parse(const std::string& input) -> Command;
    static auto parse_command(std::string cmd) -> CommandType;

    bool enabled;

    int steps = 0;
    uint counter = 0;

    u16 breakpoint_addr = 0;
    u16 breakpoint_value_addr = 0;
    u8 breakpoint_value = 0;
    bool debugger_enabled = true;
};
