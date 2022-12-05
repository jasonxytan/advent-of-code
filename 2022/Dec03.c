#include <stdio.h>
#include <inttypes.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    FILE *infile;
    infile = fopen(argv[1], "r");
    if (infile) {
        uint8_t occur[26*2] = {0};
        char s[100];
        uint32_t sum = 0;
        while (fscanf(infile, "%s", s) == 1)
        {
            /* PART 1 
            for (int i = 0; i < strlen(s)/2; i++)
            {
                occur[(s[i]>'Z')?(s[i]-'a'+26):(s[i]-'A')]++;
            }
            for (int i = strlen(s)/2; i < strlen(s); i++)
            {
                if (occur[(s[i]>'Z')?(s[i]-'a'+26):(s[i]-'A')] > 0)
                {
                    sum += (s[i]>'Z')?(s[i]-'a'+1):(s[i]-'A'+27);
                    break;
                }
            }
            */
            for (int i = 0; i < strlen(s); i++)
            {
                occur[(s[i]>'Z')?(s[i]-'a'+26):(s[i]-'A')]++;
            }

            fscanf(infile, "%s", s);
            for (int i = 0; i < strlen(s); i++)
            {
                if (occur[(s[i]>'Z')?(s[i]-'a'+26):(s[i]-'A')] > 0)
                {
                    occur[(s[i]>'Z')?(s[i]-'a'+26):(s[i]-'A')] = 0xFF;
                }
            }

            fscanf(infile, "%s", s);
            for (int i = 0; i < strlen(s); i++)
            {
                if (occur[(s[i]>'Z')?(s[i]-'a'+26):(s[i]-'A')] == 0xFF)
                {
                    sum += (s[i]>'Z')?(s[i]-'a'+1):(s[i]-'A'+27);
                    break;
                }
            }
            memset(occur, 0, 26*2);
        }
        printf("sum = %u\n", sum);
        fclose(infile);
    }
    return 0;
}
