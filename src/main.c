#include "db.h"
#include "createdb.h"

int main(void)
{
    srand((unsigned int)time(NULL));

    fprintf(stdout, "CREADO Bases de Datos...\n");
    generate_csv("small_database.csv", SMALL_DB_SIZE);
    generate_csv("large_database.csv", LARGE_DB_SIZE);


    return EXIT_SUCCESS;
}