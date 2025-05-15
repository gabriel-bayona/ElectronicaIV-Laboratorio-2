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

/** @file alumno.c
 ** @brief Implementación del módulo para manejo de datos de alumnos.
 **/

/* === Headers files inclusions ==================================================================================== */
#include <string.h>
#include <stdio.h>
#include "alumno.h"
#include <stdlib.h>
#include "config.h"
#include <stdbool.h>

/* === Macros definitions ========================================================================================== */
#define MAX_NOMBRE     30
#define MAX_APELLIDO   30

#ifdef USAR_MEMORIA_ESTATICA
    #ifndef ALUMNOS_MAX_INSTANCIAS
        #define ALUMNOS_MAX_INSTANCIAS 2 //!<Cantidad maxima de alumnos
    #endif
#endif

/* === Private data type declarations ============================================================================== */
struct alumno_s {
    char nombre[MAX_NOMBRE];     //!< Nombre del alumno
    char apellido[MAX_APELLIDO];   //!< Apellido del alumno
    int documento;  //!< Documento del alumno
#ifdef USAR_MEMORIA_ESTATICA
    bool ocupado;       //!<Indica si la instancia esta ocupada
#endif
};


/* === Private function declarations =============================================================================== */

/**
 * @brief Crea una nueva instancia de la estructura alumno_s.
 *
 * @return Puntero a la nueva instancia de alumno_s, o NULL si no hay espacio disponible.
 */
#ifdef USAR_MEMORIA_ESTATICA
static alumno_t CrearInstancia(void);
#endif
/**
 * @brief Serializa un campo de texto clave-valor en formato JSON.
 *
 * @param campo Nombre del campo.
 * @param valor Valor del campo.
 * @param destino Buffer donde se escribe el resultado.
 * @param size  Tamaño disponible para escribir la cadena
 * @return int Longitud del texto generado o -1 si el espacio no es suficiente
 */
static int SerializarTexto(char campo[], const char valor[], char destino[], int size);


/**
 * @brief Función interna para serializar campos numéricos.
 *
 * Similar a SerializarTexto, pero para valores enteros.
 *
 * @param campo Nombre del campo (clave).
 * @param valor Valor numérico a insertar.
 * @param destino  Buffer donde se escribirá el resultado. Debe tener espacio suficiente.
 * @param size     Tamaño máximo disponible en el buffer (incluyendo el carácter nulo).
 *  * 
 * @return int     Número de bytes escritos (sin incluir el nulo), o -1 si:
 *                 - El buffer es insuficiente.
 *                 - El campo es NULL o vacío.
 *                 - El destino es NULL.
 * 
 */
static int SerializarNumero(char campo[], int valor, char buffer[], int size);


/* === Private variable definitions ================================================================================ */
#ifdef USAR_MEMORIA_ESTATICA
    static struct alumno_s instancias[ALUMNOS_MAX_INSTANCIAS]={0};
#endif
/* === Public variable definitions ================================================================================= */




/* === Private function definitions ================================================================================ */
#ifdef USAR_MEMORIA_ESTATICA
static alumno_t CrearInstancia(){
    alumno_t self = NULL;        //usar self es una buena practica
    for (int i = 0; i < ALUMNOS_MAX_INSTANCIAS; i++)
    {
        if (!instancias[i].ocupado)
        {
            instancias[i].ocupado = true;
            self = &instancias[i];
            break;
        }
        
    }
   return self;
}
#endif

static int SerializarTexto(char campo[], const char valor[], char buffer [], int size) {
    return snprintf(buffer, size, "\"%s\":\"%s\",", campo, valor);
}
/**
 * @brief Función interna para serializar un campo numérico a formato JSON.
 *
 * Convierte un campo numérico a formato JSON y lo agrega al buffer de salida.
 *
 * @param campo Nombre del campo.
 * @param valor Valor del campo.
 * @param destino Buffer donde se almacenará el JSON generado.
 * @param size Tamaño disponible en el buffer.
 * @return int Longitud de la cadena generada o -1 si no hay espacio suficiente.
 */

static int SerializarNumero(char campo[], int valor, char buffer[], int size) {
    return snprintf(buffer, size, "\"%s\":%d", campo, valor);
}
/**
 * @brief Función interna para serializar un campo de texto a formato JSON.
 *
 * Convierte un campo de texto a formato JSON y lo agrega al buffer de salida.
 *
 * @param campo Nombre del campo.
 * @param valor Valor del campo.
 * @param destino Buffer donde se almacenará el JSON generado.
 * @param size Tamaño disponible en el buffer.
 * @return int Longitud de la cadena generada o -1 si no hay espacio suficiente.
 */

/* === Public function implementation ============================================================================== */



alumno_t CrearAlumno(char* nombre, char* apellido, int dni) {
    #ifdef USAR_MEMORIA_DINAMICA
        alumno_t self = malloc(sizeof(struct alumno_s));
    #else
        alumno_t self = CrearInstancia();
    #endif
    if (self != NULL) {
        self->documento = dni;
        strncpy(self->nombre, nombre, sizeof(self->nombre) - 1);
        strncpy(self->apellido, apellido, sizeof(self->apellido) - 1);
    } else{
        printf("Error alumno\n");
    }
    return self;
}

int SerializarAlumno(alumno_t self, char *buffer, int size) {
    int escritos;
    int resultado;

    buffer[0] = '{';
    buffer++;
    escritos = 1;

    resultado = SerializarTexto("nombre", self->nombre, buffer, size - escritos);
    if (resultado < 0) {
        return -1;
    }

    escritos = escritos + resultado;
    buffer = buffer + resultado;
    resultado = escritos;
    escritos += SerializarTexto("apellido", self->apellido, buffer, size - escritos);
    if (escritos < 0) {
        return -1;
    }

    buffer = buffer + (escritos - resultado);
    resultado = escritos;

    escritos = escritos + SerializarNumero("documento", self->documento, buffer, size - escritos);
    if (escritos < 0) {
        return -1;
    }

    buffer = buffer + (escritos - resultado);

    if (escritos >= (int)(size - 1)) {
        return -1;
    } else {
        *buffer = '}';
        buffer++;
        *buffer = '\0';

        escritos = escritos + 2;
    }

    return escritos;
}


/* === End of documentation ======================================================================================== */