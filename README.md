# Emulate 6502
An Emulator for the 6502, including RAM/ROM inspector, Register inspection and debugging features

## How to use
The emulator should be run from the command line. Use `./Emulate6502 --help` to see a list of available options.

## How to build
This project depends on the GTK 3 library and thus requires the library itself and the dev package to compile and run the project. In apt, these packages are called `libgtk-3` and `libgtk-3-dev` respectively. You can get the required C flags and library flags for building with `pkg-config --cflags gtk+-3-0` and `pkg-config --libs gtk+-3-0` respecively.

## Compromises
Considering that this is a limited emulation of the 6502 microprocessor, there will have to be some compromises made for simplicity or simply because there is no better option.

## Todo:
* Add compromises made for the emulation
* Explain the GUI
* Code the GUI
* Add a Makefile for easier building
* Actually complete the project