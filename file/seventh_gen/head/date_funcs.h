#ifndef MAIN_H
#define MAIN_H
#include "struct.h"


int * time_to_expiry(int day, int mon, int year);
int valid_date(int day, int mon, int year);
void output_products(product_info pro_info[], int count2);
void print_products(product_info pro_info[], int count);

#endif
