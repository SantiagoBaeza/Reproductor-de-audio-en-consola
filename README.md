[⬅️ Volver a "Ejercicios en C y C++"](https://github.com/SantiagoBaeza/programacion-en-C-Cpp)

# Reproductor de audio en consola

Este proyecto implementa un reproductor básico en C que permite al usuario seleccionar y reproducir canciones almacenadas en un archivo `.raw`.  
La lógica se centra en organizar la información de cada pista, mostrar un menú interactivo y utilizar una función externa (`play_audio`) para la reproducción.  
Además, se ofrece la opción de guardar la canción seleccionada en un nuevo archivo `.raw`.

---

## Contexto

Este ejercicio fue parte de una práctica en clase, donde se nos proporcionó un archivo binario (`audio_list.raw`) con múltiples canciones y su metadata.  
También se nos entregaron los archivos `audio_player.c` y `audio_player.h`, que contenían la función `play_audio(...)` ya implementada.  
Nuestro objetivo era desarrollar el algoritmo que leyera la información, organizara las pistas en estructuras, y ofreciera una interfaz de consola para reproducirlas o guardarlas.  
El foco estuvo en el manejo de memoria dinámica, lectura binaria con `fread`, uso de `struct`, y diseño de un menú interactivo.

---

## Capturas

- **Captura 01**: Menú de selección de canciones en consola.  
- **Captura 02**: Mensaje de error al fallar la reserva de memoria.  

*(Podés agregar las imágenes cuando las tengas, usando el formato `![Texto alternativo](URL)`)*

---

## Funcionalidad clave

- Lectura de archivo `.raw` con `fread` para obtener:
  - Cantidad de canciones
  - Sample rate, cantidad de muestras y nombre de cada pista
  - Datos de audio en formato `float`
- Uso de `struct cancion` para organizar la información de cada pista
- Menú interactivo para seleccionar y reproducir canciones
- Opción de guardar la canción actual en un nuevo archivo `.raw`
- Manejo de errores y liberación de memoria dinámica en caso de fallos

---

## Tecnologías utilizadas

- Lenguaje C (estándar)
- Librerías: `stdio.h`, `stdint.h`, `stdlib.h`
- Función externa `play_audio(...)` provista en `audio_player.c/.h`
- Compilación con `gcc` y enlace dinámico mediante DLL

---

## Comentarios finales

Para compilar el proyecto, se siguió la metodología trabajada en clase:
![imagen1](enlace_aca)


De esta manera, el ejecutable `prog.exe` queda vinculado a la DLL `audio_player.dll`, permitiendo la reproducción de las pistas mediante la función `play_audio`.

Este ejercicio fue una excelente práctica para reforzar conceptos importantes de programación en C, como el manejo de archivos binarios, estructuras, memoria dinámica y compilación modular con DLL.

---

> 🧩 Estos espacios están en construcción y se actualizan de forma frecuente.
