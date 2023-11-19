/*
 * main.h
 *
 *  Created on: 06.11.2023
 *      Author: keheck
 */
#ifndef HEADERS_MAIN_H_
#define HEADERS_MAIN_H_

#include <stdint.h>

typedef struct emulator_config {
    uint16_t rom_offset;
    uint16_t stdout_address;
    uint16_t irq_override;
    uint16_t rdy_override;
    uint16_t nmi_override;
    uint8_t virt_rom;
}emulator_config;

#define CONFIG_DEFAULT {0, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0}

#endif /* HEADERS_MAIN_H_ */
