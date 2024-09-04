<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<%@ page import="data.dao.CampDAO.CampDAO" %>
<%@ page import="business.camp.CampDTO" %>
<%@ page import="data.dao.InscriptionDAO.InscriptionDAO" %>
<%@ page import="business.inscription.InscriptionDTO" %>
<%@ page import="java.util.ArrayList" %>
<%@ page import="display.userbean.userBean" %>
<jsp:useBean id="userBean" class="display.userbean.userBean" scope="session" />

<!-- 
    Esta página JSP permite al administrador mostrar los detalles del campamento y sus inscripciones. 
    Muestra una tabla con información sobre los campamentos disponibles y permite al administrador asociar monitores a esos campamentos.    
-->

<!DOCTYPE html>
<html lang="es">
<head>
    <meta charset="UTF-8">
    <title>Inscripciones del Campamento</title>
    <link rel="stylesheet" type="text/css" href="<%= request.getContextPath() %>/css/header.css">
    <link rel="stylesheet" type="text/css" href="<%= request.getContextPath() %>/css/common.css">
    <link rel="stylesheet" type="text/css" href="<%= request.getContextPath() %>/css/footer.css">
    <link rel="icon" type="image/png" href="<%= request.getContextPath() %>/images/campFire_favicon.png" sizes="16x16">  
</head>

<jsp:include page="/common/logout.jsp" />

<body>
	<br><br><br><br><br><br>
<%
    // Verificar si el usuario está autenticado
    if (userBean != null) {
        int campID = Integer.parseInt(request.getParameter("id"));

        // Cargar propiedades de configuración
        String file = application.getInitParameter("sqlproperties");
        java.io.InputStream myIO = application.getResourceAsStream(file);
        java.util.Properties prop = new java.util.Properties();
        prop.load(myIO);

        // Inicializar DAOs y cargar datos del campamento
        CampDAO campDAO = new CampDAO(prop);
        CampDTO camp = campDAO.getCamp(campID);
        ArrayList<String> activities = campDAO.getActivitiesEnCamp(campID);
        
        InscriptionDAO inscriptionDAO = new InscriptionDAO(prop);
        ArrayList<InscriptionDTO> array = inscriptionDAO.printInscriptions();
%>

    <h1>Inscripciones del Campamento <%= campID %></h1>
    <table>
        <tr>
            <th scope="row">Id</th>
            <td><%= camp.getID() %></td>
        </tr>
        <tr>
            <th scope="row">Nivel</th>
            <td><%= camp.getLevelEducation() %></td>
        </tr>
        <tr>
            <th scope="row">Comienzo</th>
            <td><%= camp.getStartDate() %></td>
        </tr>
        <tr>
            <th scope="row">Fin</th>
            <td><%= camp.getEndDate() %></td>
        </tr>
        <tr>
            <th scope="row">Aforo Máximo</th>
            <td><%= camp.getMaximunAsistent() %></td>
        </tr>
        <tr>
            <th scope="row">Actividades</th>
            <td colspan="2"> 
                <%
                // Mostrar actividades del campamento
                for (String activity : activities) {
                %>
                    <div><%= activity %></div>
                <%
                }
                %>
            </td>
        </tr>
    </table>

    <%
    // Mostrar detalles de inscripciones si el usuario es administrador
    if (userBean.getRole() == 1) {
    %>
        <h2>Detalles de las Inscripciones:</h2>
        <ul>
        <%
            // Filtrar y mostrar inscripciones del campamento
            for (InscriptionDTO inscripcion : array) {
                if (inscripcion.getIdCamp() == campID) {
                    String estado = inscripcion.getCompletada() ? "Completa" : "Parcial";
        %>
                    <li>Inscripción del participante con id=<%= inscripcion.getIdAsistent() %>: <%= estado %></li>
        <%
                }
            }
        %>
        </ul>
    <%
    }
}
%>
</body>
</html>
