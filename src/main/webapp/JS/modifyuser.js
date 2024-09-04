/**
 * Función para validar el formulario de usuario.
 * Asegura que todos los campos requeridos tengan entradas válidas.
 *
 * @returns {boolean} true si la validación es exitosa, false en caso contrario.
 */
function validateForm() {
    // Obtener los valores de los campos del formulario
    var password = document.getElementsByName('password')[0].value;
    var name = document.getElementsByName('name')[0].value.trim();
    var surname = document.getElementsByName('surname')[0].value.trim();
    var errorContainer = document.getElementById('error-container');

    // Elimina cualquier mensaje de error previo
    errorContainer.innerHTML = '';

    // Validación de la contraseña
    if (password === '') {
        errorContainer.innerHTML += '<p>Por favor, introduzca una contraseña.</p>';
    } else if (password.length < 8) {
        errorContainer.innerHTML += '<p>La contraseña debe tener al menos 8 caracteres.</p>';
    }

    // Expresión regular para validar que el nombre y apellidos contengan solo letras y espacios
    var caract = /^[a-zA-Z\s]+$/;

    // Validación del nombre
    if (name === '') {
        errorContainer.innerHTML += '<p>Por favor, indique su nombre.</p>';
    } else if (!caract.test(name)) {
        errorContainer.innerHTML += '<p>El nombre debe ser una cadena de caracteres que contenga letras y espacios.</p>';
    }

    // Validación de los apellidos
    if (surname === '') {
        errorContainer.innerHTML += '<p>Por favor, indique sus apellidos.</p>';
    } else if (!caract.test(surname)) {
        errorContainer.innerHTML += '<p>Los apellidos deben ser una cadena de caracteres que contenga letras y espacios.</p>';
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
