#pragma once

#include <string>

class Gameboy;
class CPU;

static const char* PROMPT = "> ";

enum class Command {
    Step,
    Registers,

    Run100,
    Run1000,
    Run10000,

    Steps,
    Exit,
    Help,

    Unknown,
};

class Debugger {
public:
    Debugger(Gameboy& inGameboy);

    void cycle();

private:
    Command get_command() const;
    Command parse(std::string input) const;
    void execute(Command command);

    int steps = 0;
    int counter = 0;

    Gameboy& gameboy;
};
