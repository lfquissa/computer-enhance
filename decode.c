#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>

typedef uint8_t u8;

const char *reg_names[2][8] = {
                                 {"al", "cl", "dl", "bl", "ah", "ch", "dh", "bh"},
                                 {"ax", "cx", "dx", "bx", "sp", "bp", "si", "di"}
                              };

int main(int argc, char * argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./decode <file>\n");
        exit(1);
    }

    u8 buffer[2];
    FILE * f = fopen(argv[1], "r");

    while (fread(buffer, sizeof(char), sizeof(buffer), f) == sizeof(buffer))
    {
        u8 opcode = (buffer[0] & 0b11111100) >> 2;
        u8 d   = (buffer[0] & 0b10 ) >> 1;
        u8 w   = (buffer[0] & 0b1  );
        u8 mod = (buffer[1] & 0b11000000) >> 6;
        (void) mod;
        u8 reg = (buffer[1] & 0b00111000) >> 3;
        u8 r_m = (buffer[1] & 0b00000111);

        if (opcode == 0b100010)
        {
            if (d == 1)
                printf("mov %s, %s\n", reg_names[w][reg], reg_names[w][r_m]);
            else
                printf("mov %s, %s\n", reg_names[w][r_m], reg_names[w][reg]);
        }
    }
}
