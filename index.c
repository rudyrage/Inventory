#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "database.h"
#include "write_file.h"

void add_database(database **rec);
char *read_entry(void);
void delete_database(database *rec, int part_no);
bool has_part(database *rec, int part_no);
database *find_part(database *rec, int part_no);
void print_database(database *rec);
void update_database(database *rec, int part_no);
void retrive_from_file(database *rec, char *filename);
void data_entry(database **rec);
void instruction(void);

int main(void) {
   database *record = NULL;
   retrive_from_file(record, "./data.txt");
   data_entry(&record);
   print_database(record);
   write_file(record);
   return 0;
}

void data_entry(database **rec) {
   int operation_code;
   int part_no;

   instruction();

   do {
      printf("Enter operation code: ");
      scanf("%d", &operation_code);

      switch (operation_code) {
         case 1:
            add_database(rec);
            break;
         case 2:
            printf("Enter Part Number: ");
            scanf("%d", &part_no);
            delete_database(*rec, part_no);
            break;
         case 3:
            printf("Enter Part Number: ");
            scanf("%d", &part_no);
            update_database(*rec, part_no);
            break;
         case 4:
            printf("Enter Part Number: ");
            scanf("%d", &part_no);
            find_part(*rec, part_no);
            break;

         case 0:
            break;
         default:
            printf("INVALID OPERATION CODE\n\n");
      }
   } while (operation_code);
}

void add_database(database **rec) {
   database *rec_temp = malloc(sizeof(database));
   if (rec_temp == NULL) {
      printf("%s : MALLOC FAILED : LINE = %d\n", __FILE__, __LINE__);
      exit(EXIT_FAILURE);
   }

   printf("enter part number: ");
   scanf("%d", &rec_temp->part_no);

   if (!has_part(*rec, rec_temp->part_no)) {
      printf("Enter data: "); getchar();
      rec_temp->entry_data = read_entry();
      rec_temp->next = *rec;
      *rec = rec_temp;
   } else {
      printf("Part Exist..\n\n");
   }
   putchar('\n');
}

void delete_database(database *rec, int part_no) {
   database *temp;
   while (rec) {
      temp = rec->next;
      if (temp && temp->part_no == part_no) {
         rec->next = rec->next->next;
         free(temp);
         return;
      }
      rec = rec->next;
   }
   printf("Failed to find part in database.\n\n");
}

void update_database(database *rec, int part_no) {
   while (rec) {
      if (rec->part_no == part_no) {
         rec->entry_data = read_entry();
         printf("Database Updated\n\n");
         return;
      }
      rec = rec->next;
   }
   printf("Part Number Not Found\n\n");
}

void retrive_from_file(database *rec, char *filename) {
   FILE *fp = fopen(filename, "r");
   char *str = malloc(sizeof(char)*100);

   fclose(fp);
}

bool has_part(database *rec, int part_no) {
   while (rec) {
      if (rec->part_no == part_no)
         return true;
      rec = rec->next;
   }
   return false;
}

database *find_part(database *rec, int part_no) {
   while (rec) {
      if (rec->part_no == part_no) {
         printf
           (
            "Part Number: %d\nPart Name: %s\n\n",
            rec->part_no, rec->entry_data
           );
           return rec;
      }
      rec = rec->next;
   }
   printf("Part Doesn\'t exist\n\n");
   return NULL;
}

char *read_entry(void) {
   char ch, *temp_entry = malloc(sizeof(char) * 1024);
   size_t i = 0;

   while ((ch = getchar()) != '\n') {
      temp_entry[i++] = ch;
   }

   temp_entry = realloc(temp_entry, i+1);
   temp_entry[i] = '\0';

   return temp_entry;
}

void print_database(database *database_storage) {
   printf("\n%s %18s", "Date", "Entry Name\n");
   while (database_storage) {
      printf(
               " %4d \t\t%-5s\n",
               database_storage->part_no,
               database_storage->entry_data
            );
      database_storage = database_storage->next;
   }
}

void instruction(void) {
   printf("%45s", "OPERATION CODES\n");
   printf("%56s", "ENTER 1 TO ADD  DATA  TO  THE DATABASE\n");
   printf("%56s", "ENTER 2 TO DELETE DATA IN THE DATABASE\n");
   printf("%56s", "ENTER 3 TO UPDATE DATA IN THE DATABASE\n");
   printf("%56s", "ENTER 4 TO FIND DATA IN  THE  DATABASE\n");
   printf("\n\n");
}
