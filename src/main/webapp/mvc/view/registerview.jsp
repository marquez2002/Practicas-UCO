<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<%@ page import="display.userbean.userBean" %>
<jsp:useBean id="userBean" class="display.userbean.userBean" scope="session" />

<!DOCTYPE html>
<html lang="es">
<head>
    <meta charset="UTF-8">
    <link rel="stylesheet" type="text/css" href="<%= request.getContextPath() %>/css/registro.css">
    <link rel="stylesheet" type="text/css" href="<%= request.getContextPath() %>/css/footer.css">
    <title>Registro</title>
    <link rel="icon" type="image/png" href="<%= request.getContextPath() %>/images/campFire_favicon.png" sizes="16x16">   
</head>
<body>
    <div class="background"></div>

    <a href="<%= request.getContextPath() %>/index.jsp" class="back-button">Atrás</a>

    <div class="register">
        <h3>Registro</h3>
	
        <form action="<%= request.getContextPath() %>/mvc/control/registerControlador.jsp" method="post" onsubmit="return validateForm()">
            <div class="form-row">
                <div class="form-group">
                    <label for="email">Email</label>
                    <input type="email" id="email" name="email" placeholder="example@gmail.com" required>
                </div>
	
                <div class="form-group">
                    <label for="password">Contraseña</label>
                    <input type="password" id="password" name="password" placeholder="Password" required>
                </div>
            </div>
	
            <div class="form-row">
                <div class="form-group">
                    <label for="name">Nombre</label>
                    <input type="text" id="name" name="name" placeholder="Nombre" required>
                </div>
	
                <div class="form-group">
                    <label for="surname">Apellidos</label>
                    <input type="text" id="surname" name="surname" placeholder="Apellidos" required>
                </div>
            </div>
	
            <div class="form-row">
                <div class="form-group">
                    <label for="birthdate">Fecha de Nacimiento</label>
                    <input type="date" id="birthdate" name="date" required>
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
            </div>
	
            <div id="error-container" class="error-container"></div>
	
            <button type="submit" class="button2">Aceptar</button>
        </form>
    </div>

    <script src="<%= request.getContextPath() %>/JS/Register.js" defer></script>
</body>

<jsp:include page="/common/footer.jsp" />
</html>
