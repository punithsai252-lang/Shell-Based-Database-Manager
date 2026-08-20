#ifndef DATABASE_H
#define DATABASE_H

#define MAX_TABLES 10
#define MAX_COLUMNS 10
#define MAX_ROWS 100
#define MAX_NAME 50
#define MAX_VALUE 100

typedef struct
{
    char name[MAX_NAME];
} Column;

typedef struct
{
    char values[MAX_COLUMNS][MAX_VALUE];
} Row;

typedef struct
{
    char name[MAX_NAME];

    int column_count;
    Column columns[MAX_COLUMNS];

    int row_count;
    Row rows[MAX_ROWS];

} Table;

typedef struct
{
    int table_count;
    Table tables[MAX_TABLES];

} Database;

void database_init(Database *db);

void database_create_table(Database *db, const char *name);

void database_insert(Database *db, const char *table_name);

void database_select(Database *db, const char *table_name);

void database_show_tables(Database *db);

void database_drop_table(Database *db, const char *table_name);

#endif
