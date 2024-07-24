#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>

#define MAX_SIZE 1024
typedef uint8_t u8;

const char *reg_names[2][8] = {
                                 {"al", "cl", "dl", "bl", "ah", "ch", "dh", "bh"},
                                 {"ax", "cx", "dx", "bx", "sp", "bp", "si", "di"}
                              };
u8 buffer[MAX_SIZE];

int main(int argc, char * argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./decode <file>\n");
        exit(1);
    }

    FILE * f = fopen(argv[1], "r");

    size_t sz = fread(buffer, sizeof(char), sizeof(buffer), f);
    size_t pc = 0;

    printf("bits 16\n");
    while (pc != sz)
    {
        u8 *inst = &buffer[pc]; 
        u8 opcode = (inst[0] & 0b11111100) >> 2;
        u8 d   = (inst[0] & 0b10 ) >> 1;
        u8 w   = (inst[0] & 0b1  );
        u8 mod = (inst[1] & 0b11000000) >> 6;
        u8 reg = (inst[1] & 0b00111000) >> 3;
        u8 r_m = (inst[1] & 0b00000111);

        if (opcode == 0b100010)
        {
            if (mod == 0b11)
            {
                if (d == 1)
                    printf("mov %s, %s\n", reg_names[w][reg], reg_names[w][r_m]);
                else
                    printf("mov %s, %s\n", reg_names[w][r_m], reg_names[w][reg]);
                pc += 2;
            }

        }

        else if ( (inst[0] >> 4) == 0b1011)
        {
            w   = (inst[0] & 0b1000) >> 3;
            reg = (inst[0] & 0b111);

            short data;
            if (w == 1)
            {
                data = (inst[2] << 8) | inst[1];
                pc += 3;
            }
            else
            {
                data = inst[1];
                pc += 2;
            }

            printf("mov %s, %hu\n", reg_names[w][reg], data);
        }
    }
}
