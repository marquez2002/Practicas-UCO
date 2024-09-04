/**
 * Función para validar el formulario de registro.
 * Asegura que todos los campos requeridos estén completos.
 * 
 * @returns {boolean} true si la validación es exitosa, false en caso contrario.
 */
function validateForm() {
    // Obtener los valores de los campos del formulario
    var email = document.getElementsByName('email')[0].value.trim();
    var password = document.getElementsByName('password')[0].value.trim();
    var name = document.getElementsByName('name')[0].value.trim();
    var surname = document.getElementsByName('surname')[0].value.trim();
    var date = document.getElementsByName('date')[0].value.trim();
    var role = document.getElementsByName('role')[0].value.trim();

    var errorContainer = document.getElementById('error-container');
    errorContainer.innerHTML = ''; // Limpiar mensajes de error previos

    // Validar que todos los campos requeridos no estén vacíos
    if (email === '' || password === '' || name === '' || surname === '' || date === '' || role === '') {
        errorContainer.innerHTML += 'Por favor, complete todos los campos.<br>';
    }

    // Verificar si hay mensajes de error y mostrar el contenedor si es necesario
    if (errorContainer.innerHTML !== '') {
        errorContainer.style.display = 'block'; // Mostrar mensajes de error
        return false; // Evitar el envío del formulario
    }

    errorContainer.style.display = 'none'; // Ocultar mensajes de error
    return true; // Permitir el envío del formulario si pasa las validaciones
}
