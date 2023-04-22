#include <stdio.h>
#include "database.h"

void write_file(database *database_storage) {
   FILE *fp = fopen("./data.txt", "w");
   fprintf(fp, "%s %18s", "Part No", "Entry Name\n");
   while (database_storage) {
      fprintf(
               fp,
               " %4d \t\t\t %-5s\n",
               database_storage->part_no,
               database_storage->entry_data
            );
      database_storage = database_storage->next;
   }
   fclose(fp);
}
