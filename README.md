# Sistema de Gestión de Inventario - Grupo 5 🧍🧍‍♀️

En este conjunto de directorios está desarrollado el análisis de rendimiento de algoritmos de búsqueda y ordenamiento implementados en un **Sistema de Gestión de Inventario**.

---

# Integrantes 👨‍💻

### 1. Miguel Loaiza 🤓
- Estudiante de Ingeniería Informática
- [Miguel Loaiza](https://github.com/EhMigueh)
- **miloaiza@umag.cl**

### 2. Ignacio Contreras 🤓
- Estudiante de Ingeniería Informática
- [Ignacio Contreras](https://github.com/Dysnomia9)
- **igcontre@umag.cl**

### 3. Rodolfo Cifuentes 🤓
- Estudiante de Ingeniería Informática
- [Rodolfo Cifuentes](https://github.com/Fitooooooooo)
- **rcifuent@umag.cl**

---

## Objetivo 🎯

implementar y analizar algoritmos básicos de ordenación y búsqueda, aplicándolos a un sistema de gestión de inventario. El equipo deben desarrollar un sistema que permita ordenar y buscar productos según diferentes criterios, evaluando el rendimiento de los algoritmos implementados.

---

## Descripción del Proyecto ✏️
Este proyecto simula un sistema de gestión de inventario donde se deberán implementar distintas funcionalidades, como:

1. Carga de datos de productos desde archivos CSV, permitiendo la gestión dinámica del inventario.
2. Ordenación eficiente de productos utilizando diversos algoritmos (Bubble Sort, Selection Sort, Insertion Sort) según diferentes criterios (ID, nombre, precio, stock).
3. Búsqueda optimizada de productos mediante algoritmos secuenciales y binarios, permitiendo encontrar artículos por ID, nombre o rango de precios.
4. Análisis estadístico del inventario, calculando métricas como valor total, productos más/menos populares, promedios por categoría.
5. Interacción mediante interfaz de comandos que permita al usuario gestionar todo el sistema de manera intuitiva.

---

## Explicación de Directorios 📁

El proyecto de sistema de gestión de inventario posee muchos directorios, la explicación de los directorios importantes es la siguiente:

 - *incs*     : Headers (.h).
 - *src*      : Código fuente principal (.c).
 - *srcdb*    : Código relacionado a la base de datos (.c y .h).
 - *db*       : Archivos CSV con los datos.
 - *plots*    : Gráficos de análisis.
 - *docs*     : Documentación del proyecto.

---

## Gnuplot 📈

Para poder ejecutar el programa sin problemas asegurece de tener instalado en su sistema gnuplot. Si está en linux o WSL puede instalarlo por medio del siguiente comando en su terminal:

- sudo apt-get install gnuplot

---

## Funcionalidad del Programa 🛠️

Para poder ejecutar el programa debe ejecutar los siguientes comandos en el siguiente orden dentro de la carpeta grupo_5 en su terminal:

- make clean
- make
- make run

Una vez hecho el make run puede sentirse libre de explorar todas las opciones que brinda el programa.

---
