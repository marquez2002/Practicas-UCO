<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ page import="display.userbean.userBean"%>
<%@ page import="data.dao.CampDAO.CampDAO"%>
<%@ page import="business.camp.CampDTO"%>
<%@ page import="data.dao.InscriptionDAO.InscriptionDAO"%>
<%@ page import="business.inscription.InscriptionDTO"%>
<%@ page import="data.dao.ActivityDAO.ActivityDAO"%>
<%@ page import="business.activity.ActivityDTO"%>
<%@ page import="java.util.ArrayList"%>
<%@ page import="java.util.Iterator"%>

<jsp:useBean id="userBean" scope="session" class="display.userbean.userBean"></jsp:useBean>

<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Asociar Actividad a Campamento</title>
    <link rel="stylesheet" type="text/css" href="<%= request.getContextPath() %>/css/header.css">
    <link rel="stylesheet" type="text/css" href="<%= request.getContextPath() %>/css/common.css">
    <link rel="stylesheet" type="text/css" href="<%= request.getContextPath() %>/css/footer.css">  
    <link rel="icon" type="image/png" href="<%= request.getContextPath() %>/images/campFire_favicon.png" sizes="16x16">
</head>

<!-- 
    Esta página JSP permite asociar una actividad a un determinado campamento 
-->

<body>
    <!-- Incluye el módulo de logout -->
    <jsp:include page="/common/logout.jsp" />
    <br><br><br><br><br><br>

    <%
    // Verifica si el usuario tiene el rol de administrador
    if (userBean.getRole() == 1) {
    %>
        <h1>Asociar Actividad a Campamento</h1>

        <!-- Tabla para mostrar los campamentos y asociar actividades -->
        <table>
            <thead>
                <tr>
                    <th class="left-th" style="text-align: center">ID y Nivel del Campamento</th>
                    <th style="text-align: center">Fecha Inicio</th>
                    <th style="text-align: center">Fecha Finalización</th>
                    <th class="right-th" style="text-align: center">Asociar Actividad</th>
                </tr>
            </thead>
            <tbody>
                <%
                try {
                    // Carga las propiedades desde el archivo de configuración
                    String file = application.getInitParameter("sqlproperties");
                    java.io.InputStream myIO = application.getResourceAsStream(file);
                    java.util.Properties prop = new java.util.Properties();
                    prop.load(myIO);

                    // Inicializa los DAO necesarios
                    CampDAO campDAO = new CampDAO(prop);
                    ActivityDAO activityDAO = new ActivityDAO(prop);

                    // Obtiene la lista de campamentos y actividades
                    ArrayList<CampDTO> camps = campDAO.imprimirCamps();
                    ArrayList<ActivityDTO> activities = activityDAO.imprimirActividadNameAndLevel();

                    // Itera sobre cada campamento para mostrar sus datos
                    for (CampDTO camp : camps) {
                %>
                    <tr>
                        <td style="text-align: center"><%= camp.getID() %>, <%= camp.getLevelEducation() %></td>
                        <td style="text-align: center"><%= camp.getStartDate() %></td>
                        <td style="text-align: center"><%= camp.getEndDate() %></td>
                        <td style="text-align: center">
                            <div class="dropdown">
                                <span class="center triangle" data-tooltip-icon="▼">Asociar Actividad</span>
                                <div class="dropdown-content">
                                    <%
                                    // Itera sobre cada actividad y verifica si puede ser asociada al campamento
                                    for (ActivityDTO activity : activities) {
                                        if (!activityDAO.activitidadAsociadaACamp(camp.getID(), activity.getName(), activity.getLevelEducation())) {
                                            if (activity.getLevelEducation().equals(camp.getLevelEducation())) {
                                    %>
                                                <a href="<%= request.getContextPath() %>/AsociarActividadCamp?name=<%= activity.getName() %>&levelEducation=<%= activity.getLevelEducation() %>&idCamp=<%= camp.getID() %>">
                                                    <%= activity.getName() %>
                                                </a>
                                    <%
                                            } else {
                                                out.println("El nivel de educación no coincide: " + activity.getLevelEducation());
                                            }
                                        } else {
                                            out.println("La actividad ya está asociada al campamento: " + activity.getName());
                                        }
                                    }
                                    %>
                                </div>
                            </div>
                        </td>
                    </tr>
                <%
                    }
                } catch (Exception e) {
                    out.println("Error: " + e.getMessage());
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
