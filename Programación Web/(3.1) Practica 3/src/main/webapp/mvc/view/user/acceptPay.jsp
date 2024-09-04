	<%@ page language="java" contentType="text/html; charset=UTF-8"
		pageEncoding="UTF-8"%>
		<%@ page import="display.userbean.userBean"%>
	    <jsp:useBean id="userBean" class="display.userbean.userBean"
		scope="session" />
	<%@ page import="display.userbean.userBean" %>
	<%@ page import="data.dao.CampDAO.CampDAO" %>
	<%@ page import="data.dao.InscriptionDAO.InscriptionDAO" %>
	<%@ page import="data.dao.ActivityDAO.ActivityDAO" %>
	<%@ page import="data.dao.MonitorDAO.MonitorDAO" %>
	<%@ page import="business.camp.CampDTO" %>
	<%@ page import="business.activity.ActivityDTO" %>
	<%@ page import="java.util.ArrayList" %>
	<%@ page import="java.util.Date" %>
	
	<!--
	    Este archivo JSP maneja el proceso de pago e información de inscripciones a campamentos.
	
	    Funcionalidades:
	    - Muestra información detallada del campamento seleccionado para inscripción.
	    - Calcula y muestra el precio de la inscripción completa o parcial dependiendo del tipo de inscripción.
	    - Determina si la inscripción es cancelada dependiendo de la cercanía a la fecha de inicio del campamento.
	-->
	
	<!DOCTYPE html>
	<html>
	<head>
	    <meta charset="UTF-8">
	    <title>Pago</title>
	    <link rel="stylesheet" type="text/css" href="<%= request.getContextPath() %>/css/header.css">
		<link rel="stylesheet" type="text/css" href="<%= request.getContextPath() %>/css/common.css">
		<link rel="stylesheet" type="text/css" href="<%= request.getContextPath() %>/css/footer.css">
	    <link rel="icon" type="image/png" href="<%= request.getContextPath() %>/images/campFire_favicon.png" sizes="16x16">
	</head>
	
	<jsp:include page="/common/logout.jsp" />
	
	<body>
		<br><br><br><br><br><br>
	    <% 
	    if (userBean != null && userBean.getRole() == 0) { 
	        String Stringid = request.getParameter("id");
	        int id = Integer.parseInt(Stringid);
	        String file = application.getInitParameter("sqlproperties");
	        
	        // Cargar propiedades SQL
	        java.io.InputStream myIO = application.getResourceAsStream(file);
	        java.util.Properties prop = new java.util.Properties();
	        prop.load(myIO);
	        
	        // Crear objetos DAO
	        CampDAO campDAO = new CampDAO(prop);
	        InscriptionDAO inscriptionDAO = new InscriptionDAO(prop);
	        
	        // Obtener información del campamento y actividades
	        CampDTO camp = campDAO.getCamp(id);
	        ArrayList<String> activities = campDAO.getActivitiesEnCamp(id);
	        
	        boolean complete = false;
	        boolean cancelable = true;
	        String StringInscription = request.getParameter("inscription");
	        float price = -1;
	    %>
	       
	    <h1>INFORMACIÓN SOBRE EL PAGO</h1>
	     
	    <form action="<%= request.getContextPath() %>/RegisterInscription" method="post">
	        <table>
	            <tr>
	                <th scope="row">ID</th>
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
	                    for (String activity : activities) {
	                    %>
	                        <%= activity %><br>
	                    <%
	                    }
	                    %>
	                </td>
	            </tr>
	            <tr>
	                <th scope="row">Tipo de inscripción</th>
	                <td><%= StringInscription %></td>
	            </tr>
	        </table>
	
	        <%
	        // Calcular precios
	        int precioCompleto = inscriptionDAO.calcularPrecioCompleto(campDAO.contarActividadesCamp(id), StringInscription);
	        int precioParcial = inscriptionDAO.calcularPrecioParcial(campDAO.contarActividadesCamp(id), StringInscription);
	        
	        if ("COMPLETA".equals(StringInscription)) {
	        %>
	            <h2>El precio de su inscripción completa es de <%= precioCompleto %> €</h2>
	        <%
	            complete = true;
	        	price = precioCompleto;
	        } else if ("PARCIAL".equals(StringInscription)) {
	        %>
	            <h2>El precio de su inscripción parcial es de <%= precioParcial %> €</h2>
	        <%
	            complete = false;
	        	price = precioParcial;
	        }
	
	        // Calcular días hasta el inicio del campamento
	        Date currentDate = new Date();
	        Date startDate = camp.getStartDate();
	        long daysDifference = (startDate.getTime() - currentDate.getTime()) / (1000 * 60 * 60 * 24);
	
	        if (daysDifference > 15) {
	        %>
	            <h2>Usted está realizando la inscripción en modalidad temprana.</h2>
	        <%
	            cancelable = true;
	        } else {
	        %>
	            <h2>Usted está realizando la inscripción en modalidad tardía. Tenga en cuenta que esta modalidad no admite cancelación.</h2>
	        <%
	            cancelable = false;
	        }
	        %>	        
	
	        <br />
	        <h1><button type="submit">Aceptar</button></h1>
	        <p>
	            <input type="hidden" value="<%= camp.getID() %>" name="idCamp">
	            <input type="hidden" value="<%= userBean.getId() %>" name="idAsistent">
	            <input type="hidden" value="<%= price %>" name="price">
	            <input type="hidden" value="<%= complete %>" name="completada_">
	            <input type="hidden" value="<%= cancelable %>" name="cancelada_">	            
	        </p>
	    </form>   	    	    
	
	    <% 
	    } else {
	        response.sendRedirect("../../../errorpage.html");
	    }
	    %>
	        
	</body>
	<jsp:include page="/common/footer.jsp" />
	</html>
