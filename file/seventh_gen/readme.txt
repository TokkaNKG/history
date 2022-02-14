To make the code work do the following:

In data_handling.c change path for the file pointer in function load_data and save_data:
fpointer = fopen("C:\\tmp\\file\\seventh_gen\\head\\storage.txt", "r");
and
fpointer = fopen("C:\\tmp\\file\\seventh_gen\\head\\storage.txt", "w");
To the absolute path of the storage.txt file in head folder.

In barcode.c change path for the file pointer:
FILE *f = fopen("C:\\tmp\\file\\seventh_gen\\head\\database.txt", "r");
To the absolute path for the database.txt in the head folder.