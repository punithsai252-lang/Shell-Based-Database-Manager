#include <stdio.h>
#include <string.h>
#include "database.h"

void database_init(Database *db)
{
    db->table_count = 0;
}

void database_create_table(Database *db, const char *name)
{
    if (db->table_count >= MAX_TABLES)
    {
        printf("Error: Maximum number of tables reached.\n");
        return;
    }

    for (int i = 0; i < db->table_count; i++)
    {
        if (strcmp(db->tables[i].name, name) == 0)
        {
            printf("Error: Table '%s' already exists.\n", name);
            return;
        }
    }

    Table *table = &db->tables[db->table_count];

     strcpy(table->name, name);

table->column_count = 3;
table->row_count = 0;

strcpy(table->columns[0].name, "id");
strcpy(table->columns[1].name, "name");
strcpy(table->columns[2].name, "value");

    db->table_count++;

    printf("Table '%s' created successfully.\n", name);
}

void database_show_tables(Database *db)
{
    if (db->table_count == 0)
    {
        printf("No tables found.\n");
        return;
    }

    printf("\nTables:\n");
    printf("--------------------\n");

    for (int i = 0; i < db->table_count; i++)
    {
        printf("%d. %s\n", i + 1, db->tables[i].name);
    }

    printf("--------------------\n");
}

void database_insert(Database *db, const char *table_name)
{
    for (int i = 0; i < db->table_count; i++)
    {
        if (strcmp(db->tables[i].name, table_name) == 0)
        {
            Table *table = &db->tables[i];

            if (table->row_count >= MAX_ROWS)
            {
                printf("Error: Maximum rows reached.\n");
                return;
            }

            if (table->column_count == 0)
            {
                printf("Error: Table has no columns.\n");
                return;
            }

            printf("Enter values for %d columns:\n",
                   table->column_count);

            for (int j = 0; j < table->column_count; j++)
            {
                printf("%s: ", table->columns[j].name);

                scanf(" %[^\n]",
                      table->rows[table->row_count].values[j]);
            }

            table->row_count++;

            printf("Record inserted successfully.\n");
            return;
        }
    }

    printf("Error: Table '%s' not found.\n", table_name);
}

void database_select(Database *db, const char *table_name)
{
    for (int i = 0; i < db->table_count; i++)
    {
        if (strcmp(db->tables[i].name, table_name) == 0)
        {
            Table *table = &db->tables[i];

            printf("\nTable: %s\n", table->name);
            printf("--------------------\n");

            if (table->row_count == 0)
            {
                printf("No records found.\n");
                return;
            }

            for (int j = 0; j < table->column_count; j++)
            {
                printf("%-15s", table->columns[j].name);
            }

            printf("\n");

            for (int j = 0; j < table->row_count; j++)
            {
                for (int k = 0; k < table->column_count; k++)
                {
                    printf("%-15s",
                           table->rows[j].values[k]);
                }

                printf("\n");
            }

            return;
        }
    }

    printf("Error: Table '%s' not found.\n", table_name);
}

void database_drop_table(Database *db, const char *table_name)
{
    for (int i = 0; i < db->table_count; i++)
    {
        if (strcmp(db->tables[i].name, table_name) == 0)
        {
            for (int j = i; j < db->table_count - 1; j++)
            {
                db->tables[j] = db->tables[j + 1];
            }

            db->table_count--;

            printf("Table '%s' dropped successfully.\n",
                   table_name);

            return;
        }
    }

    printf("Error: Table '%s' not found.\n", table_name);
}
