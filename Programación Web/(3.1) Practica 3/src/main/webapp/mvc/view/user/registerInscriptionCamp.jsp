<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<%@ page import="display.userbean.userBean" %>
<%@ page import="data.dao.CampDAO.CampDAO" %>
<%@ page import="data.dao.InscriptionDAO.InscriptionDAO" %>
<%@ page import="business.camp.CampDTO" %>
<%@ page import="java.util.ArrayList" %>
<%@ page import="java.util.Date" %>

<jsp:useBean id="userBean" class="display.userbean.userBean" scope="session" />

<!--  
    Este archivo JSP permite a los usuarios registrar su inscripción en un campamento específico.
    Obtiene datos del campamento y las inscripciones existentes para calcular el número de plazas disponibles.
    Muestra la información del campamento y permite al usuario seleccionar el tipo de inscripción.
-->

<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Registrar Inscripción</title>
    <link rel="stylesheet" type="text/css" href="<%= request.getContextPath() %>/css/header.css">
	<link rel="stylesheet" type="text/css" href="<%= request.getContextPath() %>/css/common.css">
	<link rel="stylesheet" type="text/css" href="<%= request.getContextPath() %>/css/footer.css">
    <link rel="icon" type="image/png" href="<%= request.getContextPath() %>/images/campFire_favicon.png" sizes="16x16">
    <script src="../../../JS/registerInscriptionCamp.js"></script>
</head>
<body>
    <jsp:include page="/common/logout.jsp" />
    <br><br><br><br><br><br>

    <% if (userBean != null && userBean.getRole() == 0) { %>
        <% 
        String Stringid = request.getParameter("id");
        int id = Integer.parseInt(Stringid);
        
        // Cargar propiedades de conexión a la base de datos
        String file = application.getInitParameter("sqlproperties");
        java.io.InputStream myIO = application.getResourceAsStream(file);
        java.util.Properties prop = new java.util.Properties();
        prop.load(myIO);
        
        InscriptionDAO insDao = new InscriptionDAO(prop);
        CampDAO campDAO = new CampDAO(prop);
        
        ArrayList<String> activities = campDAO.getActivitiesEnCamp(id);
        CampDTO camp = campDAO.getCamp(id);
        int ins = insDao.contarInscriptionsCamp(id);
        Date startDate = camp.getStartDate();
        
        // Calcular capacidad disponible
        int capacity = camp.getMaximunAsistent() - ins;
        %>

        <h1>REGISTRAR INSCRIPCIÓN AL CAMPAMENTO <%= id %></h1>
        
        <form action="<%= request.getContextPath() %>/AcceptInscription" method="post" onsubmit="return validateForm()">
            <br />
            <table>
                <tr style="text-align: center">
                    <th scope="row">Id</th>
                    <td><%= camp.getID() %></td>
                </tr>
                <tr style="text-align: center">
                    <th scope="row">Nivel</th>
                    <td><%= camp.getLevelEducation() %></td>
                </tr>
                <tr style="text-align: center">
                    <th scope="row">Comienzo</th>
                    <td><%= camp.getStartDate() %></td>
                </tr>
                <tr style="text-align: center">
                    <th scope="row">Fin</th>
                    <td><%= camp.getEndDate() %></td>
                </tr>
                <tr style="text-align: center">
                    <th scope="row">Plazas Restantes</th>
                    <td><%= capacity %></td>
                </tr>
                <tr style="text-align: center">
                    <th scope="row">Aforo Máximo</th>
                    <td><%= camp.getMaximunAsistent() %></td>
                </tr>
                <tr style="text-align: center">
                    <th scope="row">Actividades</th>
                    <td colspan="2">
                        <%
                        for (String activity : activities) {
                        %>
                        <div><%= activity %></div>
                        <%
                        }
                        %>
                    </td>
                </tr>
            </table>
            <br>
            <input type="hidden" name="id" value="<%= id %>">
            <label for="inscription">Seleccione el tipo de inscripción:</label>
            <select class="select-type center" name="inscription" id="inscription">
                <option value="">...</option>
                <option value="COMPLETA">Completa</option>
                <option value="PARCIAL">Parcial</option>
            </select>

            <%
            Date currentDate = new Date();
            long timeDifference = startDate.getTime() - currentDate.getTime();
            long daysDifference = timeDifference / (1000 * 60 * 60 * 24);

            if (daysDifference > 15) {
            %>
            <h2>Usted está realizando la inscripción en modalidad temprana.</h2>
            <%
            } else {
            %>
            <h2>Usted está realizando la inscripción en modalidad tardía. Tenga en cuenta que esta modalidad no admite cancelación.</h2>
            <%
            }
            %>
            <div id="error-container" style="color: red;"></div>
            <h1><button>Continuar</button></h1>
        </form>
        <br><br><br><br>
    <% } else {
        // Redirigir a la página de error si el usuario no está autenticado
        response.sendRedirect("../../../errorpage.html");
    } %>
    
    <jsp:include page="/common/footer.jsp" />
</body>
</html>
