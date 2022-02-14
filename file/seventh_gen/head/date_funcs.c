#include <stdio.h>
#include <string.h>
#include <time.h>
#include "barcode.h"
#include "date_funcs.h"


int * time_to_expiry(int day, int mon, int year) {
    static int return_value[3]; //her laver vi et array til antal dage, måneder, år fra nuværende dato,

	  time_t raw;
      time(&raw);
	  struct tm *time = localtime(&raw); //Vi låner en funktion fra time.h biblioteket. Den gør det muligt at finde den nuværende dato.

		if (day < time->tm_mday) { //her tjekker vi om vi skal "låne" dage fra den tidligere måned.
  			if (mon== 3) { //her låner vi dage fra februar.
    				if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) { //tjekker om det er skudår, hvis det er skud år er februar 29 dage lang.
    				      day += 29;
    				} else {
    				      day += 28;
    				}
  			} else if (mon == 5 || mon == 7 || mon == 10 || mon == 12) { //her låner vi dage fra april, juni, september eller november da de alle har 30 dage i måneden.
  				    day += 30;
  			} else { //her låner vi dage fra alle andre måneder der alle har 31 dage.
  				    day += 31;
  			}
  			mon -= 1; //her minusser vi med en måned fordi vi har "lånt" dens dage.
		}
		if (mon < time->tm_mon+1) { // Her "låner" vi måneder fra året hvis udløbsdatoens måned er mindre end den nuværende.
  			year -= 1;
  			mon += 12;
		}

		return_value[0] = day - time->tm_mday; //nuværende dag trækkes fra udløbsdagen resultatet puttes i arrayet på 0 plads
		return_value[1] = mon - (time->tm_mon+1); //nuværende måned trækkes fra udløbsmåneden resultatet puttes i arrayet på 1 plads
		return_value[2] = year - (time->tm_year+1900); //nuværende år trækkes fra udløbsår resultatet puttes i arrayet på 2 plads

		return return_value;
}

int valid_date(int day, int mon, int year) {
    //Funktionen tester om datoen er valid. Den returnere 1 hvis den er valid og 0 hvis den er forkert.

    int is_leap = 0; // Vi bruger en integer en til at holde styr på om det er skudår.

  	if (year >= 1800 && year <= 9999) {
        //Her tjekker vi det brugerindtastede årstal, og giver det en ramme, for hvis det ikke er indenfor antages det at være en fejl.
    	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
            //Tjekker om det er skudår, og gør isleap til 1 (true).
            is_leap = 1;
        }
    	if (mon >= 1 && mon <= 12) { // Tjekker om måned er indenfor 1 og 12 da der kun er 12 måneder på året.
      		if (mon == 2) { // Vi tjekker for hver måned om dagen passer indenfor den specifikke måned.
                if (is_leap == 1 && day == 29) { //Tjekker om det er skudår.
                    //Stadig valid date.
                } else if (is_leap == 0 && day > 28) { //Tjekker efterfølgende for alle måneder.
                    return 0;
                }
            } else if ((mon == 4 || mon == 6 || mon == 9 || mon == 11) && day > 30) {
                    return 0;
            }
            if (day > 31 || day < 1) { //for resten af månederne er der 31 dage.
      				return 0;
      		}
        } else {
    		    return 0;
        }
  	} else {
        return 0;
  	}
  	return 1;
}

void output_products(struct product_info pro_info[], int count2){

    printf("\nExpiring soon:\n");
    for(int count = 0; count < count2; count++) { /* En if statement der tjekker kategorien indeni et for-loop
        der køre alle produkter igennem, hvis kategorien passer køre print funktionen. Det gør vi så for alle kategorier */
        if (strcmp(pro_info[count].category, "Expiring_soon") == 0) {
            //Vi benytter os af string.h funktionen strcmp, der sammenligner 2 strings og returner -1 0 eller 1
            //Hvis de 2 strings er ens bliver en 0, hvis den første er større bliver den 1, hvis den sidste er større bliver den -1
            print_products(pro_info, count); //Vi indsætter produkt-inforationerne og nummeret på det specifikke produkt der skal printes
        }
    }
    printf("\nFruit and vegetables:\n");
    for(int count = 0; count < count2; count++) {
        if (strcmp(pro_info[count].category, "Fruit_and_vegetables") == 0) {
            print_products(pro_info, count);
        }
    }
    printf("\nBakery:\n");
    for(int count = 0; count < count2; count++) {
        if (strcmp(pro_info[count].category, "Bakery") == 0) {
            print_products(pro_info, count);
	      }
    }
    printf("\nMeat:\n");
    for(int count = 0; count < count2; count++) {
        if (strcmp(pro_info[count].category, "Meat") == 0) {
            print_products(pro_info, count);
        }
    }
    printf("\nDairy:\n");
    for(int count = 0; count < count2; count++) {
        if (strcmp(pro_info[count].category, "Dairy") == 0) {
            print_products(pro_info, count);
        }
    }
    printf("\nVegan products:\n");
    for(int count = 0; count < count2; count++) {
        if (strcmp(pro_info[count].category, "Vegan") == 0) {
            print_products(pro_info, count);
        }
    }
    printf("\nOthers:\n");
    for(int count = 0; count < count2; count++) {
        if (strcmp(pro_info[count].category, "Others") == 0) {
            print_products(pro_info, count);
        }
    }
    printf("\nExpired:\n");
    for(int count = 0; count < count2; count++) {
        if (strcmp(pro_info[count].category, "Expired") == 0) {
            print_products(pro_info, count);
        }
    }
}

void print_products(struct product_info pro_info[], int count) {
    int days = 0, mdays = 0; /*Vi laver 2 integers, days der udregner hvor mange dage der er fra årsskiftet til udløbsdatoen,
        og mdays der udregner antal dage fra årsskiftet til nuværende dato */

    time_t raw;
    time(&raw);
    struct tm *time = localtime(&raw); //Vi bruger igen time.h biblioteket til at finde de nuværende datoer.

        if (pro_info[count].year < time->tm_year+1900 ||
            (pro_info[count].mon < time->tm_mon+1 && pro_info[count].year == time->tm_year+1900) ||
            (pro_info[count].day < time->tm_mday && pro_info[count].mon == time->tm_mon+1 && pro_info[count].year == time->tm_year+1900) ) {
            // Denne if statement undersøger om varen allerede er udløbet ved at sammenligne udløbsår, måned og dag med nuværende dato.
            for (int i = 1; i < pro_info[count].mon; i++) { //Et for-loop der køre antal gange lig med måned på udløbsdatoen.
                //Vi laver så alle månederne om til dage med if, eftersom forskellige måneder har forskellige dage, kræver det flere if statements.
                if (i == 2) { //her låner vi dage fra februar.
                    if ((pro_info[count].year % 4 == 0 && pro_info[count].year % 100 != 0) || pro_info[count].year % 400 == 0) { /*tjekker om det er skudår,
                    hvis det er skud år er februar 29 dage lang. Ellers 28*/
                        days += 29;
                    } else {
                        days += 28;
                    }
                } else if (i == 4 || i == 6 || i == 9 || i == 11) { //her låner vi dage fra april, juni, september eller november da de alle har 30 dage i måneden.
                    days += 30;
                } else { //her låner vi dage fra alle andre måneder der alle har 31 dage.
                    days += 31;
                }
            }
            days += pro_info[count].day; //Vi ligger også udløbsdagen til days
            for (int i = 1; i < time->tm_mon+1; i++) {
                //her gør vi det samme bare med mdays, vi regner nu ud hvor mange dage der er fra årsskiftet til nuværende dato.
                //Vi gør det antal gange lig med nuværende måned.
                if (i == 2) { //her låner vi dage fra februar.
                    if ((pro_info[count].year % 4 == 0 && pro_info[count].year % 100 != 0) || pro_info[count].year % 400 == 0) {
                        //tjekker om det er skudår, hvis det er skud år er februar 29 dage lang.
                        mdays += 29;
                    } else {
                        mdays += 28;
                    }
                } else if (i == 4 || i == 6 || i == 9 || i == 11) { //her låner vi dage fra april, juni, september eller november da de alle har 30 dage i måneden.
                    mdays += 30;
                } else { //her låner vi dage fra alle andre måneder der alle har 31 dage.
                    mdays += 31;
                }
            }
            //her gør vi det samme bare med mdays, vi regner nu ud hvor mange dage der er fra årsskiftet til nuværende dato.
            //Vi gør det antal gange lig med nuværnde måned.
            for (int i = pro_info[count].year; i < (time->tm_year+1900); i++) {
                //Vi undersøger også om det er flere år siden varen er udløbet,
                //og køre for-loopet antal gange lig med forskellen mellem udløbsåret og nuværende år.
                if ((i % 4 == 0 && i % 100 != 0) || i % 400 == 0) { //her tjekker vi for skudår
                    mdays += 366;
                } else {
                    mdays += 365;
                }
            }
            mdays += time->tm_mday; // Vi ligger nuværende dag til mdays.
            days = mdays - days; // Vi trækker days fra mdays for at få differensen og derved hvor mange dage der er til produktet udløber.
            printf("NR %d The %s has already expired. It expired %d day(s) ago.\n", count+1, pro_info[count].name, days);
                //Vi addere count med 1 for så starter vores produkters numre fra 1 i stedet for 0.

        } else if (pro_info[count].day == time->tm_mday && pro_info[count].mon == time->tm_mon+1 && pro_info[count].year == time->tm_year+1900) {
            printf("NR %d The %s is expiring today, hurry up and use it!\n", count+1, pro_info[count].name);
            // Her tjekker vi om det udløber i dag.
        } else if (pro_info[count].year_diff == 0 && pro_info[count].mon_diff == 0) {
            // Vi behøver ikke vise antal år og måneder hvis de er lig med 0, så her tjekker vi for det.
            printf("NR %d The %s is expiring in %d day(s).\n", count+1, pro_info[count].name, pro_info[count].day_diff);
        } else if (pro_info[count].year_diff == 0) {
            // Her gør vi det samme med år.
            printf("NR %d The %s is expiring in %d day(s) and %d month(s)\n", count+1, pro_info[count].name, pro_info[count].day_diff, pro_info[count].mon_diff);
        } else {
            printf("NR %d The %s is expiring in %d day(s), %d month(s) and %d year(s).\n",
                count+1, pro_info[count].name, pro_info[count].day_diff, pro_info[count].mon_diff, pro_info[count].year_diff);
        }
    }
