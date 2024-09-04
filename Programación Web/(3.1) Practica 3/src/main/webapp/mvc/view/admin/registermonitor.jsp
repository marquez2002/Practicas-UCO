<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ page import="display.userbean.userBean"%>
<%@ page import="servlet.admin.RegisterMonitor"%>

<jsp:useBean id="userBean" class="display.userbean.userBean" scope="session" />

<!-- 
    Esta página JSP permite registrar un determinado monitor. 
-->

<!DOCTYPE html>
<html lang="es">
<head>
    <meta charset="UTF-8">
    <title>Registrar Monitor</title>
    <link rel="stylesheet" type="text/css" href="<%= request.getContextPath() %>/css/header.css">
    <link rel="stylesheet" type="text/css" href="<%= request.getContextPath() %>/css/common.css">
    <link rel="stylesheet" type="text/css" href="<%= request.getContextPath() %>/css/footer.css">
    <link rel="icon" type="image/png" href="<%= request.getContextPath() %>/images/campFire_favicon.png" sizes="16x16">
    <script src="../../../JS/RegisterMonitor.js"></script>
</head>

<jsp:include page="/common/logout.jsp" />

<body>
    <br><br><br><br><br><br>
    
    <% if (userBean.getRole() == 1) { %>
        <h1>Registra un nuevo monitor</h1>
        <div>
            <form action="<%= request.getContextPath() %>/RegisterMonitor" method="post" onsubmit="return validateForm()">
                <section>
                    <div class="align">
                        <label for="name">Nombre</label>
                        <input type="text" name="name" placeholder="Nombre">
                    </div>
                    <div class="align">
                        <label for="surname">Apellidos</label>
                        <input type="text" name="surname" placeholder="Apellidos">
                    </div>
                </section>

                <div class="form-group">
			        <label>Atención Especial</label>
			        <div class="radio-group">
			            <input type="radio" id="yes" name="special" value="true" required>
			            <label for="yes">Sí</label>
			            <input type="radio" id="no" name="special" value="false" required>
			            <label for="no">No</label>
			        </div>
			    </div>
                <button type="submit">Aceptar</button>
            </form>
        </div>
    <% } else { 
        response.sendRedirect("../../../errorpage.html");
    } %>
</body>

<jsp:include page="/common/footer.jsp" />
</html>
