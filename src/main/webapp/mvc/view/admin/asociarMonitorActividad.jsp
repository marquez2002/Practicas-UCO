<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ page import="display.userbean.userBean"%>
<%@ page import="data.dao.CampDAO.CampDAO"%>
<%@ page import="business.camp.CampDTO"%>
<%@ page import="data.dao.MonitorDAO.MonitorDAO"%>
<%@ page import="business.monitor.MonitorDTO"%>
<%@ page import="data.dao.ActivityDAO.ActivityDAO"%>
<%@ page import="business.activity.ActivityDTO"%>
<%@ page import="java.util.ArrayList"%>

<jsp:useBean id="userBean" scope="session" class="display.userbean.userBean"></jsp:useBean>

<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Asociar Monitor a Actividad</title>
    <link rel="stylesheet" type="text/css" href="<%= request.getContextPath() %>/css/header.css">
    <link rel="stylesheet" type="text/css" href="<%= request.getContextPath() %>/css/common.css">
    <link rel="stylesheet" type="text/css" href="<%= request.getContextPath() %>/css/footer.css">  
    <link rel="icon" type="image/png" href="<%= request.getContextPath() %>/images/campFire_favicon.png" sizes="16x16">
</head>

<!-- 
    Esta página JSP permite asociar un monitor a una determinada actividad 
-->

<body>

    <!-- Incluye el módulo de logout -->
    <jsp:include page="/common/logout.jsp" />
    
    <br><br><br><br><br><br>

    <%
    // Verifica si el usuario tiene el rol de administrador
    if (userBean.getRole() == 1) {
    %>
        <h1>Asociar Monitor a Actividad</h1>

        <!-- Tabla para mostrar las actividades y asociar monitores -->
        <table>
            <thead>
                <tr>
                    <th class="left-th" style="text-align: center">Nombre y Nivel de Actividad</th>
                    <th class="right-th" style="text-align: center">Asociar Monitor</th>
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
                    MonitorDAO monitorDAO = new MonitorDAO(prop);
                    ActivityDAO activityDAO = new ActivityDAO(prop);

                    // Obtiene la lista de monitores y actividades
                    ArrayList<MonitorDTO> monitores = monitorDAO.imprimirMonitores();
                    ArrayList<ActivityDTO> actividades = activityDAO.imprimirActividades();

                    // Itera sobre cada actividad para mostrar sus datos y asociar monitores
                    for (ActivityDTO actividad : actividades) {
                        int countMonitors = activityDAO.contarMonitores(actividad.getName(), actividad.getLevelEducation());
                        
                        if (countMonitors < actividad.getNumberMonitor()) {
                %>
                            <tr>
                                <td style="text-align: center"><%= actividad.getName() %>, <%= actividad.getLevelEducation() %></td>
                                <td style="text-align: center">
                                    <div class="dropdown">
                                        <span class="center triangle" data-tooltip-icon="▼">Asociar Monitor</span>
                                        <div class="dropdown-content">
                                            <%
                                            // Itera sobre cada monitor disponible para asociarlo a la actividad
                                            for (MonitorDTO monitor : monitores) {
                                                if (!monitorDAO.esMonitorAsociadaAActividad(monitor.getId(), actividad.getName(), actividad.getLevelEducation()) && !monitor.getSpecial()) {
                                            %>
                                                    <a href="<%= request.getContextPath() %>/AsociarMonitorActividad?idMonitor=<%= monitor.getId() %>&levelEducation=<%= actividad.getLevelEducation() %>&name=<%= actividad.getName() %>">
                                                        <%= monitor.getName() %>
                                                    </a>
                                            <%
                                                }
                                            }
                                            %>
                                        </div>
                                    </div>
                                </td>
                            </tr>
                <%
                        }
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
