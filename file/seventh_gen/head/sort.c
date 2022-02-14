#include <stdio.h>
#include <string.h>
#include <time.h>
#include "barcode.h"
#include "sort.h"


void sort(product_info pro_info[], int count2) {
    int a = 0, b = 0, product = count2;
    char h[40];

    time_t raw;
    time(&raw);
    struct tm *time = localtime(&raw);

    for (int i = 0; i < product; i++) { //sortering af produkter efter udløbsdatoen. Vi starter fra første product i rækken.
        for (int j = i+1; j < product; j++) { //her sammenligner i første product med alle andre produkter og bytter hver gang det første produkt er større.
            if ((pro_info[i].year > pro_info[j].year) || (pro_info[i].mon > pro_info[j].mon && pro_info[i].year == pro_info[j].year) ||
               (pro_info[i].day > pro_info[j].day && pro_info[i].mon == pro_info[j].mon && pro_info[i].year == pro_info[j].year)) {
                strcpy(h, pro_info[i].name);
                strcpy(pro_info[i].name, pro_info[j].name);
                strcpy(pro_info[j].name, h);

                strcpy(h, pro_info[i].category);
                strcpy(pro_info[i].category, pro_info[j].category);
                strcpy(pro_info[j].category, h);

                a = pro_info[i].day_diff;
                pro_info[i].day_diff = pro_info[j].day_diff;
                pro_info[j].day_diff = a;

                a = pro_info[i].mon_diff;
                pro_info[i].mon_diff = pro_info[j].mon_diff;
                pro_info[j].mon_diff = a;

                a = pro_info[i].year_diff;
                pro_info[i].year_diff = pro_info[j].year_diff;
                pro_info[j].year_diff = a;

                a = pro_info[i].day;
                pro_info[i].day = pro_info[j].day;
                pro_info[j].day = a;

                a = pro_info[i].mon;
                pro_info[i].mon = pro_info[j].mon;
                pro_info[j].mon = a;

                a = pro_info[i].year;
                pro_info[i].year = pro_info[j].year;
                pro_info[j].year = a;


            }
            if ((pro_info[i].year < time->tm_year+1900) ||
                (pro_info[i].mon < time->tm_mon+1 && pro_info[i].year == time->tm_year+1900) ||
                (pro_info[i].day-3 < time->tm_mday && pro_info[i].mon == time->tm_mon+1 && pro_info[i].year == time->tm_year+1900) ) {
                strcpy(pro_info[i].category, "Expiring_soon");
            }
            if ((pro_info[j].year < time->tm_year+1900) ||
                (pro_info[j].mon < time->tm_mon+1 && pro_info[j].year == time->tm_year+1900) ||
                (pro_info[j].day-3 < time->tm_mday && pro_info[j].mon == time->tm_mon+1 && pro_info[j].year == time->tm_year+1900) ) {
                strcpy(pro_info[j].category, "Expiring_soon");
            }
            if ((pro_info[i].year < time->tm_year+1900) ||
                         (pro_info[i].mon < time->tm_mon+1 && pro_info[i].year == time->tm_year+1900) ||
                         (pro_info[i].day < time->tm_mday && pro_info[i].mon == time->tm_mon+1 && pro_info[i].year == time->tm_year+1900) ) {
                strcpy(pro_info[i].category, "Expired");
            }
            if ((pro_info[j].year < time->tm_year+1900) ||
                (pro_info[j].mon < time->tm_mon+1 && pro_info[j].year == time->tm_year+1900) ||
                (pro_info[j].day < time->tm_mday && pro_info[j].mon == time->tm_mon+1 && pro_info[j].year == time->tm_year+1900) ) {
                strcpy(pro_info[j].category, "Expired");
            }

        }
    }
}
