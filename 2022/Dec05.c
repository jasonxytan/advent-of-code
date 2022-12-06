#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>

struct node
{
    char crate;
    struct node *next;
};

int main(int argc, char const *argv[])
{
    FILE *infile;
    infile = fopen(argv[1], "r");
    if (infile) {
        uint32_t num;
        char c;
        while((c = fgetc(infile)) != '1') {}
        while(fscanf(infile, "%u", &num) == 1) {}
        rewind(infile);

        struct node *heads[num];
        memset(heads, 0, sizeof(heads));

        struct node *tails[num];
        char s[4*num+1];
        while (*fgets(s, 4*num+1, infile) == '[') {
            for (int i = 0; i < num; i++) {
                if(s[4*i+1] != ' ') {
                    if(heads[i] == NULL) {
                        tails[i] = malloc(sizeof(struct node));
                        tails[i]->crate = s[4*i+1];
                        tails[i]->next = NULL;
                        heads[i] = tails[i];
                    }
                    else {
                        tails[i]->next = malloc(sizeof(struct node));
                        tails[i]->next->crate = s[4*i+1];
                        tails[i]->next->next = NULL;
                        tails[i] = tails[i]->next;
                    }
                }
            }
        }

        uint32_t n, src, dest;
        while(fscanf(infile, " move %u from %u to %u", &n, &src, &dest) == 3) {
            printf("n=%u, src=%u, dest=%u\n", n, src, dest);
            // PART 1
            // for (int i = 0; i < n; i++) {
            //     struct node *temp = heads[src-1];
            //     heads[src-1] = temp->next;
            //     temp->next = heads[dest-1];
            //     heads[dest-1] = temp;
            // }

            // PART 2
            struct node *temp = heads[src-1];
            for (int i = 0; i < n-1; i++) {
                temp = temp->next;
            }
            struct node *nd = temp->next;
            temp->next = heads[dest-1];
            heads[dest-1] = heads[src-1];
            heads[src-1] = nd;
        }

        struct node *nd;
        for (int i = 0; i < num; i++) {
            nd = heads[i];
            printf("[%c] ", nd->crate);
            while(nd != NULL){
                struct node *temp = nd->next;
                free(nd);
                nd = temp;
            }
        }

        fclose(infile);
    }
    return 0;
}