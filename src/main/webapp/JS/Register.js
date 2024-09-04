/**
 * Función para validar el formulario de registro de usuario.
 * Asegura que todas las entradas sean válidas antes de enviar el formulario.
 * 
 * @returns {boolean} true si la validación es exitosa, false en caso contrario.
 */
function validateForm() {
    // Obtener los valores de los campos del formulario
    var email = document.getElementsByName('email')[0].value.trim();
    var password = document.getElementsByName('password')[0].value;
    var name = document.getElementsByName('name')[0].value.trim();
    var surname = document.getElementsByName('surname')[0].value.trim();
    var date = document.getElementsByName('date')[0].value;
    var specialAttentionYes = document.getElementById('yes').checked;
    var specialAttentionNo = document.getElementById('no').checked;
    var errorContainer = document.getElementById('error-container');

    // Elimina cualquier mensaje de error previo
    errorContainer.innerHTML = '';

    // Expresión regular para validar el formato de correo electrónico
    var emailRegex = /^\S+@\S+\.\S+$/;

    // Validaciones de los campos
    // Validación de correo electrónico
    if (!emailRegex.test(email)) {
        errorContainer.innerHTML += '<p>Por favor, introduzca un correo electrónico válido.</p>';
    }

    // Validación de contraseña
    if (password === '') {
        errorContainer.innerHTML += '<p>Por favor, introduzca una contraseña.</p>';
    } else if (password.length < 8) {
        errorContainer.innerHTML += '<p>La contraseña debe tener al menos 8 caracteres.</p>';
    }

    // Expresión regular para validar que el nombre y apellidos contengan solo letras y espacios
    var caract = /^[a-zA-Z\s]+$/;

    // Validación de nombre
    if (name === '') {
        errorContainer.innerHTML += '<p>Por favor, indique su nombre.</p>';
    } else if (!caract.test(name)) {
        errorContainer.innerHTML += '<p>El nombre debe ser una cadena de caracteres que contenga letras y espacios.</p>';
    }

    // Validación de apellidos
    if (surname === '') {
        errorContainer.innerHTML += '<p>Por favor, indique sus apellidos.</p>';
    } else if (!caract.test(surname)) {
        errorContainer.innerHTML += '<p>Los apellidos deben ser una cadena de caracteres que contenga letras y espacios.</p>';
    }

    // Validación de fecha
    if (date === '') {
        errorContainer.innerHTML += '<p>Por favor, introduzca su fecha de nacimiento.</p>';
    }

    // Validación de atención especial
    if (!(specialAttentionYes || specialAttentionNo)) {
        errorContainer.innerHTML += '<p>Por favor, seleccione si requiere atención especial.</p>';
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
