<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<%@ page import="display.userbean.userBean" %>
<%@ page import="data.dao.CampDAO.CampDAO" %>
<%@ page import="business.camp.CampDTO" %>
<%@ page import="java.util.ArrayList" %>
<%@ page import="data.dao.InscriptionDAO.InscriptionDAO" %>
<%@ page import="business.inscription.InscriptionDTO" %>


<jsp:useBean id="userBean" class="display.userbean.userBean" scope="session" />

<!--  
    Este archivo JSP muestra una lista de campamentos disponibles para que los usuarios se inscriban.
    Se recuperan los campamentos disponibles y las inscripciones del usuario actual.
    La interfaz muestra una tabla con los campamentos disponibles y botones para inscribirse en cada uno.
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
</head>

<body>
    <jsp:include page="/common/logout.jsp" />
    <br><br><br><br><br><br>

    <% if (userBean != null) { %>
        <%
        // Cargar propiedades de conexión a la base de datos
        String file = application.getInitParameter("sqlproperties");
        java.io.InputStream myIO = application.getResourceAsStream(file);
        java.util.Properties prop = new java.util.Properties();
        prop.load(myIO);

        CampDAO campDAO = new CampDAO(prop);
        InscriptionDAO inscriptionDAO = new InscriptionDAO(prop);        
        int userId = userBean.getId();
        
        // Recuperar campamentos disponibles y las inscripciones del usuario
        ArrayList<CampDTO> campList = campDAO.buscarCampDisponibles();
        ArrayList<InscriptionDTO> userInscriptions = inscriptionDAO.getAsistentInscriptionsById(userId);
        %>

        <h1>REGISTRAR INSCRIPCIÓN</h1>
        <h2>Listado de campamentos disponibles:</h2>
        <table>
            <thead>
                <tr>
                    <th class="left-th" style="text-align: center">ID Campamento</th>
                    <th class="left-th" style="text-align: center">Nivel Educativo</th>
                    <th class="left-th" style="text-align: center">Fecha Inicio</th>
                    <th class="left-th" style="text-align: center">Fecha Fin</th>
                    <th class="right-th" style="text-align: center">Inscribirse</th>
                </tr>
            </thead>
            <tbody>
                <%
                // Iterar sobre la lista de campamentos
                for (CampDTO camp : campList) {
                    boolean userRegistered = false;
                    int capacity = inscriptionDAO.contarInscriptionsCamp(camp.getID());

                    // Verificar si el usuario está registrado en este campamento o si el cupo está completo
                    for (InscriptionDTO inscription : userInscriptions) {
                        if (inscription.getIdCamp() == camp.getID() || camp.getMaximunAsistent() <= capacity) {
                            userRegistered = true;
                            break;
                        }
                    }

                    // Mostrar el campamento solo si el usuario no está registrado en él y hay disponibilidad
                    if (!userRegistered) {
                %>
                    <tr>
                        <td style="text-align: center"><%= camp.getID() %></td>
                        <td style="text-align: center"><%= camp.getLevelEducation() %></td>
                        <td style="text-align: center"><%= camp.getStartDate() %></td>
                        <td style="text-align: center"><%= camp.getEndDate() %></td>
                        <td style="text-align: center">
                            <form action="<%= request.getContextPath() %>/mvc/view/user/registerInscriptionCamp.jsp?id=<%= camp.getID() %>" method="post">
                                <button class="small-button">Inscribirse</button>
                            </form>
                        </td>
                    </tr>
                <%
                    }
                }
                %>
            </tbody>
        </table>
    <% } %>
</body>
</html>
