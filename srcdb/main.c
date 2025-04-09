#include "db.h"

int main(void)
{
    srand((unsigned int)time(NULL));

    fprintf(stdout, "\nCREADO Bases de Datos...\n");

    generate_csv("./db/small_database.csv", SMALL_DB_SIZE);
    generate_csv("./db/large_database.csv", LARGE_DB_SIZE);

    fprintf(stdout, "Bases de Datos CREADAS exitosamente.\n\n");

    return EXIT_SUCCESS;
}