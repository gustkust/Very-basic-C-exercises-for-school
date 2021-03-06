#include <stdio.h>
#include <string.h>
FILE* file;
struct worker {
    char name[16];
    char surname[64];
    long long int id;
};
struct worker workers[100];
int workers_number = 0;
int str_to_int(char* (str)) {
    int result = 0;
    int i = 0;
    while (str[i] != '\0' && str[i] != '\n') {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    return result;
}
long long int str_to_long_int(char* (str)) {
    long long int result = 0;
    int i = 0;
    while (str[i] != '\0' && str[i] != '\n') {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    return result;
}



void option_a() {
    struct worker new_worker;
    printf("Type name:\n");
@@ -71,47 +70,47 @@
        }
    }
}
void option_d() {
    char ssurname[64];
    int i, z = 0;
    printf("Type surname of worker to delete:\n");
    scanf_s("%s", ssurname);
    for (i = 0; i < workers_number; i++) {
        if (strcmp(workers[i].surname, ssurname) == 0) {
            z++;
        }
        else {
            workers[i - z] = workers[i];
        }
    }
    workers_number--;
}
void option_e() {
    int i;
    fopen_s(&file, "file.txt", "w");
    fprintf(file, "%d\n", workers_number);
    for (i = 0; i < workers_number; i++) {
        fprintf(file, "%s\n", workers[i].name);
        fprintf(file, "%s\n", workers[i].surname);
        fprintf(file, "%lld\n", workers[i].id);
    }
    fclose(file);
    printf("Done.\n");
}
void option_f() {
    fopen_s(&file, "file.txt", "r");
    char num_str[128];
    int i;
    fgets(num_str, 128, file);
    workers_number = str_to_int(num_str);
    for (i = 0; i < workers_number; i++) {
        char nname[16], nsurname[64], nid_str[100];
        char nid_str[100];
        long long int nid;
        struct worker new_worker;
        fgets(new_worker.name, 16, file);
        new_worker.name[strlen(new_worker.name) - 1] = '\0';
        fgets(new_worker.surname, 64, file);
        new_worker.surname[strlen(new_worker.surname) - 1] = '\0';
        fgets(nid_str, 100, file);
        nid = str_to_long_int(nid_str);
        new_worker.id = nid;
        workers[i] = new_worker;
    }
    printf("Done.\n");
}


int main() {
    option_f();
    option_b();
    char option = 'g';
    int was = 1;
    printf("Choose option: a, b, c, d, e, f\n");
    while (option < 104 && option > 96) {
        char option = 'g';
        scanf_s("%c", &option);
        if (was == 1) {
            was = 0;
        }
        else {
            printf("Choose option: a, b, c, d, e, f\n");
        }
        if (option == '\n') scanf_s("%c", &option);
        if (option > 104 || option < 96){
            return 0;
        }
        switch (option) {
        case 97:
            option_a();
            break;
        case 98:
            option_b();
            break;
        case 99:
            option_c();
            break;
        case 100:
            option_d();
            break;
        case 101:
            option_e();
            break;
        case 102:
            option_f();
            break;
        }
    }
    return 0;
}
