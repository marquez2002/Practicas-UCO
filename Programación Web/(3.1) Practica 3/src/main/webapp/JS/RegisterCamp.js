/**
 * Función para validar el formulario de creación de campamentos.
 * Asegura que todas las entradas sean válidas antes de enviar el formulario.
 * 
 * @returns {boolean} true si la validación es exitosa, false en caso contrario.
 */
function validateForm() {
    // Obtener los valores de los campos del formulario
    var startDate = document.getElementsByName('startDate')[0].value.trim();
    var endDate = document.getElementsByName('endDate')[0].value.trim();
    var levelEducation = document.getElementById('levelEducation').value;
    var maximunAsistent = document.getElementsByName('maximunAsistent')[0].value.trim();
    var errorContainer = document.getElementById('error-container');

    // Limpiar mensajes de error previos
    errorContainer.innerHTML = '';

    // Validaciones
    if (startDate === '') {
        errorContainer.innerHTML += '<p>Por favor, ingrese la fecha de inicio.</p>';
    }

    if (endDate === '') {
        errorContainer.innerHTML += '<p>Por favor, ingrese la fecha de finalización.</p>';
    }
    
    // Verificar si la fecha de inicio es anterior a la fecha de finalización
    if (new Date(startDate) >= new Date(endDate)) {
        errorContainer.innerHTML += '<p>La fecha de inicio debe ser anterior a la fecha de finalización.</p>';
    }

    if (levelEducation === '') {
        errorContainer.innerHTML += '<p>Por favor, seleccione el nivel educativo.</p>';
    }

    // Validar el número máximo de asistentes
    if (maximunAsistent === '' || isNaN(maximunAsistent)) {
        errorContainer.innerHTML += '<p>Por favor, ingrese un número válido para el número máximo de asistentes.</p>';
    } else {
        var maxAssistantsInt = parseInt(maximunAsistent);
        if (maxAssistantsInt < 0 || maxAssistantsInt > 1000) {
            errorContainer.innerHTML += '<p>El número máximo de asistentes debe estar entre 0 y 1000.</p>';
        }
    }

    // Si hay mensajes de error, muestra el contenedor y evita el envío del formulario
    if (errorContainer.innerHTML !== '') {
        errorContainer.style.display = 'block'; // Muestra el contenedor de mensajes de error
        return false; // Evita el envío del formulario
    }

    // Ocultar contenedor de mensajes de error si no hay errores
    errorContainer.style.display = 'none'; // Oculta el contenedor de mensajes de error
    return true; // Permite el envío del formulario si pasa todas las validaciones
}
