#include <stdio.h>
#include <inttypes.h>

int main(int argc, char const *argv[])
{
    FILE *infile;
    infile = fopen(argv[1], "r");
    if (infile) {
        char op = 0;
        char rps = 0;
        uint32_t score = 0;
        while (fscanf(infile, "%c %c\n", &op, &rps) == 2)
        {
            // score += rps - 'W' + 3 * ((rps-op-1)%3); // part 1
            score += (3+op + rps-'Y' - 'A')%3+1 + 3*(rps-'X'); // part 2
        }
        printf("score = %u\n", score);
        fclose(infile);
    }
    return 0;
}
