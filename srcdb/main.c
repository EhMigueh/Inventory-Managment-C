#include "db.h"

int main(void)
{
    srand((unsigned int)time(NULL));

    fprintf(stdout, "\nCREADO Bases de Datos...\n\n");

    generate_csv("./db/database10.csv", FIRST_DB_SIZE);
    fprintf(stdout, "Base de Datos de 10000 objetos CREADA.\n");
    generate_csv("./db/database25.csv", SECOND_DB_SIZE);
    fprintf(stdout, "Base de Datos de 25000 objetos CREADA.\n");
    generate_csv("./db/database50.csv", THIRD_DB_SIZE);
    fprintf(stdout, "Base de Datos de 50000 objetos CREADA.\n");
    generate_csv("./db/database75.csv", FOURTH_DB_SIZE);
    fprintf(stdout, "Base de Datos de 75000 objetos CREADA.\n");
    generate_csv("./db/database100.csv", FIFTH_DB_SIZE);
    fprintf(stdout, "Base de Datos de 100000 objetos CREADA.\n");

    fprintf(stdout, "\nBases de Datos CREADAS exitosamente.\n\n");

    return EXIT_SUCCESS;
}