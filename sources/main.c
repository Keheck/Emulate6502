#include <stdlib.h>
#include <argp.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "main.h"

static void check_and_assign(char* arg, uint16_t* destination, char* name, struct argp_state* state) {
	char* end;
	int val = strtol(arg, &end, 16);
	if(end[0] != 0)
	    argp_error(state, "Address for %s has to be a hexadecimal number, instead got %s!", name, arg);
	if(val < 0 || val > 0xFFFF)
	    argp_failure(state, -1, 0, "Address for %s has to be between 0x0000 and 0xFFFF inclusive, got %x instead!", name, val);
	*destination = val;
}

static error_t parse(int key, char* arg, struct argp_state* state) {
    struct emulator_config* config = (struct emulator_config*)state->input;

    switch(key) {
        case 'v':
            config->virt_rom = 1;
            break;
        case 's':
            check_and_assign(arg, &(config->stdout_address), "stdout", state);
            break;
        case 'o':
            check_and_assign(arg, &(config->rom_offset), "ROM offset", state);
            break;
        case 'i':
        	check_and_assign(arg, &(config->irq_override), "IRQ vector", state);
        	break;
        case 'r':
            check_and_assign(arg, &(config->rdy_override), "RDY vector", state);
            break;
        case 'n':
            check_and_assign(arg, &(config->nmi_override), "NMI vector", state);
            break;
        default:
            return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

int main (int argc, char *argv[])
{
    struct argp_option options[7];
    memset(options, 0, sizeof(options));
    options[0].name = "virtual";
    options[0].key = 'v';
    options[0].doc = "If set, writing to an address that maps to the ROM will will not be discarded. Is idempotent. "
    		"Any arguments associated with this flag are ignored.";

    options[1].name = "offset";
    options[1].key = 'o';
    options[1].doc = "The address at which the first byte of the ROM will be found.";
    options[1].arg = "address";

    options[2].name = "stdout";
    options[2].key = 's';
    options[2].doc = "The address which will output any bytes written to it to stdout.";
    options[2].arg = "address";

    options[3].name = "irq";
    options[3].key = 'i';
    options[3].doc = "Setting this flag will instruct the emulator to directly set a vector for the IRQ handler to FFFA/FFFB after the ROM has been loaded.";
    options[3].arg = "vector";

    options[4].name = "rdy";
    options[4].key = 'r';
    options[4].doc = "Setting this flag will instruct the emulator to directly set a vector for RDY to FFFC/FFFD after the ROM has been loaded.";
    options[4].arg = "vector";

    options[5].name = "nmi";
    options[5].key = 'n';
    options[5].doc = "Setting this flag will instruct the emulator to directly set a vector for the NMI handler to FFFE/FFFF after the ROM has been loaded.";
    options[5].arg = "vector";

    struct argp parser;
    memset(&parser, 0, sizeof(parser));
    parser.doc = "Emulates the MCS6502 microprocessor from MOS Technology\v"
    		"To provide a ROM to the emulator, use the < or | operator to redirect the content of your ROM to stdin.\n"
    		"\x1b[31mNote: When setting any of the vector flags, they will overwrite data that has been written to their associated addresses. "
    		"For simplicity reasons, using FFFF as a value for these vectors will result in them being ignored."
    		"\x1b[0m";
    parser.options = options;
    parser.parser = parse;
    struct emulator_config conf = CONFIG_DEFAULT;
    argp_parse(&parser, argc, argv, 0, 0, &conf);
    printf("rom_offset: %x\n", conf.rom_offset);
    printf("stdout_address: %x\n", conf.stdout_address);
    printf("irq_override: %x\n", conf.irq_override);
    printf("rdy_override: %x\n", conf.rdy_override);
    printf("nmi_override: %x\n", conf.nmi_override);
    printf("virt_rom: %s\n", conf.virt_rom ? "yes" : "no");
    return 0;
}


