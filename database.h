#ifndef _DATABASE_H
typedef struct db {
   int part_no;
   char *entry_data;
   struct db *next;
} database;
#endif // _DATABASE_H
