#include <stdio.h>
#include "barcode.h"
#include "date_funcs.h"
#include "data_handling.h"


int load_data(product_info load[]){

    FILE * fpointer; //Her laver vi en file pointer.
    int pronumb = 1;
  	int *p;

        fpointer = fopen("C:\\tmp\\file\\seventh_gen\\head\\storage.txt", "r"); // Her åbner vi vores txt fil vi gemmer vores data i, og får vores file pointer til at pege på den.
    fscanf(fpointer, "%d", &pronumb); // Her scanner vi første værdi i txt filen hvilket altid er antal produkter. Efter incrementer pointeren med 1 og peger automatisk på næste værdi.
    for (int i = 0; i < pronumb; i++) { // Forloop'et køre antal gange lig med antal produkter, og scaner ind i structets produktnavne.
        fscanf(fpointer, "%s", load[i].name);
    }
    for (int i = 0; i < pronumb; i++) {
        fscanf(fpointer, "%d", &load[i].day); // -||- , og scaner ind i structets udløbsdag.
    }
    for (int i = 0; i < pronumb; i++) {
        fscanf(fpointer, "%d", &load[i].mon); // -||- , og scaner ind i structets udløbsmåned.
    }
    for (int i = 0; i < pronumb; i++) {
        fscanf(fpointer, "%d", &load[i].year); // -||- , og scaner ind i structets udløbsår.
    }
    for (int i = 0; i < pronumb; i++) {
        fscanf(fpointer, "%s", load[i].category); // -||- , og scaner ind i structets kategori.
    }
    for (int i = 0; i < pronumb; i++) {
        p = time_to_expiry(load[i].day, load[i].mon, load[i].year); //funktion der udregner tid til udløb indsættes i pointer p
        load[i].day_diff = *(p); //her refereres til første led i p, hvilket er dagene til udløb
        load[i].mon_diff = *(p+1); //her refereres til andet led i p, hvilket er månederne til udløb
        load[i].year_diff = *(p+2); //her refereres til tredje led i p, hvilket er årene til udløb
    }
    fclose(fpointer);
    return pronumb;
}


void save_data(struct product_info load[], int count2){

    FILE * fpointer;

    fpointer = fopen("C:\\tmp\\file\\seventh_gen\\head\\storage.txt", "w");
    fprintf(fpointer, "%d\n", count2);
    for (int i = 0; i < count2; i++) {
        fprintf(fpointer, "%s\n", load[i].name);
    }
    for (int i = 0; i < count2; i++) {
        fprintf(fpointer, "%d\n", load[i].day);
    }
    for (int i = 0; i < count2; i++) {
        fprintf(fpointer, "%d\n", load[i].mon);
    }
    for (int i = 0; i < count2; i++) {
        fprintf(fpointer, "%d\n", load[i].year);
    }
    for (int i = 0; i < count2; i++) {
        fprintf(fpointer, "%s\n", load[i].category);
    }
    for (int i = 0; i < count2; i++) {
        fprintf(fpointer, "Produkt %s, udløbsdato: %d/%d/%d tid til udløb: %d dag(e), %d måned(er) og %d år\n",
            load[i].name, load[i].day, load[i].mon, load[i].year, load[i].day_diff, load[i].mon_diff, load[i].year_diff);
    }
    fclose(fpointer);

}
