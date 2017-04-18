# emulator

`emulator` is a Nintendo Game Boy emulator written in C++. Its goals are _code readability_ and _utilisation of modern C++_.

### Progress

| #   | CPU Test            | Status |
| --- | ---                 | ---    |
| 01  | special             | ❌      |
| 02  | interrupts          | ❌      |
| 03  | op sp,hl            | ✅      |
| 04  | op r,imm            | ❌      |
| 05  | op rp               | ✅      |
| 06  | ld r,r              | ✅      |
| 07  | jr,jp,call,ret,rst  | ✅      |
| 08  | misc                | ❌      |
| 09  | op r,r              | ❌      |
| 10  | bit ops             | ✅      |
| 11  | op a,(hl)           | ❌      |

### Build Instructions

##### OSX & Linux

- Install [`libsfml`][sfml]
- Run `make`

[sfml]: http://www.sfml-dev.org

### Usage

##### Running a game

```sh
$ ./build/emulator rom_file
```

##### Using the integrated debugger

```sh
$ ./build/emulator rom_file -d
```
