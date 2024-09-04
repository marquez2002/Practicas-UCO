<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<%@ page import="display.userbean.userBean" %>
<%@ page import="data.dao.AsistentDAO.AsistentDAO" %>
<%@ page import="business.asistent.AsistentDTO" %>

<jsp:useBean id="userBean" class="display.userbean.userBean" scope="session" />

<!-- 
    Este archivo JSP permite a un usuario con rol 0 asistente editar su información personal.   
    Los campos de email y atención especial son de solo lectura.
-->

<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Editar Datos</title>
    <link rel="stylesheet" type="text/css" href="<%= request.getContextPath() %>/css/header.css">
	<link rel="stylesheet" type="text/css" href="<%= request.getContextPath() %>/css/common.css">
	<link rel="stylesheet" type="text/css" href="<%= request.getContextPath() %>/css/footer.css">
    <link rel="icon" type="image/png" href="<%= request.getContextPath() %>/images/campFire_favicon.png" sizes="16x16"> 
    <script src="<%= request.getContextPath() %>/JS/modifyuser.js"></script>
</head>

<body>
    <jsp:include page="/common/logout.jsp" />
    <br><br><br><br><br><br>
    
    <%
    // Verifica el rol del usuario antes de permitir la edición
    if (userBean.getRole() == 0) {
        String file = application.getInitParameter("sqlproperties");
        java.io.InputStream myIO = application.getResourceAsStream(file);
        java.util.Properties prop = new java.util.Properties();
        prop.load(myIO);
        
        AsistentDAO asistentDAO = new AsistentDAO(prop);
        AsistentDTO asistent = asistentDAO.getAsistentConEmail(userBean.getEmail());
    %>
    
    <h1>Editar Datos de <%= userBean.getName() %></h1>
    <div>
        <form action="<%= request.getContextPath() %>/mvc/control/modifyControlador.jsp" method="post" onsubmit="return validateForm()">
            <section>
                <div class="align">
                    <label for="mail">Email</label>
                    <input type="email" name="email" value="<%= userBean.getEmail() %>" readonly>
                </div>
                <div class="align">
                    <label for="passwd">Contraseña</label>
                    <input type="password" name="password" value="<%= asistent.getPassword() %>">
                </div>
            </section>
            <section>
                <div class="align">
                    <label for="name">Nombre</label>
                    <input type="text" name="name" value="<%= asistent.getName() %>" required>
                </div>
                <div class="align">
                    <label for="surname">Apellidos</label>
                    <input type="text" name="surname" value="<%= asistent.getSurname() %>" required>
                </div>
            </section>
            <section>
                <div class="align">
                    <label for="birthdate">Fecha de Nacimiento</label>
                    <input class="center" type="date" name="date" value="<%= asistent.getDate() %>" required>
                </div>
                <div class="align">
                    <label for="special">Atención especial</label>
                    <input class="center" type="text" value="<%= asistent.getEspecial() ? "Sí" : "No" %>" readonly>
                </div>
            </section>
            
            <div id="error-container" style="color: red;"></div>
            <h1><button type="submit">Aceptar</button></h1>
        </form>
    </div>
    
    <% 
    } else {
        // Redirige a la página de error si el usuario no tiene el rol adecuado
        response.sendRedirect("../../../errorpage.html");
    } 
    %>
    
    <jsp:include page="/common/footer.jsp" />
</body>
</html>
