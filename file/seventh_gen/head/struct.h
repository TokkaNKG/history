#ifndef STRUCT_H
#define STRUCT_H

struct product_info {
    char name[40];
    char category[30];
    int day;
    int mon;
    int year;
    int day_diff;
    int mon_diff;
    int year_diff;
};
typedef struct product_info product_info;

#endif

