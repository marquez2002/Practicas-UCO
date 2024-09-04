/**
 * Función para validar el formulario de fechas.
 * Verifica que las fechas de inicio y fin sean válidas y estén en el orden correcto.
 *
 * @returns {boolean} true si la validación es exitosa, false en caso contrario.
 */
function validateForm() {
    // Obtener los valores de las fechas
    var startDate = document.getElementsByName('startDate')[0].value;
    var endDate = document.getElementsByName('endDate')[0].value;
    var errorContainer = document.getElementById('error-container');

    // Elimina cualquier mensaje de error previo
    errorContainer.innerHTML = '';

    // Validación de la fecha de inicio
    if (startDate === '') {
        errorContainer.innerHTML += '<p>Por favor, ingrese la primera fecha.</p>';
    }

    // Validación de la fecha de fin
    if (endDate === '') {
        errorContainer.innerHTML += '<p>Por favor, ingrese la segunda fecha.</p>';
    }

    // Comprueba si la fecha de inicio es posterior o igual a la fecha de finalización
    if (startDate && endDate && new Date(startDate) >= new Date(endDate)) {
        errorContainer.innerHTML += '<p>La fecha de inicio debe ser anterior a la fecha de finalización.</p>';
    }

    // Si hay mensajes de error, muestra el contenedor y evita que se envíe el formulario
    if (errorContainer.innerHTML !== '') {
        errorContainer.style.display = 'block'; 
        return false; 
    }

    // Si todas las validaciones son exitosas, el formulario se enviará
    errorContainer.style.display = 'none'; 
    return true; // Permite el envío del formulario
}
