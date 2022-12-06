#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

int main(int argc, char const *argv[])
{
    FILE *infile;
    infile = fopen(argv[1], "r");
    if (infile) {
        
        // PART 1

        // uint32_t num = 0;
        // int a = fgetc(infile);
        // num++;
        // int b = 0;
        // int c = 0;
        // int d = 0;
        // while(1) {
        //     if (b == 0) {
        //         b = fgetc(infile);
        //         num++;
        //         if(a == b)
        //         {
        //             a = b;
        //             b = 0;
        //             continue;
        //         }
        //     }

        //     if (c == 0) {
        //         c = fgetc(infile);
        //         num++;
        //         if (c == b) {
        //             a = c;
        //             b = 0;
        //             c = 0;
        //             continue;
        //         }
        //         else if (c == a) {
        //             a = b;
        //             b = c;
        //             c = 0;
        //             continue;
        //         }
        //     }
        //     if (d == 0) {
        //         d = fgetc(infile);
        //         num++;
        //         if (d == c) {
        //             a = d;
        //             b = 0;
        //             c = 0;
        //             d = 0;
        //             continue;
        //         }
        //         else if (d == b) {
        //             a = c;
        //             b = d;
        //             c = 0;
        //             d = 0;
        //             continue;
        //         }
        //         else if (d == a) {
        //             a = b;
        //             b = c;
        //             c = d;
        //             d = 0;
        //             continue;
        //         }
        //     }

        //     printf("num = %u\n", num);
        //     break;
        // }


        // PART 2
        uint32_t num = 0;
        int cont_flag = 0;
        int end_flag = 1;
        int arr[14] = {0};
        arr[0] = fgetc(infile);
        num++;
        while (1)
        {
            for (int i = 1; i < sizeof(arr)/sizeof(int); i++)
            {
                if (arr[i] == 0)
                {
                    arr[i] = fgetc(infile);
                    num++;
                    for (int j = 0; j < i; j++)
                    {
                        if (arr[i] == arr[j])
                        {
                            for (int k = 0; k < sizeof(arr)/sizeof(int); k++)
                            {
                                if (k+j+1<sizeof(arr)/sizeof(int))
                                {
                                    arr[k] = arr[k+j+1];
                                }
                                else
                                {
                                    arr[k] = 0;
                                }
                            }
                            cont_flag = 1;
                            break;
                        }
                    }
                    end_flag = 1;
                    if (cont_flag)
                    {
                        end_flag = 0;
                        cont_flag = 0;
                        break;
                    }
                }
            }
            if (end_flag)
            {
                printf("num = %u\n", num);
                break;
            }
        }

        fclose(infile);
    }
    return 0;
}