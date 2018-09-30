#include "debugger.h"

#include "gameboy.h"
#include "cpu/cpu.h"
#include "util/log.h"
#include "util/string.h"

#include <iostream>
#include <algorithm>

Debugger::Debugger(Gameboy& inGameboy, bool should_debug) :
    gameboy(inGameboy),
    enabled(should_debug)
{
}

void Debugger::cycle() {
    if (!enabled) return;

    steps++;

    if (breakpoint_addr != 0 && !debugger_enabled) {
        if (gameboy.cpu.pc.value() != breakpoint_addr) { return; }
        debugger_enabled = true;
    }

    if (breakpoint_value_addr != 0 && !debugger_enabled) {
        if (gameboy.mmu.read(breakpoint_value_addr) != breakpoint_value) { return; }
        breakpoint_value_addr = 0;
        breakpoint_value = 0;
        debugger_enabled = true;
    }

    if (!debugger_enabled) { return; }

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

        case CommandType::Run:
            debugger_enabled = false;
            return true;

        case CommandType::BreakAddr: command_breakaddr(command.args); break;
        case CommandType::BreakValue: command_breakvalue(command.args); break;
        case CommandType::Registers: command_registers(command.args); break;
        case CommandType::Flags: command_flags(command.args); break;
        case CommandType::Memory: command_memory(command.args); break;
        case CommandType::MemoryCell: command_memory_cell(command.args); break;
        case CommandType::Steps: command_steps(command.args); break;
        case CommandType::Log: command_log(command.args); break;
        case CommandType::Exit: command_exit(command.args); break;
        case CommandType::Help: command_help(command.args); break;

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
            } catch (std::invalid_argument&) {
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
    unused(args);

    printf("AF: %04X\n", gameboy.cpu.af.value());
    printf("BC: %04X\n", gameboy.cpu.bc.value());
    printf("DE: %04X\n", gameboy.cpu.de.value());
    printf("HL: %04X\n", gameboy.cpu.hl.value());
    printf("SP: %04X\n", gameboy.cpu.sp.value());
    printf("PC: %04X\n", gameboy.cpu.pc.value());
}

void Debugger::command_flags(Args args) {
    unused(args);

    printf("Zero: %d\n", gameboy.cpu.f.flag_zero_value());
    printf("Subtract: %d\n", gameboy.cpu.f.flag_subtract_value());
    printf("Half Carry: %d\n", gameboy.cpu.f.flag_half_carry_value());
    printf("Carry: %d\n", gameboy.cpu.f.flag_carry_value());
}

void Debugger::command_memory(Args args) {
    if (args.size() > 3) {
        log_error("Invalid arguments to command");
        return;
    }

    /* TODO: Error handling for mis-parsed arguments */
    u16 memory_location = static_cast<u16>(std::stoul(args[0], nullptr, 16));

    uint lines = 10;
    if (args.size() >= 2) {
        lines = static_cast<uint>(std::stoi(args[1]));
    }

    uint line_length = 16;
    if (args.size() == 3) {
        line_length = static_cast<uint>(std::stoul(args[2]));
    }

    for (uint i = 0; i < lines; i++) {
        Address addr = static_cast<u16>(memory_location + i * line_length);
        printf("0x%04X | ", addr.value());

        for (uint cell = 0; cell < line_length; cell++) {
            Address cell_addr = static_cast<u16>(addr.value() + cell);
            printf("%02X ", gameboy.mmu.read(cell_addr));
        }

        printf("\n");
    }
}

void Debugger::command_memory_cell(Args args) {
    if (args.size() != 1) {
        log_error("Invalid arguments to command");
        return;
    }

    u16 memory_location = static_cast<u16>(std::stoul(args[0], nullptr, 16));

    printf("0x%02X\n", gameboy.mmu.read(memory_location));
    return;
}

void Debugger::command_breakaddr(Args args) {
    if (args.size() != 1) {
        log_error("Invalid arguments to command");
        return;
    }

    u16 addr = static_cast<u16>(std::stoul(args[0], nullptr, 16));
    breakpoint_addr = addr;
    log_info("Breakpoint set for address 0x%04X", breakpoint_addr);
}

void Debugger::command_breakvalue(Args args) {
    if (args.size() != 2) {
        log_error("Invalid arguments to command");
        return;
    }

    u16 addr = static_cast<u16>(std::stoul(args[0], nullptr, 16));
    u8 value = static_cast<u8>(std::stoul(args[1], nullptr, 16));
    breakpoint_value_addr = addr;
    breakpoint_value = value;
    log_info("Breakpoint set for value 0x%02X at address 0x%04X", breakpoint_value, breakpoint_value_addr);
}

void Debugger::command_steps(Args args) {
    unused(args);

    printf("Steps: %d\n", steps);
}

void Debugger::command_log(Args args) {
    if (args.size() != 1) {
        log_error("Invalid arguments to command");
        return;
    }

    std::string desired_log_level = args[0];
    std::transform(desired_log_level.begin(), desired_log_level.end(), desired_log_level.begin(), ::tolower);

    if (desired_log_level == "none") {
        log_set_level(LogLevel::Error);
        printf("Log level: Error\n");
    } else if (desired_log_level == "error") {
        log_set_level(LogLevel::Error);
        printf("Log level: Error\n");
    } else if (desired_log_level == "debug") {
        log_set_level(LogLevel::Debug);
        printf("Log level: Debug\n");
    } else if (desired_log_level == "trace") {
        log_set_level(LogLevel::Trace);
        printf("Log level: Trace\n");
    } else {
        log_error("Invalid log level");
    }
}

void Debugger::command_exit(Args args) {
    unused(args);

    log_error("Exiting");
    exit(1);
}

void Debugger::command_help(Args args) {
    unused(args);

    printf("\n");
    printf("= Flow Control\n");
    printf("[s]tep $steps=1        Run $steps cycles\n");
    printf("[r]un                  Run until the next breakpoint\n");
    printf("breakaddr $addr        Set a breakpoint at $addr\n");
    printf("breakvalue $addr #n    Set a breakpoint at $addr\n");
    printf("\n");
    printf("= Debug Information\n");
    printf("registers              Print a dump of the CPU registers\n");
    printf("flags                  Print a dump of the CPU flags\n");
    printf("[mem]ory $start $lines Print a dump of memory from $start to $end\n");
    printf("[addr]ess $addr        Print the value of the memory at $addr\n");
    printf("\n");
    printf("= Other\n");
    printf("steps                  Print the number of steps so far\n");
    printf("help                   Print this help page\n");
    printf("exit                   Exit the emulator\n");
    printf("\n");
}

Command Debugger::get_command() {
    printf("%s", PROMPT);
    std::string input_line;
    std::getline(std::cin, input_line);
    return parse(input_line);
}

Command Debugger::parse(std::string input) {
    using std::string;
    using std::vector;

    vector<string> elems = split(input);

    /* If nothing was entered, repeat the last command */
    if (elems.size() < 1) return last_command;

    string cmd = elems[0];
    CommandType cmd_type = parse_command(cmd);

    vector<string> args(elems.begin() + 1, elems.end());

    last_command = Command { cmd_type, args };

    return { cmd_type, args };
}

CommandType Debugger::parse_command(std::string cmd) {
    std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);

    if (cmd == "step" || cmd == "s") return CommandType::Step;
    if (cmd == "run" || cmd == "r") return CommandType::Run;

    if (cmd == "breakaddr") return CommandType::BreakAddr;
    if (cmd == "breakvalue") return CommandType::BreakValue;

    if (cmd == "regs" || cmd == "registers") return CommandType::Registers;
    if (cmd == "flags") return CommandType::Flags;
    if (cmd == "memory" || cmd == "mem") return CommandType::Memory;
    if (cmd == "address" || cmd == "addr") return CommandType::MemoryCell;
    if (cmd == "steps") return CommandType::Steps;

    if (cmd == "log") return CommandType::Log;

    if (cmd == "exit") return CommandType::Exit;
    if (cmd == "help") return CommandType::Help;

    return CommandType::Unknown;
}
