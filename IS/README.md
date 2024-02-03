# Sistema de Reservas - Grupo Pr_509

## Descripción del Proyecto

La implementación realizada por los alumnos del grupo Pr_509 consiste en un sistema de reservas que comienza con un sencillo proceso de inicio de sesión. Durante este proceso, se solicitará un ID, usuario y contraseña. Dependiendo del ID proporcionado, el sistema dirigirá al usuario a diferentes menús. Si el ID está en el rango de 1 a 4, el usuario accederá al menú del administrador, donde podrá realizar diversas acciones, como crear usuarios (para ID 1 o 2), modificar la disponibilidad de las máquinas (para ID 3 o 4) y restringir recursos (para cualquier administrador).

Las modificaciones realizadas se guardarán en archivos de texto correspondientes y se podrán acceder desde la carpeta del programa. Si el ID no pertenece a los valores 1, 2, 3 o 4, el usuario accederá a un menú simplificado que solo permite la creación de reservas. Se solicitará información como la máquina deseada, los recursos seleccionados, fechas y horas de inicio y fin, y confirmación de la operación.

Destacamos que habrá un total de 8 máquinas, y cada una contará con 8 recursos disponibles que podrán reservarse inicialmente de manera íntegra. El programa comenzará con las 8 máquinas disponibles.

## Configuración y Ejecución

### Requisitos

- Sistema operativo compatible con el desarrollo (Linux, Windows, macOS).
- Compilador compatible con C++.
- Acceso a la carpeta de googletest.

### Makefile

Para compilar y ejecutar el proyecto, se ha proporcionado un archivo Makefile. Antes de ejecutarlo, asegúrese de modificar la variable `GTEST_DIR` en el archivo Makefile con la ubicación de la carpeta de googletest que contiene su trabajo.

```make
GTEST_DIR = /ruta/a/googletest
```

## Ejecución de Tests en Otros Dispositivos

Si se requiere la ejecución de los tests establecidos para dicho ejercicio en otros dispositivos, siga estos pasos:

1. Descargue la documentación y carpetas de googletest desde el siguiente enlace: [googletest](enlace_a_googletest).

2. Asegúrese de tener las dependencias necesarias instaladas para la ejecución de los tests. Puede consultar la documentación de googletest para obtener información detallada sobre los requisitos.

3. Utilice el siguiente comando para ejecutar los tests:

    ```bash
    ./run_tests
    ```

    Este comando iniciará la suite de pruebas y proporcionará información detallada sobre los resultados.

Recuerde ajustar la variable `GTEST_DIR` en el archivo Makefile con la ubicación correcta de la carpeta de googletest que contiene su trabajo, antes de realizar cualquier compilación o ejecución de pruebas.

## Estructura de Carpetas

- **docs**: Documentación del proyecto.
- **src**: Código fuente del programa.
- **tests**: Archivos de prueba.

## Contribuciones y Problemas

Si desea contribuir al proyecto o informar sobre problemas encontrados, no dude en crear una solicitud de extracción o un problema en el repositorio.

¡Gracias por utilizar nuestro sistema de reservas!
