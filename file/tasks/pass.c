#include <stdio.h>
#include <string.h>



int main () {
    char code[8], s[40];
    int count = 0, ccount = 0, pass = 1;
    scanf("%s %s", code, s);

    for (int i = 0; i < strlen(code); i++) {
        for (int j = count; j <= strlen(s); j++) {
            if (j == strlen(s)) {
                pass = 0;
                count = j;
                break;
            }

            if (code[i] == s[j]) {
                count = j+1;
                break;
            } else {
                for (int k = i; k < strlen(code); k++) {
                    if (code[k] == s[j]) {
                        pass = 0;
                    }
                }
            }
        count = j;
        }
    }
    switch (pass) {
        case 0:
            printf("FAIL\n");
            break;
        case 1:
            printf("PASS\n");
            break;
    }
    return 0;

}
