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

        bool should_continue = execute(cmd);

        if (should_continue) break;
    }
}

bool Debugger::execute(Command command) {
    switch (command.type) {
        case CommandType::Step:
            /* Note: 'Step' allows the program to break
             * out of the debugger loop so the boolean
             * return value of this function is returned */
            return command_step(command.args);

        case CommandType::Registers:
            command_registers(command.args);
            break;

        case CommandType::Steps:
            command_steps(command.args);
            break;

        case CommandType::Exit:
            command_exit(command.args);
            break;

        case CommandType::Help:
            command_help(command.args);
            break;

        case CommandType::Unknown:
            printf("Unknown command\n");
            break;
    }

    return false;
}

bool Debugger::command_step(Args args) {
    switch (args.size()) {
        case 0:
            return true;
        case 1:
            /* TODO: Clean this up
             * Try/catch should be moved somewhere (could use optional?)
             * Should be able to avoid subtracting 1 */
            try {
                int nsteps = std::stoi(args[0]);
                if (nsteps == 0) {
                    log_error("Cannot step zero times");
                    return false;
                }
                if (nsteps < 0) {
                    log_error("Cannot step a negative number of times");
                    return false;
                }
                counter = static_cast<uint>(nsteps - 1);
            } catch (std::invalid_argument) {
                log_error("Invalid number of steps: %s", args[0].c_str());
                /* If an invalid argument was encountered, the program
                 * should not step at all, thus false is returned */
                return false;
            }
            return true;
        default:
            log_error("Invalid arguments to 'step'");
            return false;
    }
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
