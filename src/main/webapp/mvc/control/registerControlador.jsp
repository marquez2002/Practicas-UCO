<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ page import="display.userbean.userBean" %>
<%@ page import="data.dao.AsistentDAO.AsistentDAO" %>
<%@ page import="business.asistent.AsistentDTO" %>
<jsp:useBean id="userBean" scope="session" class="display.userbean.userBean" />

<%
    String nextPage = "../view/registerview.jsp"; // Página predeterminada en caso de error
    String mensajeNextPage;

    // Permitir registro si no hay usuario logueado o si el usuario logueado es administrador
    if (userBean == null || userBean.getEmail().isEmpty() || userBean.getRole() == 1) {
        // Recuperar parámetros del formulario
        String name = request.getParameter("name");
        String surname = request.getParameter("surname");
        String email = request.getParameter("email");
        String date = request.getParameter("date");
        String password = request.getParameter("password");
        String specialParam = request.getParameter("special");     	     
        String roleStr = request.getParameter("role");
        
        boolean special = Boolean.parseBoolean(specialParam);
        // Determinar el rol del asistente
        int role = (userBean != null && userBean.getRole() == 1 && roleStr != null) 
                        ? Integer.parseInt(roleStr) 
                        : 0;

        // Verificar si hay parámetros requeridos para el registro
        if (email != null && !email.isEmpty()) {
            // Cargar propiedades desde el archivo de configuración
            String file = application.getInitParameter("sqlproperties");
            try (java.io.InputStream myIO = application.getResourceAsStream(file)) {
                java.util.Properties prop = new java.util.Properties();
                prop.load(myIO);
                AsistentDAO asistent = new AsistentDAO(prop);

                // Comprobar si el usuario ya existe
                if (asistent.esAsistentRegistrado(email)) {
                    mensajeNextPage = "Este email ya ha sido registrado en la web.";
                } else {
                    // Registrar nuevo usuario
                    asistent.registrarAsistent(name, surname, email, password, role, date, special);
                    mensajeNextPage = "Registro exitoso.";
                    nextPage = "../../index.jsp"; // Redirigir a la página de inicio
                }
            } catch (Exception e) {
                e.printStackTrace();
                mensajeNextPage = "Error al procesar el registro. Inténtelo de nuevo.";
            }
        } else {
            mensajeNextPage = "Faltan datos para el registro.";
        }
    } else {
        mensajeNextPage = "No tienes permiso para registrar nuevos usuarios.";
    }
%>

<jsp:forward page="<%= nextPage %>">
    <jsp:param name="message" value="<%= mensajeNextPage %>" />
</jsp:forward>
