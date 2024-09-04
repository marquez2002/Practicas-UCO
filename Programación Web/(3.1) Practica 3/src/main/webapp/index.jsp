<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ page import="display.userbean.userBean"%>
<jsp:useBean id="userBean" class="display.userbean.userBean" scope="session" />

<%
    // Verificamos si el usuario está autenticado
    if (userBean != null && userBean.getName() != null && !userBean.getName().isEmpty()) {
        // Redireccionar según el rol del usuario
        if (userBean.getRole() == 1) {
            response.sendRedirect("mvc/view/admin/adminmenu.jsp");
            return; // Aseguramos que el código no continúe después de la redirección
        } else {
            response.sendRedirect("mvc/view/user/usermenu.jsp");
            return; // Aseguramos que el código no continúe después de la redirección
        }
    }
%>

<!DOCTYPE html>
<html lang="es">
<head>
    <meta charset="UTF-8">
    <link rel="stylesheet" type="text/css" href="<%= request.getContextPath() %>/css/index.css">
    <title>Login</title>
    <link rel="icon" type="image/png" href="<%= request.getContextPath() %>/images/campFire_favicon.png" sizes="16x16">   
</head>

<body>
    <div class="background">
        <div class="shape"></div>
        <div class="shape"></div>
    </div>
    
    <div class="login-container">
        <form class="login" action="<%= request.getContextPath() %>/mvc/control/loginControlador.jsp" method="post">
            <h3>campFire</h3>
            <label for="mail">Correo Electrónico</label>
            <input type="email" name="mail" placeholder="example@gmail.com" required><br>
            <label for="passwd">Contraseña</label>
            <input type="password" name="password" placeholder="Contraseña" required><br>
            <div class="button-group">
                <button class="button1" type="submit">Iniciar Sesión</button>
                <button class="button2" type="button" onclick="window.location.href='<%= request.getContextPath() %>/mvc/view/registerview.jsp'">Registro</button>
            </div>
        </form>
    </div>
</body>
</html>
