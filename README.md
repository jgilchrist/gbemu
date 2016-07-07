# emulator

`emulator` is a Nintendo Game Boy emulator written in C++. Its goals are _code readability_ and _utilisation of modern C++_.

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
