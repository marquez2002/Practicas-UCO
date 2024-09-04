<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ page import="display.userbean.userBean" %>
<%@ page import="data.dao.AsistentDAO.AsistentDAO" %>
<%@ page import="business.asistent.AsistentDTO" %>
<jsp:useBean id="userBean" scope="session" class="display.userbean.userBean" />

<%
    String nextPage; 
    String msgNextPage; 

    // Verifica si el usuario ya está logueado
    if (userBean != null && !userBean.getEmail().isEmpty()) {    
        nextPage = "../../index.jsp"; // Redirige a la página de inicio
        msgNextPage = "Already logged in"; 
    } else {
        // Obtener parámetros de la solicitud
        String email = request.getParameter("mail");
        String pass = request.getParameter("password");

        // Cargar propiedades desde el archivo de configuración
        String file = application.getInitParameter("sqlproperties");
        try (java.io.InputStream myIO = application.getResourceAsStream(file)) {
            java.util.Properties prop = new java.util.Properties();
            prop.load(myIO); // Carga las propiedades

            // Crear instancia del DAO
            AsistentDAO asistentDAO = new AsistentDAO(prop);
            Boolean res = asistentDAO.esAsistentExiste(email, pass); // Verifica si el asistente existe

            if (res) {
                // Si las credenciales son válidas, configurar el bean de usuario
                AsistentDTO asistent = asistentDAO.getAsistentConEmail(email);
                userBean.setEmail(asistent.getEmail());
                userBean.setName(asistent.getName());
                userBean.setRole(asistent.getRole());
                userBean.setId(asistent.getID());

                // Redirigir según el rol del usuario
                if (userBean.getRole() == 1) {
                    nextPage = "../view/admin/adminmenu.jsp"; // Rol de administrador
                } else {
                    nextPage = "../view/user/usermenu.jsp"; // Rol de usuario normal
                }
                msgNextPage = "Login successful"; // Mensaje de éxito
            } else {            
                nextPage = "../../index.jsp"; // Redirige a la página de inicio en caso de error
                msgNextPage = "Invalid credentials"; // Mensaje de error
            }
        } catch (Exception e) {
            e.printStackTrace(); // Manejo de excepciones (puedes personalizar la gestión de errores)
            nextPage = "../../index.jsp";
            msgNextPage = "An error occurred while processing your request."; // Mensaje de error genérico
        }
    }
%>

<!-- Redirige a la página correspondiente con el mensaje -->
<jsp:forward page="<%=nextPage%>">
    <jsp:param name="message" value="<%=msgNextPage%>" />
</jsp:forward>
