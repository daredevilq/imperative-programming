#include <stdio.h>
#include <stdbool.h>

void wc(int *nl, int *nw, int *nc) {
    char c;
    int in_word = 0;
    *nl = *nw = *nc = 0;

    while ((c = fgetc(stdin)) != EOF) {
        (*nc)++;
    

        if (c == '\n') {
            (*nl)++;
        }

        if (c == ' ' || c == '\n' || c == '\t') {
            in_word = 0;
        } 
        else if (in_word==0) {
            in_word = 1;
            (*nw)++;
        }
    }

    // Increment line count if the last character in the input is not a newline
    if (*nc > 0 && (*nc - 1) != '\n') {
        (*nl)++;
    }
}

int main() {
    int nl, nw, nc;
    wc(&nl, &nw, &nc);
    int a=110;
    char abc=a;
    printf("%c",abc);
    
    printf("%d %d %d\n", nl, nw, nc);
    return 0;
}