<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<%@ page import="display.userbean.userBean" %>

<jsp:useBean id="userBean" class="display.userbean.userBean" scope="session" />

<!--
    Este archivo JSP maneja el formulario de registro de usuarios en el modo administrador.
-->

<!DOCTYPE html>
<html lang="es">
<head>
    <meta charset="UTF-8">
    <title>Registrar Usuario</title>
    <link rel="stylesheet" type="text/css" href="<%= request.getContextPath() %>/css/header.css">
    <link rel="stylesheet" type="text/css" href="<%= request.getContextPath() %>/css/common.css">
    <link rel="stylesheet" type="text/css" href="<%= request.getContextPath() %>/css/footer.css"> 
    <link rel="icon" type="image/png" href="<%= request.getContextPath() %>/images/campFire_favicon.png" sizes="16x16">
</head>

<body>
    <jsp:include page="/common/logout.jsp"/>

    <% if (userBean.getRole() == 1) { %>
        <br><br><br><br><br><br>
        <h1>REGISTRAR USUARIOS</h1>
        <div>
            <form action="<%= request.getContextPath() %>/mvc/control/registerControlador.jsp" method="post">
                <section>
                    <div class="login">
                        <label for="mail">Email</label>
                        <input type="email" name="email" placeholder="example@gmail.com" required>
                    </div>
                    <div class="align">
                        <label for="password">Contraseña</label>
                        <input type="password" name="password" placeholder="Password" required>
                    </div>
                </section>
                
                <section>
                    <div class="align">
                        <label for="name">Nombre</label>
                        <input type="text" name="name" placeholder="Nombre" required>
                    </div>
                    <div class="align">
                        <label for="surname">Apellidos</label>
                        <input type="text" name="surname" placeholder="Apellidos" required>
                    </div>
                </section>
                
                <section>
                    <div class="align">
                        <label for="date">Fecha de Nacimiento</label>
                        <input class="center" type="date" name="date" placeholder="1/1/1977" required>
                    </div>
                    <div class="form-group">
					    <label>Atención Especial</label>
					    <div class="radio-group">
					        <input type="radio" id="yes" name="special" value="true" required>
					        <label for="yes">Sí</label>
					        <input type="radio" id="no" name="special" value="false" required>
					        <label for="no">No</label>
					    </div>
					</div>
                </section>
                
                <section>
                    <div class="align center">
                        <label for="role">Rol</label>
                        <select class="center" name="role" id="role" required>
                            <option value="">...</option>
                            <option value="0">Asistente</option>
                            <option value="1">Administrador</option>
                        </select>
                    </div>
                </section>

                <div id="error-container" style="color: red;"></div> <!-- Contenedor para mensajes de error -->
                <h1><button type="submit">Aceptar</button></h1>
            </form>
        </div>

    <% } else { 
        // Redirige a la página de error si el usuario no es administrador
        response.sendRedirect("../../../errorpage.html");
    } %>
</body>
</html>
