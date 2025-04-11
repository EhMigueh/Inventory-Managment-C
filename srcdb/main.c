#include "db.h"

int main(void)
{
    srand((unsigned int)time(NULL));

    fprintf(stdout, "\nCREADO Bases de Datos...\n");

    generate_csv("./db/database10.csv", FIRST_DB_SIZE);
    generate_csv("./db/database25.csv", SECOND_DB_SIZE);
    generate_csv("./db/database50.csv", THIRD_DB_SIZE);
    generate_csv("./db/database75.csv", FOURTH_DB_SIZE);
    generate_csv("./db/database100.csv", FIFTH_DB_SIZE);

    fprintf(stdout, "Bases de Datos CREADAS exitosamente.\n\n");

    return EXIT_SUCCESS;
}