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

/** @file alumno.h
 ** @brief Declaraciones públicas para la gestión de datos de un alumno en formato JSON.
 **/

#ifndef ALUMNO_H_
#define ALUMNO_H_

/* === Headers files inclusions ==================================================================================== */

/* === Header for C++ compatibility ================================================================================ */
#ifdef __cplusplus
extern "C" {
#endif

/* === Public macros definitions =================================================================================== */

/* === Public data type declarations =============================================================================== */

/**
 * @struct alumno_t
 * @brief Estructura que contiene los datos personales de un alumno.
 *
 * Representa los datos básicos de identificación de un alumno, incluyendo nombre, apellido y número de documento.
 */
typedef struct {
    const char * nombre;     /**< Nombre del alumno */
    const char * apellido;   /**< Apellido del alumno */
    int documento;           /**< Documento del alumno */
} alumno_t;

/* === Public variable declarations ================================================================================ */

/* === Public function declarations ================================================================================ */

/**
 * @brief Serializa los datos de un alumno al formato JSON.
 * 
 * Esta función convierte los datos de la estructura `alumno_t` a una cadena JSON válida.
 *
 * @param alumno Puntero a la estructura con los datos del alumno.
 * @param resultado Buffer donde se almacenará la cadena JSON resultante.
 * @param espacio_disponible Tamaño del buffer disponible en bytes.
 * @return int Longitud de la cadena generada, o -1 si no hay espacio suficiente.
 */
int Serializar(const alumno_t *alumno, char *resultado, size_t espacio_disponible);

/* === End of conditional blocks =================================================================================== */
#ifdef __cplusplus
}
#endif

#endif /* ALUMNO_H_ */
