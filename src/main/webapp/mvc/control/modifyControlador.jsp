<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ page import="display.userbean.userBean" %>
<%@ page import="data.dao.AsistentDAO.AsistentDAO" %>
<%@ page import="business.asistent.AsistentDTO" %>
<jsp:useBean id="userBean" scope="session" class="display.userbean.userBean" />

<%
    String nextPage = "../../index.jsp";
    String mensajeNextPage = "Error. Para modificar sus datos, primero debe iniciar sesión.";

    // Verifica si el usuario está autenticado
    if (userBean != null && !userBean.getEmail().isEmpty()) {
        String name = request.getParameter("name");
        String surname = request.getParameter("surname");
        String email = request.getParameter("email");
        String date = request.getParameter("date");
        String password = request.getParameter("password");
        int role = userBean.getRole();

        // Carga las propiedades desde el archivo de configuración
        String file = application.getInitParameter("sqlproperties");
        try (java.io.InputStream myIO = application.getResourceAsStream(file)) {
            java.util.Properties prop = new java.util.Properties();
            prop.load(myIO);

            AsistentDAO asistentDAO = new AsistentDAO(prop);
            boolean isUpdated = false;

            // Verifica el rol del usuario y actualiza la información correspondiente
            if (name != null) {
                asistentDAO.modificarAsistent(name, surname, email, password, role, date, false);
                isUpdated = true; // Actualización exitosa
            }

            if (isUpdated) {
                mensajeNextPage = "La información ha sido actualizada de manera exitosa";
                %>
                <jsp:setProperty property="name" value="<%=name%>" name="userBean" />
                <%
                nextPage = (role == 1) ? "../view/admin/adminmenu.jsp" : "../view/user/usermenu.jsp";
            } else {
                nextPage = (role == 1) ? "../view/admin/modifyadmin.jsp" : "../view/user/modifyuser.jsp"; 
            }
        } catch (Exception e) {
            e.printStackTrace(); 
            mensajeNextPage = "Ha ocurrido un error al procesar su solicitud."; 
        }
    }
%>

<!-- Redirige a la página correspondiente con el mensaje -->
<jsp:forward page="<%=nextPage%>">
    <jsp:param name="message" value="<%=mensajeNextPage%>" />
</jsp:forward>
