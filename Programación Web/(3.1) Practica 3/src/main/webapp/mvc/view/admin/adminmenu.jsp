<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<%@ page import="display.userbean.userBean" %>
<%@ page import="data.dao.CampDAO.CampDAO" %>
<%@ page import="data.dao.InscriptionDAO.InscriptionDAO" %>
<%@ page import="data.dao.ActivityDAO.ActivityDAO" %>
<%@ page import="data.dao.MonitorDAO.MonitorDAO" %>
<%@ page import="business.camp.CampDTO" %>
<%@ page import="business.activity.ActivityDTO" %>
<%@ page import="java.util.ArrayList" %>

<jsp:useBean id="userBean" class="display.userbean.userBean" scope="session" />

<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Menu Administrador</title>
    <link rel="stylesheet" type="text/css" href="<%= request.getContextPath() %>/css/header.css">
    <link rel="stylesheet" type="text/css" href="<%= request.getContextPath() %>/css/common.css">
    <link rel="stylesheet" type="text/css" href="<%= request.getContextPath() %>/css/footer.css">  
    <link rel="icon" type="image/png" href="<%= request.getContextPath() %>/images/campFire_favicon.png" sizes="16x16">
</head>

<!-- 
    Esta página JSP representa el menú de administrador accesible 
    solo para usuarios con rol de administrador con distintas funciones.
-->

<body>
	<br><br><br><br><br><br>
    <%
        // Verifica si el usuario tiene el rol de administrador
        if (userBean.getRole() == 1) {
    %>

        <!-- Incluye el header común -->
        <jsp:include page="/common/header.jsp" />

        <h1>Bienvenido al Menú de Administrador, <%= userBean.getName() %></h1>

        <div class="center">
            <!-- Formularios para registrar y asociar diferentes elementos -->
            <form action="<%= request.getContextPath() %>/mvc/view/admin/registeruser.jsp" method="post">
                <p><input type="submit" value="Registrar Usuario"></p>
            </form>
            <form action="<%= request.getContextPath() %>/mvc/view/admin/registermonitor.jsp" method="post">
                <p><input type="submit" value="Registrar Monitor"></p>
            </form>
            <form action="<%= request.getContextPath() %>/mvc/view/admin/registercamp.jsp" method="post">
                <p><input type="submit" value="Registrar Campamento"></p>
            </form>
            <form action="<%= request.getContextPath() %>/mvc/view/admin/registeractivity.jsp" method="post">
                <p><input type="submit" value="Registrar Actividad"></p>
            </form>
            <form action="<%= request.getContextPath() %>/mvc/view/admin/asociarActividadCamp.jsp" method="post">
                <p><input type="submit" value="Asociar Actividad a Campamento"></p>
            </form>
            <form action="<%= request.getContextPath() %>/mvc/view/admin/asociarMonitorActividad.jsp" method="post">
                <p><input type="submit" value="Asociar Monitor a Actividad"></p>
            </form>
            <form action="<%= request.getContextPath() %>/mvc/view/admin/asociarMonitorCampamento.jsp" method="post">
                <p><input type="submit" value="Asociar Monitor a Campamento"></p>
            </form>
        </div>

        <!-- Tabla para mostrar los campamentos disponibles -->
        <table>
            <caption><strong>Campamentos Disponibles</strong></caption>
            <thead>
                <tr>
                    <th class="left-th" style="text-align: center">ID Campamento</th>
                    <th style="text-align: center">Inscripciones</th>
                    <th class="right-th" style="text-align: center">Más información</th>
                </tr>
            </thead>
            <tbody>
            <%
                // Carga las propiedades desde el archivo de configuración
                String file = application.getInitParameter("sqlproperties");
                java.io.InputStream myIO = application.getResourceAsStream(file);
                java.util.Properties prop = new java.util.Properties();
                prop.load(myIO);

                // Inicializa los DAO necesarios
                CampDAO campDAO = new CampDAO(prop);
                InscriptionDAO inscriptionDAO = new InscriptionDAO(prop);
                ArrayList<Integer> array = campDAO.imprimirCampsID(); // Obtiene los IDs de los campamentos

                // Itera sobre cada campamento para mostrar sus datos
                for (int i = 0; i < array.size(); i++) {
                    int num = inscriptionDAO.contarInscriptionsCamp(array.get(i));
            %>
                <tr>
                    <td style="text-align: center"><%= array.get(i) %></td> <!-- ID del campamento -->
                    <td style="text-align: center"><%= num %></td> <!-- Número de inscripciones -->
                    <td style="text-align: center">
                        <form action="<%= request.getContextPath() %>/mvc/view/admin/inscriptionCamp.jsp?id=<%= array.get(i) %>" method="post">
                            <button class="smaller-button">Información</button>
                        </form>
                    </td>
                </tr>
            <%
                }
            %>
            </tbody>
        </table>

    <%
        } else {
            // Redirige a la página de error si el usuario no es administrador
            response.sendRedirect("../../../errorpage.html");
        }
    %>

    <!-- Incluye el footer común -->
    <jsp:include page="/common/footer.jsp" />
</body>
</html>
