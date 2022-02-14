#include <stdio.h>
#include <string.h>
#include "barcode.h"
#include "date_funcs.h"
#include "sort.h"
#include "menu_opt.h"



int menuopt1_input(product_info pro_info[], int count2){
    char barcode[40], menu[40];
    int semi = 0, *p, a = 0, b = 1;

    for(int product = count2; product < 40; product++) { //Her laver vi et loup for hvert produkt der indskrives
        printf("\nOptions\n [1] Input via barcode\n [2] Input manually\n [3] Back to menu\n");
        scanf("%d", &a);
        if (a == 1) {
            //get barcode from user
            printf("\nInput barcode to search for: " );
            scanf("%s", barcode);
            for (int i = 0; i < 10 && barcode_search(barcode, menu, pro_info, product) == 0; i++) {
                printf("Error couldn't find barcode in database, try again: ");
                scanf("%s", barcode);
            }

        } else if (a == 2) {
            printf("\nEnter name of the product without spaces [x for exit to menu]: ");
            scanf("%s", menu); // Her scanner vi navnet på varen og indsætter det i en char string og ikke i vores struct.
            if (strcmp(menu,"x") == 0){
                break;
            } // For hvis man så skriver x for exit, vil x forblive i vores struct.
            for (int i = 0; i < 10 && b == 1; i++) { // Derfor indsætter vi indholdet fra menu ind i vores struct med strcpy vi låner fra string.h biblioteket, først efter. Se under switch.
                printf("Enter the category:\n [1] Fruit and vegetables\n [2] Bakery\n [3] Meat\n [4] Dairy\n [5] Vegan products\n [6] Others\n");
                scanf("%d", &semi);
                switch(semi) { // Vi benytter her en switch til indsættelse af kategori, scanner en integer og indsætter den i "semi". Switchen kigger så på semi og undersøger om den passer til en case.
                    case 1: // Hvis semi er '1' går vi ind i første case
                        strcpy(pro_info[product].category, "Fruit_and_vegetables"); //vi benytter strcpy fra string.h biblioteket for at indsætte kategorien i vores struct.
                        printf("The product %s, is now in category: Fruit and vegetables\n", menu);
                        b = 0;
                        break; // så break'er vi loop'et.
                    case 2:
                        strcpy(pro_info[product].category, "Bakery"); // Samme gør vi for alle kategorierne
                        printf("The product %s, is now in category: Bakery\n", menu);
                        b = 0;
                        break;
                    case 3:
                        strcpy(pro_info[product].category, "Meat");
                        printf("The product %s, is now in category: Meat\n", menu);
                        b = 0;
                        break;
                    case 4:
                        strcpy(pro_info[product].category, "Dairy");
                        printf("The product %s, is now in category: Dairy\n", menu);
                        b = 0;
                        break;
                    case 5:
                        strcpy(pro_info[product].category, "Vegan");
                        printf("The product %s, is now in category: Vegan products\n", menu);
                        b = 0;
                        break;
                    case 6:
                        strcpy(pro_info[product].category, "Others");
                        printf("The product %s, is now in category: Others\n", menu);
                        b = 0;
                        break;
                    default: //Til sidst har vi en default der aktiveres hvis ingen af casesne matcher "semi". Og fordi b forbliver 1 forsætter loop'et.
                        printf("Error, incorret input.\n");
                }
            } //Udenom har vi et forloop der køre så længe b er 1, der er dog en stopklods på 10 fejlforsøg.
            b = 1;
            strcpy(pro_info[product].name, menu);
        } else if (a == 3) {
            break;
        } else {
            printf("Error\n");
            for (int i = 0; i < 10 && (a < 1 || a > 3); i++) {
                printf("Enter name of the product[x for exit to menu]: ");
                scanf("%s", menu);
                if (strcmp(menu,"x") == 0){
                    break;
                }
            }
            break;
        }


        printf("Enter the expiry date [DD/MM/YYYY]: ");
        scanf("%d/%d/%d", &pro_info[product].day, &pro_info[product].mon, &pro_info[product].year);

        while (valid_date(pro_info[product].day, pro_info[product].mon, pro_info[product].year) == 0 && semi < 10){ // her tjekker vi om det er en valid dato.
            // Hvis funktionen valid_date returner 1 er den valid 0 er den ikke.
            if (valid_date(pro_info[product].day, pro_info[product].mon, pro_info[product].year) == 0) {
                 printf("The date is invalid, try again[DD/MM/YYYY]:");
                 scanf("%d/%d/%d", &pro_info[product].day, &pro_info[product].mon, &pro_info[product].year);
                 semi++;
            } else {
                 break;
            }
        }
        semi = 0;


        p = time_to_expiry(pro_info[product].day, pro_info[product].mon, pro_info[product].year);
        //funktion der udregner tid til udløb indsættes i array p
        pro_info[product].day_diff = *(p); //her refereres til første led i p, hvilket er dagene til udløb
        pro_info[product].mon_diff = *(p+1); //her refereres til andet led i p, hvilket er månederne til udløb
        pro_info[product].year_diff = *(p+2); //her refereres til tredje led i p, hvilket er årene til udløb


        count2++;
        sort(pro_info, count2); //sortering af producter så producter der udgår først kommer øverst
        printf("\n");
        output_products(pro_info, count2);


    }
    return count2;
}


int menuopt2_delete(struct product_info pro_info[], int count2) {
    int delete = 0;

    printf("\n");
    output_products(pro_info, count2);
    printf("\nInput products number to delete product[press 0 for exit to menu]:");
    scanf("%d", &delete);

    if (delete-1 >= 0) {
        printf("The %s has been deleted.\n", pro_info[delete-1].name);
        for (int i = delete-1; i < count2; i++) {
            if (i == count2) {
                strcpy(pro_info[i].name, "0");
                strcpy(pro_info[i].category, "0");
                pro_info[i].day = 0;
                pro_info[i].mon = 0;
                pro_info[i].year = 0;
                pro_info[i].day_diff = 0;
                pro_info[i].mon_diff = 0;
                pro_info[i].year_diff = 0;
            } else {
                strcpy(pro_info[i].name, pro_info[i+1].name);
                strcpy(pro_info[i].category, pro_info[i+1].category);
                pro_info[i].day = pro_info[i+1].day;
                pro_info[i].mon = pro_info[i+1].mon;
                pro_info[i].year = pro_info[i+1].year;
                pro_info[i].day_diff = pro_info[i+1].day_diff;
                pro_info[i].mon_diff = pro_info[i+1].mon_diff;
                pro_info[i].year_diff = pro_info[i+1].year_diff;
            }
        }
        count2--;
    } else {
        printf("No product was deleted.\n");
    }
    return count2;


}


void menuopt3_list_products(struct product_info pro_info[], int count2){
  int *p, semi = 0, b = 1, a = 0;


    printf("\n");
    output_products(pro_info, count2);
    while (a != 3) {
        printf("\nOptions:\n [1] Change expiry date of product\n [2] Change category of product\n [3] Exit to menu\n");
        scanf("%d", &a);
        if (a == 1) {
            printf("\nInput product number to change products expiry date[press 0 to exit]: ");
            scanf("%d", &b);
            if (b == 0) {
                break;
            }
            for (int i = 0; (b > count2 || b < 0) && i <= 10; i++) {
                printf("Invalid product try again:");
                scanf("%d", &b);
            }
            printf("\nYou are now changing the expiry date of %s\nInput the date like DD/MM/YYYY: ", pro_info[b-1].name);
            scanf("%d/%d/%d", &pro_info[b-1].day, &pro_info[b-1].mon, &pro_info[b-1].year);
            for(int i = 0; valid_date(pro_info[b-1].day, pro_info[b-1].mon, pro_info[b-1].year) == 0 && i < 10; i++) {
                printf("Invalid date try again[DD/MM/YYYY]: ");
                scanf("%d/%d/%d", &pro_info[b-1].day, &pro_info[b-1].mon, &pro_info[b-1].year);
            }
            p = time_to_expiry(pro_info[b-1].day, pro_info[b-1].mon, pro_info[b-1].year); //funktion der udregner tid til udløb indsættes i array p
            pro_info[b-1].day_diff = *(p); //her refereres til første led i p, hvilket er dagene til udløb
            pro_info[b-1].mon_diff = *(p+1); //her refereres til andet led i p, hvilket er månederne til udløb
            pro_info[b-1].year_diff = *(p+2); //her refereres til tredje led i p, hvilket er årene til udløb
            printf("You have now changed the %s's expiry date to %d/%d/%d, it now expires in %d day(s), %d month(s) and %d year(s)\n",
                pro_info[b-1].name, pro_info[b-1].day, pro_info[b-1].mon, pro_info[b-1].year,
                pro_info[b-1].day_diff, pro_info[b-1].mon_diff, pro_info[b-1].year_diff);
            sort(pro_info, count2);
            b = 1;
        } else if (a == 2) {
            printf("Input product number to change product category: ");
            scanf("%d", &semi);
            printf("You are now changing the category of %s.\n", pro_info[semi-1].name);
            printf("Enter the category:\n [1] Fruit and vegetables\n [2] Bakery\n [3] Meat\n [4] Dairy\n [5] Vegan products\n [6] Others\n");
            scanf("%d", &b);
            switch(b) {
                case 1:
                    strcpy(pro_info[semi - 1].category, "Fruit_and_vegetables");
                    printf("The product %s, is now in category: Fruit and vegetables\n", pro_info[semi - 1].name);
                    b = 0;
                    break;

                case 2:
                    strcpy(pro_info[semi - 1].category, "Bakery");
                    printf("The product %s, is now in category: Bakery\n", pro_info[semi - 1].name);
                    b = 0;
                    break;

                case 3:
                    strcpy(pro_info[semi - 1].category, "Meat");
                    printf("The product %s, is now in category: Meat\n", pro_info[semi - 1].name);
                    b = 0;
                    break;

                case 4:
                    strcpy(pro_info[semi - 1].category, "Dairy");
                    printf("The product %s, is now in category: Dairy\n", pro_info[semi - 1].name);
                    b = 0;
                    break;

                case 5:
                    strcpy(pro_info[semi - 1].category, "Vegan");
                    printf("The product %s, is now in category: Vegan products\n", pro_info[semi - 1].name);
                    b = 0;
                    break;

                case 6:
                    strcpy(pro_info[semi - 1].category, "Others");
                    printf("The product %s, is now in category: Others\n", pro_info[semi - 1].name);
                    b = 0;
                    break;

                default:
                    printf("Error!\n");
            }

            b = 1;
            semi = 0;
        } else if (a == 3) {
            break;
        } else {
            printf("Error try again.\n");
        }
    } a = 0;
}
