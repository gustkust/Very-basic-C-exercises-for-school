#include <stdio.h>

int main() {
    unsigned int x;
    int i, a[99];
    printf("give positive number:\n");
    scanf("%d", &x);
    for (i = 0; x > 0; i++){
        a[i] = x & 1;
        x = x >> 1;
    }
if (a[0] == 1 && a[1] == 1 && a[2] == 0 && a[3] == 1){
printf("\nnumber does have 1101 at the oldest positions");
}
else{
printf("number does not have 1101 at the oldest positions");
}
return 0;
}
