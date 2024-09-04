<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ page import="display.userbean.userBean"%>
<%@ page import="data.dao.CampDAO.CampDAO"%>
<%@ page import="business.camp.CampDTO"%>
<%@ page import="data.dao.MonitorDAO.MonitorDAO"%>
<%@ page import="business.monitor.MonitorDTO"%>
<%@ page import="data.dao.InscriptionDAO.InscriptionDAO"%>
<%@ page import="data.dao.AsistentDAO.AsistentDAO"%>
<%@ page import="business.activity.ActivityDTO"%>
<%@ page import="data.dao.ActivityDAO.ActivityDAO"%>
<%@ page import="java.util.ArrayList"%>

<jsp:useBean id="userBean" scope="session" class="display.userbean.userBean"></jsp:useBean>

<!--
    Esta página JSP permite al administrador asociar monitores a campamentos.
-->

<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Asociar Monitor a Campamento</title>
    <link rel="stylesheet" type="text/css" href="<%= request.getContextPath() %>/css/header.css">
    <link rel="stylesheet" type="text/css" href="<%= request.getContextPath() %>/css/common.css">
    <link rel="stylesheet" type="text/css" href="<%= request.getContextPath() %>/css/footer.css">
    <link rel="icon" type="image/png" href="<%= request.getContextPath() %>/images/campFire_favicon.png" sizes="16x16">   
</head>

<jsp:include page="/common/logout.jsp" />
<body>
    <br><br><br><br><br><br>

    <%
    // Verifica si el usuario tiene el rol de administrador
    if (userBean.getRole() == 1) {
    %>
        <h1>Asociar Monitor a Campamento</h1>

        <table>
            <thead>
                <tr>
                    <th class="left-th" style="text-align: center">ID y Nivel del Campamento</th>
                    <th style="text-align: center">Asociar Monitor</th>
                    <th class="right-th" style="text-align: center">Asociar Monitor Especial</th>
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
                InscriptionDAO inscriptionDAO = new InscriptionDAO(prop);
                AsistentDAO asistentDAO = new AsistentDAO(prop);
                CampDAO campDAO = new CampDAO(prop);
                MonitorDAO monitorDAO = new MonitorDAO(prop);

                // Obtiene la lista de campamentos y monitores
                ArrayList<CampDTO> campamentos = campDAO.imprimirCamps();
                ArrayList<MonitorDTO> monitores = monitorDAO.imprimirMonitores();

                // Itera sobre cada campamento para mostrar sus datos y asociar monitores
                for (CampDTO campamento : campamentos) {
                    boolean hayAsistenteEspecial = false;

                    // Verifica si hay asistentes especiales en el campamento
                    ArrayList<Integer> asistentes = inscriptionDAO.getAsistentsEnCamp(campamento.getID());
                    for (Integer asistente : asistentes) {
                        if (asistentDAO.esAsistentSpecial(asistente)) {
                            hayAsistenteEspecial = true;
                            break;
                        }
                    }

                %>
                    <tr>
                        <td style="text-align: center"><%= campamento.getID() %>, <%= campamento.getLevelEducation() %></td>
                        <td style="text-align: center">
                            <div class="dropdown">
                                <span class="center triangle" data-tooltip-icon="▼">Asociar Monitor</span>
                                <div class="dropdown-content">
                                    <%
                                    // Itera sobre cada monitor disponible para asociarlo al campamento
                                    for (MonitorDTO monitor : monitores) {
                                        ArrayList<ActivityDTO> actividades = campDAO.getActivitiesEnCamp2(campamento.getID());
                                        for (ActivityDTO actividad : actividades) {
                                            if (monitorDAO.esMonitorAsociadaAActividad(monitor.getId(), actividad.getName(), actividad.getLevelEducation()) &&
                                                !monitor.getSpecial() && campamento.getMonitor() != monitor.getId()) {
                                    %>
                                                <a href="<%= request.getContextPath() %>/AsociarMonitorCampamento?idMonitor=<%= monitor.getId() %>&id=<%= campamento.getID() %>&special=0">
                                               	<%= monitor.getName() %>
                                                </a>
                                    <%
                                            }
                                        }
                                    }
                                    %>
                                </div>
                            </div>
                        </td>
                        <td style="text-align: center">
                            <%
                            if (!hayAsistenteEspecial) {
                            %>
                                <span class="tooltip" data-tooltip="No hay ningún monitor especial en ninguna actividad de este campamento, no puedes asociar ninguno a este campamento" data-tooltip-icon="ℹ️">
                                    No disponible
                                </span>
                            <%
                            } else {
                            %>
                                <div class="dropdown">
                                    <span class="center triangle" data-tooltip-icon="▼">Asociar Monitor Especial</span>
                                    <div class="dropdown-content">
                                        <%
                                        // Itera sobre cada monitor especial disponible para asociarlo al campamento
                                        for (MonitorDTO monitor : monitores) {
                                            if (monitor.getSpecial() && campamento.getSpecialMonitor() != monitor.getId()) {
                                        %>
                                                <a href="<%= request.getContextPath() %>/AsociarMonitorCampamento?idMonitor=<%= monitor.getId() %>&id=<%= campamento.getID() %>&special=1">
                                                    <%= monitor.getName() %>
                                                </a>
                                        <%
                                            }
                                        }
                                        %>
                                    </div>
                                </div>
                            <%
                            }
                            %>
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
