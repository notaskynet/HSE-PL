#include <stdlib.h>
#include <stdio.h>

#define ALPH_SIZE 26


void charToCesarCipher(char ch, int key) {
    char temp;

    if((ch >= 'a') && (ch <= 'z')) {
        temp = 'a';
        temp += (int) 'a' + ((int) ch - (int) 'a' + key) % ALPH_SIZE;
        putchar(ch);
    } else if ((ch >= 'A') && (ch <= 'Z')) {
        temp = 'A';
        temp += (int) 'A' + ((int) ch - (int) 'A' + key) % ALPH_SIZE;
        putchar(ch);
    } else {
        putchar(ch);
    }
}


int main(int argc, char **argv) {
    int key; char ch;

    if (argc == 1) {
        key = 3;
    } else {
        key = atoi(argv[1]);
    }
    do {
        ch = getchar();
        charToCesarCipher(ch, key);
    } while(ch != '\n');

    return 0;
}
