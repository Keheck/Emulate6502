/*
 * emulate.h
 *
 *  Created on: 06.11.2023
 *      Author: keheck
 */

#ifndef HEADERS_EMULATE_H_
#define HEADERS_EMULATE_H_

#include <stdint.h>
#include <stdlib.h>
#include "main.h"

extern int8_t* emu_memory_map;
extern emulator_config* emu_config;

#define BUFFER_SIZE 64
#define MEMORY_SIZE 65536

void emu_init(emulator_config* config);
void step();

#endif /* HEADERS_EMULATE_H_ */
