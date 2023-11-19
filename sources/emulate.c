/*
 * emulate.c
 *
 *  Created on: 06.11.2023
 *      Author: keheck
 */
#include "emulate.h"
#include "main.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>

int8_t* emu_memory_map;
emulator_config* emu_config;

static int16_t program_counter;
static int8_t accumulator;
static int8_t x;
static int8_t y;
static int8_t stack_pointer;
static int8_t flags;

void emu_init(emulator_config* config) {
    freopen(NULL, "rb", stdin);
    emu_memory_map = calloc(MEMORY_SIZE, sizeof(int8_t));
    emu_config = config;
    int16_t offset = config->rom_offset;
    int8_t bytes_read = 0;
    int8_t* buffer = malloc(BUFFER_SIZE);

    program_counter = 0;
    accumulator = 0;
    x = 0;
    y = 0;
    stack_pointer = 0xFF;
    flags = 0;

    do {
        bytes_read = fread(buffer, sizeof(int8_t), BUFFER_SIZE, stdin);
        if(bytes_read + offset > MEMORY_SIZE) {
            printf("Count not initialize memory map: ROM was too large (at least %d bytes) to be put at address %x.\n", bytes_read, config->rom_offset);
            exit(1);
        }

        memcpy(emu_memory_map+offset, buffer, bytes_read);
        offset += bytes_read;
    } while(bytes_read == BUFFER_SIZE);

    FILE* f = fopen("/home/keheck/Schreibtisch/out.bin", "wb");
    fwrite(emu_memory_map, sizeof(int8_t), MEMORY_SIZE, f);
    fclose(f);
    free(emu_memory_map);
    free(config);
    free(buffer);
}


void step() {

}
