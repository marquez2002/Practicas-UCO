<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ page import="display.userbean.userBean"%>
<%@ page import="data.dao.CampDAO.CampDAO"%>
<%@ page import="java.util.Properties"%>

<jsp:useBean id="userBean" class="display.userbean.userBean" scope="session" />

<!--  
    Este archivo JSP permite a los usuarios buscar campamentos disponibles entre dos fechas.
    Permite a los usuarios con rol de administrador buscar campamentos disponibles durante un período específico.
-->

<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Búsqueda Campamentos</title>
    <link rel="stylesheet" type="text/css" href="<%= request.getContextPath() %>/css/header.css">
	<link rel="stylesheet" type="text/css" href="<%= request.getContextPath() %>/css/common.css">
	<link rel="stylesheet" type="text/css" href="<%= request.getContextPath() %>/css/footer.css">
    <link rel="icon" type="image/png" href="<%= request.getContextPath() %>/images/campFire_favicon.png" sizes="16x16"> 
    <script src="../../../JS/Date.js"></script>
</head>

<body>
    <jsp:include page="/common/logout.jsp" />

    <%
    // Verifica si el usuario está autenticado y tiene el rol adecuado
    if (userBean != null && userBean.getRole() == 0) {
        String file = application.getInitParameter("sqlproperties");
        CampDAO campDAO = null;
        
        try (java.io.InputStream myIO = application.getResourceAsStream(file)) {
            Properties prop = new Properties();
            prop.load(myIO);
            campDAO = new CampDAO(prop);
        } catch (Exception e) {
            e.printStackTrace(); 
            response.sendRedirect("../../../errorpage.html");
            return; 
        }
    %>
        <br><br><br><br><br><br>
        <h1>Búsqueda de Campamentos</h1>        
        <div>
    <form action="<%= request.getContextPath() %>/mvc/view/user/listarCampDisponible.jsp" method="post" onsubmit="return validateForm()">
        <p class="center"><b>Indique las fechas deseadas:</b></p>
        <div class="align">
            <label for="startDate">Primera fecha:</label>
            <input class="center" type="date" id="startDate" name="startDate" required>
        </div>
        <div class="align">
            <label for="endDate">Segunda fecha:</label>
            <input class="center" type="date" id="endDate" name="endDate" required>
        </div>
        <div id="error-container" style="color: red;"></div>                
        <h1><button type="submit">Aceptar</button></h1>
    </form>
</div>
    <%
    } else {
        // Redirige si el usuario no tiene el rol adecuado o no está autenticado
        response.sendRedirect("../../../errorpage.html");
    }
    %>

    <jsp:include page="/common/footer.jsp" />
</body>
</html>
