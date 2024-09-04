/**
 * Función para validar el formulario de creación de actividades.
 * Asegura que todas las entradas sean válidas antes de enviar el formulario.
 * 
 * @returns {boolean} true si la validación es exitosa, false en caso contrario.
 */
function validateForm() {
    // Obtener los valores de los campos del formulario
    var name = document.getElementsByName('name')[0].value.trim();
    var timetable = document.getElementById('timetable').value;
    var levelEducation = document.getElementById('levelEducation').value;
    var asistents = document.getElementsByName('asistents')[0].value.trim();
    var numberMonitor = document.getElementsByName('numberMonitor')[0].value.trim();
    var errorContainer = document.getElementById('error-container');

    // Limpiar mensajes de error previos
    errorContainer.innerHTML = '';

    // Expresión regular para validar que el nombre contenga solo letras y espacios
    var caract = /^[a-zA-Z\s]+$/;

    // Validar el campo de nombre
    if (name === '') {
        errorContainer.innerHTML += '<p>Por favor, indique su nombre.</p>';
    } else if (!caract.test(name)) {
        errorContainer.innerHTML += '<p>El nombre de la actividad debe contener solo letras y espacios.</p>';
    }

    // Validar el campo de horario
    if (timetable === '') {
        errorContainer.innerHTML += '<p>Por favor, seleccione un horario para la actividad.</p>';
    }

    // Validar el nivel educativo
    if (levelEducation === '') {
        errorContainer.innerHTML += '<p>Por favor, seleccione un nivel educativo para la actividad.</p>';
    }

    // Validar el número máximo de asistentes
    if (asistents === '' || isNaN(asistents)) {
        errorContainer.innerHTML += '<p>Por favor, ingrese un número válido para el número máximo de asistentes.</p>';
    } else {
        var asistentsInt = parseInt(asistents);
        if (asistentsInt < 0 || asistentsInt > 1000) {
            errorContainer.innerHTML += '<p>El número máximo de asistentes debe estar entre 0 y 1000.</p>';
        }
    }

    // Validar el número de monitores
    if (numberMonitor === '' || isNaN(numberMonitor)) {
        errorContainer.innerHTML += '<p>Por favor, ingrese un número válido para el número de monitores necesarios.</p>';
    } else {
        var numberMonitorInt = parseInt(numberMonitor);
        if (numberMonitorInt < 0 || numberMonitorInt > 1000) {
            errorContainer.innerHTML += '<p>El número de monitores necesarios debe estar entre 0 y 1000.</p>';
        }
    }

    // Si hay mensajes de error, muestra el contenedor y evita el envío del formulario
    if (errorContainer.innerHTML !== '') {
        errorContainer.style.display = 'block'; // Muestra el contenedor de mensajes de error
        return false; // Evita el envío del formulario
    }

    // Si todas las validaciones son exitosas, el formulario se enviará
    errorContainer.style.display = 'none'; // Oculta el contenedor de mensajes de error
    return true; // Permite el envío del formulario
}
