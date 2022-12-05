#include <stdio.h>
#include <inttypes.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    FILE *infile;
    infile = fopen(argv[1], "r");
    if (infile) {
        uint32_t low1, high1, low2, high2;
        uint32_t num = 0;
        while (fscanf(infile, "%u-%u,%u-%u\n", &low1, &high1, &low2, &high2) == 4) {
            // if (((int)low1-(int)low2)*((int)high1-(int)high2) <= 0) { // PART 1
            if (!(low1 > high2 || low2 > high1)) { // PART 2
                num++;
            }
        }
        printf("#pairs = %u\n", num);
        fclose(infile);
    }
    return 0;
}