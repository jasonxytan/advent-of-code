#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>

struct dir {
    char name[32]; // assume directory name is at most 32 bytes otherwise things would get nasty if using char * and then malloc/free
    uint32_t file_size;
    uint32_t subdir_num;
    struct dir *subdir;
    struct dir *parent;
};

uint32_t smallest = 0;
uint32_t threshold = 0;

uint32_t calculate_total_size(struct dir *dir, uint32_t *sum, int free_flag)
{
    uint32_t total = dir->file_size;
    if (dir->subdir_num > 0)
    {
        for (uint32_t i = 0; i < dir->subdir_num; i++)
        {
            total += calculate_total_size(&dir->subdir[i], sum, free_flag);
        }
    }
    if (total <= 100000)
    {
        *sum += total;
    }
    if (total >= threshold && total < smallest)
    {
        smallest = total;
    }
    if (free_flag)
    {
        free(dir->subdir);
    }
    return total;
}

int main(int argc, char const *argv[])
{
    FILE *infile;
    infile = fopen(argv[1], "r");
    if (infile) {
        char line[50];
        struct dir root = {0};
        struct dir *current_dir = &root;
        char cmd[3];
        char dir[32];
        char size[15];
        char name[32];
        int ret;
        while (fgets(line, sizeof(line), infile) != NULL)
        {   
            if (line[0] == '$') // cd xxx or ls
            {
                sscanf(line, "$ %s %s\n", cmd, dir);
                if (strcmp(cmd, "cd") == 0)
                {
                    if (strcmp(dir, "/") == 0)
                    {
                        current_dir = &root;
                    }
                    else if (strcmp(dir, "..") == 0)
                    {
                        current_dir = current_dir->parent;
                    }
                    else
                    { // assume we always ls before cd into any subdir, i.e., subdir exists
                        for (uint32_t i = 0; i < current_dir->subdir_num; i++)
                        {
                            if (strcmp(dir, current_dir->subdir[i].name) == 0)
                            {
                                current_dir = &current_dir->subdir[i];
                                break;
                            }
                        }
                    }
                }
                else if (strcmp(cmd, "ls") == 0)
                {
                    continue;
                }
                else
                {
                    printf("Invalid input!\n");
                }
            }
            else // result of ls
            {
                sscanf(line, "%s %s\n", size, name);
                if (strcmp(size, "dir") == 0)
                {
                    current_dir->subdir_num++;
                    current_dir->subdir = realloc(current_dir->subdir, current_dir->subdir_num * sizeof(*current_dir->subdir));
                    if (current_dir->subdir == NULL)
                    {
                        printf("Running out of heap\n");
                        return 1;
                    }
                    struct dir *new = &current_dir->subdir[current_dir->subdir_num-1];
                    memset(new, 0, sizeof(*new));
                    strcpy(new->name, name);
                    new->parent = current_dir;
                }
                else
                {
                    current_dir->file_size += atoi(size);
                }
            }
        }
        
        uint32_t sum = 0;
        threshold =  calculate_total_size(&root, &sum, 0) - (70000000 - 30000000);
        printf("threshold = %u\n", threshold);
        // printf("sum = %u\n", sum);
        smallest = -1;
        calculate_total_size(&root, &sum, 1);
        printf("smallest = %u\n", smallest);
        fclose(infile);
    }
    return 0;
}