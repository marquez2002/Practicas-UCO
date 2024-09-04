<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ page import="display.userbean.userBean"%>
<%@ page import="data.dao.AsistentDAO.AsistentDAO"%>
<%@ page import="business.asistent.AsistentDTO"%>

<jsp:useBean id="userBean" class="display.userbean.userBean" scope="session" />

<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Editar Datos</title>
    <link rel="stylesheet" type="text/css" href="<%= request.getContextPath() %>/css/header.css">
    <link rel="stylesheet" type="text/css" href="<%= request.getContextPath() %>/css/common.css">
    <link rel="stylesheet" type="text/css" href="<%= request.getContextPath() %>/css/footer.css">
    <link rel="icon" type="image/png" href="<%= request.getContextPath() %>/images/campFire_favicon.png" sizes="16x16">
    <script src="../../../JS/modifyuser.js"></script>
</head>

<!-- 
    Esta página JSP permite modificar los datos del administrador. 
-->

<jsp:include page="/common/logout.jsp" />
<body>
    <br><br><br><br><br><br>
    <% 
        String role = "";
        if (userBean.getRole() == 1) {
    %>
        <h1>Editar Datos de <%= userBean.getName() %></h1>

        <%
            String file = application.getInitParameter("sqlproperties");
            java.io.InputStream myIO = application.getResourceAsStream(file);
            java.util.Properties prop = new java.util.Properties();
            prop.load(myIO);

            AsistentDAO asistentDAO = new AsistentDAO(prop);
            AsistentDTO asistent = asistentDAO.getAsistentConEmail(userBean.getEmail());

            if (asistent.getRole() == 1) {
                role = "Administrador";
            } else {
                role = "Asistente";
            }
        %>

        <div>
            <form action="<%= request.getContextPath() %>/mvc/control/modifyControlador.jsp" method="post" onsubmit="return validateForm()">
                <section>
                    <div class="align">
                        <label for="email">Email</label>
                        <input type="email" name="email" value="<%= userBean.getEmail() %>" readonly="readonly">
                    </div>
                    <div class="align">
                        <label for="password">Contraseña</label>
                        <input type="password" name="password" value="<%= asistent.getPassword() %>">
                    </div>
                </section>

                <section>
                    <div class="align">
                        <label for="name">Nombre</label>
                        <input type="text" name="name" value="<%= asistent.getName() %>">
                    </div>
                    <div class="align">
                        <label for="surname">Apellidos</label>
                        <input type="text" name="surname" value="<%= asistent.getSurname() %>">
                    </div>
                </section>

                <section>
                    <div class="align">
                        <label for="date">Fecha de nacimiento</label>
                        <input class="center" type="date" name="date" value="<%= asistent.getDate() %>">
                    </div>
                    <div class="align">
                        <label for="role">Rol</label>
                        <input class="center" type="text" value="<%= role %>" readonly="readonly">
                    </div>
                </section>

                <div id="error-container" style="color: red;"></div>

                <h1><button>Aceptar</button></h1>
            </form>
        </div>
    <% 
        } else {
            response.sendRedirect("../../../errorpage.html");
        }
    %>
</body>

<jsp:include page="/common/footer.jsp" />

</html>
