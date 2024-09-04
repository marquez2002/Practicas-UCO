<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ page import="display.userbean.userBean" %>
<%@ page import="data.dao.CampDAO.CampDAO" %>
<%@ page import="business.inscription.InscriptionDTO" %>
<%@ page import="data.dao.InscriptionDAO.InscriptionDAO" %>
<%@ page import="business.camp.CampDTO" %>
<%@ page import="java.util.ArrayList" %>
<%@ page import="java.util.Date" %>

<jsp:useBean id="userBean" class="display.userbean.userBean" scope="session" />

<!--  
    Este archivo JSP corresponde al menú del usuario.
    Proporciona opciones y muestra información sobre los campamentos en los que el usuario está inscrito.
    También permite buscar campamentos disponibles y registrar nuevas inscripciones.
-->

<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Menú Usuario</title>
    <link rel="stylesheet" type="text/css" href="<%= request.getContextPath() %>/css/header.css">
	<link rel="stylesheet" type="text/css" href="<%= request.getContextPath() %>/css/common.css">
	<link rel="stylesheet" type="text/css" href="<%= request.getContextPath() %>/css/footer.css">
    <link rel="icon" type="image/png" href="<%= request.getContextPath() %>/images/campFire_favicon.png" sizes="16x16">   
    <script src="../../JS/userMenu.js"></script>
</head>
<body>
    <br><br><br><br><br><br>

<%
	if (userBean.getRole() == 0 && userBean.getId()>0) {
	        java.util.Date date = new java.util.Date();
	%>
	        <jsp:include page="/common/header.jsp" />
	        <h1>¡Bienvenido al menú de usuario, <%= userBean.getName() %>!</h1>
	        <hr>
	 
	        <div class="center">
	            <div id="error-container" style="color: red;"></div>
		
	            <!-- Formulario para registrar una nueva inscripción -->
	            <form action="<%= request.getContextPath() %>/mvc/view/user/registerInscription.jsp" method="post">
	                <p>
	                    <input type="submit" value="Campamentos y Inscripciones">
	                </p>
	            </form>
	        </div>
	
	<%
	        // Obtener el ID del usuario
	        int userId = userBean.getId();
	
	        String file = application.getInitParameter("sqlproperties");
	        try (java.io.InputStream myIO = application.getResourceAsStream(file)) {
	            java.util.Properties prop = new java.util.Properties();
	            prop.load(myIO);
	
	            CampDAO campDAO = new CampDAO(prop);
	            InscriptionDAO inscriptionDAO = new InscriptionDAO(prop);
	
	            ArrayList<InscriptionDTO> userInscriptions = inscriptionDAO.getAsistentInscriptionsById(userId);
	            ArrayList<CampDTO> userCamps = new ArrayList<>();
	
	            for (InscriptionDTO inscription : userInscriptions) {
	                CampDTO camp = campDAO.getCamp(inscription.getIdCamp());
	                if (camp != null) {
	                    userCamps.add(camp);
	                }
	            }	           	           
	
	            if (!userCamps.isEmpty()) {
	%>
	                <table >
	                    <caption><strong>Campamentos a los que perteneces:</strong></caption>
	                    <thead>
	                        <tr>
	                            <th class="left-th" style="text-align: center">ID Campamento</th>
	                            <th style="text-align: center">Fecha de inicio</th>
	                            <th style="text-align: center">Cancelación</th>
	                            <th class="right-th" style="text-align: center">Ver información</th>
	                        </tr>
	                    </thead>
	                    <tbody>
	                        <% 
	                        // Iterar sobre los campamentos y mostrar información
	                        for (int i = 0; i < userCamps.size(); i++) {
	                            CampDTO camp = userCamps.get(i);	                            
	                            InscriptionDTO inscription = userInscriptions.get(i);
	                            Date currentDate = new Date();
	                	        Date startDate = camp.getStartDate();
	                	        long daysDifference = (startDate.getTime() - currentDate.getTime()) / (1000 * 60 * 60 * 24);
	                        %>
	                        <tr>
	                            <td style="text-align: center"><%= camp.getID() %></td>
	                            <td style="text-align: center"><%= camp.getStartDate() %></td>
	                            <td style="text-align: center">
	                                <% if (daysDifference > 15) { %>
	                                    <!-- Formulario para cancelar inscripción -->
	                                    <form action="<%= request.getContextPath() %>/CancelInscription" method="post" style="display: inline; margin: 0; padding: 0;">
	                                        <input type="hidden" name="idCamp" value="<%= camp.getID() %>">
	                                        <input type="hidden" name="idAsistent" value="<%= userBean.getId() %>">
	                                        <button class="small-button">Cancelar Inscripción</button>
	                                    </form>
	                                <% } else { %>
	                                    <button class="fake-small-button">Cancelar Inscripción</button>
	                                <% } %>
	                            </td>
	                            <td style="text-align: center">
	                                <!-- Formulario para ver información del campamento -->
	                                <form action="<%= request.getContextPath() %>/mvc/view/admin/inscriptionCamp.jsp?id=<%= camp.getID() %>" method="post">
	                                    <button class="smaller-button">INFO</button>
	                                </form>
	                            </td>
	                        </tr>
	                        <% } %>
	                    </tbody>
	                </table>
	<%
	            } else {
	%>
	                <br><br><h2>Todavía no está inscrito en ningún campamento.</h2><br><br>	
	<%
	            }
	        }
	    } else {
	        // Redirigir si el usuario no tiene el rol correcto
	        response.sendRedirect("../../../errorpage.html");
	    }
	%>
	
<jsp:include page="/common/footer.jsp" />
</body>
</html>
