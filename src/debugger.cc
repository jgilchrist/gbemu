#include "debugger.h"

#include "gameboy.h"
#include "cpu/cpu.h"
#include "util/log.h"
#include "util/string.h"

#include <iostream>

Debugger::Debugger(Gameboy& inGameboy) :
    gameboy(inGameboy)
{
}

void Debugger::cycle() {
    steps++;

    if (counter > 0) {
        counter--;
        return;
    }

    while (true) {
        Command cmd = get_command();

        execute(cmd);

        if (cmd.type == CommandType::Step) break;
    }
}

void Debugger::execute(Command command) {
    switch (command.type) {
        case CommandType::Step:
            command_step(command.args);
            return;

        case CommandType::Registers:
            command_registers(command.args);
            return;

        case CommandType::Steps:
            command_steps(command.args);
            return;

        case CommandType::Exit:
            command_exit(command.args);
            return;

        case CommandType::Help:
            command_help(command.args);
            return;

        case CommandType::Unknown:
            printf("Unknown command\n");
            return;
    }
}

void Debugger::command_step(Args args) {
}

void Debugger::command_registers(Args args) {
    printf("Registers:\n");
    printf("A: %02X | B: %02X | C: %02X | D: %02X | E: %02X | F: %02X\n",
        gameboy.cpu.a.value(),
        gameboy.cpu.b.value(),
        gameboy.cpu.c.value(),
        gameboy.cpu.d.value(),
        gameboy.cpu.e.value(),
        gameboy.cpu.f.value()
    );

    printf("HL: %02X\n", gameboy.cpu.hl.value());
    printf("SP: %02X\n", gameboy.cpu.sp.value());
    printf("PC: %02X\n", gameboy.cpu.pc.value());
}

void Debugger::command_steps(Args args) {
    printf("Steps: %d\n", steps);
}

void Debugger::command_exit(Args args) {
    log_error("Exiting");
    exit(1);
}

void Debugger::command_help(Args args) {
    printf("Commands:\n");
    printf("Step: Run a single cycle\n");
    printf("Exit: Exit the program\n");
}

Command Debugger::get_command() const {
    printf("%s", PROMPT);
    std::string input_line;
    std::getline(std::cin, input_line);
    return parse(input_line);
}

Command Debugger::parse(std::string input) const {
    using std::string;
    using std::vector;

    vector<string> elems = split(input);

    /* If nothing was entered, step */
    /* TODO: This could repeat the last command, similar to GDB */
    if (elems.size() < 1) return { CommandType::Step, vector<string>() };

    string cmd = elems[0];
    CommandType cmd_type = parse_command(cmd);

    vector<string> args(elems.begin() + 1, elems.end());

    return { cmd_type, args };
}

CommandType Debugger::parse_command(std::string cmd) const {
    std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);

    if (cmd == "step") return CommandType::Step;
    if (cmd == "regs") return CommandType::Registers;

    if (cmd == "steps") return CommandType::Steps;
    if (cmd == "exit") return CommandType::Exit;
    if (cmd == "help") return CommandType::Help;

    return CommandType::Unknown;
}
