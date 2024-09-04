/**
 * Función para validar el formulario de búsqueda.
 * Asegura que el término de búsqueda sea válido.
 * 
 * @returns {boolean} true si la validación es exitosa, false en caso contrario.
 */
function validateForm() {
    // Obtener el valor de la consulta de búsqueda y convertirlo a minúsculas
    var searchQuery = document.getElementsByName('search_query')[0].value.toLowerCase();
    var errorContainer = document.getElementById('error-container');

    // Eliminar cualquier mensaje de error previo
    errorContainer.innerHTML = '';

    // Expresión regular para validar el término de búsqueda
    var regex = /^(infantil|adolescente|juvenil|\d+)$/;

    // Realiza la validación del término de búsqueda
    if (!regex.test(searchQuery)) {
        errorContainer.innerHTML += '<p>Por favor, ingrese un término de búsqueda válido: INFANTIL, ADOLESCENTE, JUVENIL o un dígito.</p>';
    }

    // Si hay mensajes de error, muestra el contenedor y evita que se envíe el formulario
    if (errorContainer.innerHTML !== '') {
        errorContainer.style.display = 'block'; // Muestra el contenedor de mensajes de error
        return false; // Evita el envío del formulario
    }

    // Si todas las validaciones son exitosas, oculta el contenedor de mensajes de error
    errorContainer.style.display = 'none'; // Oculta el contenedor de mensajes de error
    return true; // Permite el envío del formulario
}
