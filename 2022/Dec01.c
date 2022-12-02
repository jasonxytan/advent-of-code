#include <stdio.h>
#include <inttypes.h>

int main(int argc, char const *argv[])
{
    FILE *infile;
    infile = fopen(argv[1], "r");
    if (infile) {
        uint32_t num = 0;
        uint32_t sum = 0;
        uint32_t max = sum;
        uint32_t sec = sum;
        uint32_t thd = sum;
        int c = 0;
        while(1) {
            while(1) {
                fscanf(infile, "%u", &num);
                printf("%u\n", num);
                sum += num;
                c = fgetc(infile);
                if (c == EOF) {
                    if (sum >= max) {
                        thd = sec;
                        sec = max;
                        max = sum;
                    }
                    else if (sum >= sec) {
                        thd = sec;
                        sec = sum;
                    }
                    else if (sum >= thd) {
                        thd = sum;
                    }
                    fclose(infile);
                    printf("max = %u\n", max+sec+thd);
                    return 0;
                }
                else if((char)c == '\n') {
                    c = fgetc(infile);
                    if (c == EOF) {
                        if (sum >= max) {
                            thd = sec;
                            sec = max;
                            max = sum;
                        }
                        else if (sum >= sec) {
                            thd = sec;
                            sec = sum;
                        }
                        else if (sum >= thd) {
                            thd = sum;
                        }
                        fclose(infile);
                        printf("max = %u\n", max+sec+thd);
                        return 0;
                    }
                    else if ((char)c == '\n') {
                        break;
                    }
                    else {
                        ungetc(c, infile);
                    }
                }
            }
            
            if (sum >= max) {
                thd = sec;
                sec = max;
                max = sum;
            }
            else if (sum >= sec) {
                thd = sec;
                sec = sum;
            }
            else if (sum >= thd) {
                thd = sum;
            }
            sum = 0;
            printf("\n");
        }
    }
    return 0;
}
