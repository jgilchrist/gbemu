#include "debugger.h"

#include "gameboy.h"
#include "cpu/cpu.h"
#include "util/log.h"

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
        if (cmd == Command::Step ||
            cmd == Command::Run100 ||
            cmd == Command::Run1000 ||
            cmd == Command::Run10000) break;
    }
}

void Debugger::execute(Command command) {
    switch (command) {
        case Command::Step:
            return;

        case Command::Registers:
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
            return;

        case Command::Run100:
            printf("Running 100 cycles...\n");
            counter = 99;
            return;

        case Command::Run1000:
            printf("Running 1000 cycles...\n");
            counter = 999;
            return;

        case Command::Run10000:
            printf("Running 10000 cycles...\n");
            counter = 9999;
            return;

        case Command::Steps:
            printf("Steps: %d\n", steps);
            return;

        case Command::Exit:
            printf("Exiting...\n");
            exit(1);

        case Command::Help:
            printf("Commands:\n");
            printf("Step: Run a single cycle\n");
            printf("Exit: Exit the program\n");
            return;

        case Command::Unknown:
            printf("Unknown command\n");
            return;
    }
}

Command Debugger::get_command() const {
    printf("%s", PROMPT);
    std::string input_line;
    std::getline(std::cin, input_line);
    return parse(input_line);
}

Command Debugger::parse(std::string input) const {
    std::transform(input.begin(), input.end(), input.begin(), ::tolower);

    if (input == "") return Command::Step;
    if (input == "step") return Command::Step;
    if (input == "regs") return Command::Registers;

    if (input == "run100") return Command::Run100;
    if (input == "run1000") return Command::Run1000;
    if (input == "run10000") return Command::Run10000;

    if (input == "steps") return Command::Steps;
    if (input == "exit") return Command::Exit;
    if (input == "help") return Command::Help;

    return Command::Unknown;
}
