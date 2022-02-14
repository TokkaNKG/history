#include <stdio.h>
#include <time.h>
#include "./head/data_handling.h"
#include "./head/menu_opt.h"
#include "./head/sort.h"



int main () {

    int menuin = 0;
  	int count2 = 0; // Her definerer vi udløbsdatoen

    product_info pro_info[40];

  	time_t raw; //definere vi gerne vil have et tids int
    time(&raw); //laver raw til sekunder siden 1/1/1900
  	struct tm *time = localtime(&raw); /*struct tm *time function laver en struct vi kalder time,
        hvor funktionen gør det muligt at pege på specifikt på fx måned på året siden 1/1/1900*/
    while (menuin != 4) { /*her loop'er vi vores menu, så vi hele tiden vender tilbage hertil.
        Medmindre vores input er 4 for så stopper programmet.*/

        printf("\nCurrent date: %d/%d/%d\n",time->tm_mday, time->tm_mon+1, time->tm_year+1900); /*vi addere måned med 1 fordi c tæller månederne fra 0 til 11,
            vi addere år med 1900, fordi c tæller antal år fra 1900*/

        count2 = load_data(pro_info); // Her henter vi dataene fra vores txt fil. Funktionen returnere antallet af produkter i vores køleskab.
        sort(pro_info, count2);

        printf("\nMenu: \n [1] Input product \n [2] Delete product \n [3] List products\n [4] Exit \n");
        scanf("%d", &menuin); //Her scanner vi vores menu input.
        if (menuin == 1) {
            count2 = menuopt1_input(pro_info, count2); // Her kalder vi funktionen til at indsætte produkter, den returnere antallet af produkter og putter det i count2.

        } else if (menuin == 2) {
            count2 = menuopt2_delete(pro_info, count2); // Her kalder vi funktionen til at fjerne produkter, den returnere antallet af produkter og putter det i count2.

        } else if (menuin == 3) {
            menuopt3_list_products(pro_info, count2);// Her kalder vi funktionen til at vise produkter.

        } else if (menuin == 4){
            break; // Her stopper vi programmet
        } else { // En else der tjekker om input er forkert
            printf("Error, try again:\n");
        }

        save_data(pro_info, count2);
        menuin = 0;
    }
    return 0;
}
