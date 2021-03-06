#include <stdio.h>


int main() {
    printf("This program count how many times each letter occurs in given file and make histogram out of it.\n\n");
    FILE *file;
    char file_name[100];
    printf("Enter a valid name of a file:\n");
    gets(file_name);
    file = fopen(file_name, "r");
    int letter, letters[25], was_it[25] = { 0 };
    while ((letter = getc(file)) != EOF){
        if (letter > 64 && letter < 91){
            letter = letter + 32;
        }
        if (letter > 96 && letter < 123){
            if (was_it[letter - 97] != 1){
                letters[letter - 97] = 0;
                was_it[letter - 97] = 1;
            }
            letters[letter - 97] = letters[letter - 97] + 1;
        }
    }
    for (int i = 0; i < 25; i++){
        char tmp = i + 97;
        if (was_it[i] == 0){
            letters[i] = 0;
        }
        printf("Letter %c occurs %d times.\n", tmp, letters[i]);
    }
    printf("\nHistogram of letters:\n");
    for (int i = 0; i < 25; i++){
        char tmp = i + 97;
        printf("\n%c:", tmp);
        if (was_it[i] != 0) {
            for (int j = 0; j < letters[i]; j++) {
                printf("#");
            }
        }
    }
    return 0;
}
