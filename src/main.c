/*********************************************************************************************************************
Copyright (c) 2025, Bayona Franco Gabriel <gabrielbayona19@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit
persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

SPDX-License-Identifier: MIT
*********************************************************************************************************************/

/** @file main.c
 ** @brief Codigo fuente principal del proyecto
 **/

/* === Headers files inclusions ==================================================================================== */
#include <stdio.h>
#include "alumno.h"

/* === Macros definitions ========================================================================================== */

/* === Private data type declarations ============================================================================== */

/* === Private function declarations =============================================================================== */

/* === Private variable definitions ================================================================================ */

/* === Public variable definitions ================================================================================= */

/* === Private function definitions ================================================================================ */

/* === Public function implementation ============================================================================== */


/**
 * @brief Función principal del programa.
 * 
 * @return int Código de salida del sistema operativo
 */
int main(void) {
    // Crear un alumno y serializarlo a JSON
    // Se utiliza un buffer de tamaño fijo para almacenar el JSON generado
    char buffer[100];
    int resultado;

    alumno_t gabrielB = CrearAlumno("Gabriel","Bayona",43770990);
    if (gabrielB == NULL) {
        printf("Error al crear el alumno\n");
        return -1;
    }
    // Crear otro alumno
    alumno_t magnusC = CrearAlumno("Magnus","Carlsen",42456945);
    if (magnusC == NULL) {
        printf("Error al crear el alumno\n");
        return -1;
    }

    resultado = SerializarAlumno(gabrielB,buffer, sizeof(buffer));
    if (resultado >= 0) {
        printf("JSON generado:\n%s\n", buffer);
    } else {
        printf("Error: no hay suficiente espacio para serializar.\n");
    }

    resultado = SerializarAlumno(magnusC,buffer, sizeof(buffer));
    if (resultado >= 0) {
        printf("JSON generado:\n%s\n", buffer);
    } else {
        printf("Error: no hay suficiente espacio para serializar.\n");
    }

    return 0;

}


/* === End of documentation ======================================================================================== */
