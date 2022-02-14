#include <stdio.h>
#include <string.h>
#include "barcode.h"

int barcode_search(char barcode[], char menu[], product_info pro_info[], int product) {
    char words[30], words2[30];
    char *search = barcode;

    //Open file to search in
    FILE *f = fopen("C:\\tmp\\file\\seventh_gen\\head\\database.txt", "r");

    //scan words and compare to the barcode
    while (fscanf(f, "%s", words)>0) {
        // Compares two strings, outputs 0 when they match
        if (strcmp(words, search)==0) {
            fscanf(f, "%s", pro_info[product].name);
            fscanf(f, "%s", pro_info[product].category);
            printf("The product %s, is now in category: %s\n", pro_info[product].name, pro_info[product].category);
            break;

        } else if (strcmp(words, "stop") == 0) {
            printf("%s is not found.\n",search); //Skrevet af Johannes --slut--
            return 0;
        }
    }
    return 1;
}


