<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ page import="display.userbean.userBean"%>
<%@ page import="servlet.admin.RegisterCamp"%>

<jsp:useBean id="userBean" class="display.userbean.userBean" scope="session" />

<!DOCTYPE html>
<html lang="es">
<head>
    <meta charset="UTF-8">
    <title>Registrar Actividad</title>
    <link rel="stylesheet" type="text/css" href="<%= request.getContextPath() %>/css/header.css">
    <link rel="stylesheet" type="text/css" href="<%= request.getContextPath() %>/css/common.css">
    <link rel="stylesheet" type="text/css" href="<%= request.getContextPath() %>/css/footer.css">
    <link rel="icon" type="image/png" href="<%= request.getContextPath() %>/images/campFire_favicon.png" sizes="16x16">
    <script src="../../../JS/RegisterActivity.js"></script>
</head>

<!-- 
    Esta página JSP permite registrar una determinada actividad. 
-->

<jsp:include page="/common/logout.jsp" />
<body>
    <br><br><br><br><br><br>
    <% if (userBean.getRole() == 1) { %>
        <h1>Registra una nueva actividad</h1>

        <div>
            <form action="<%= request.getContextPath() %>/RegisterActivity" method="post" onsubmit="return validateForm()">
                <section>
                    <div class="align">
                        <label for="name">Nombre</label>
                        <input class="center" type="text" name="name" placeholder="Actividad">
                    </div>
                </section>

                <section>
                    <div class="align">
                        <label for="timetable">Horario</label>
                        <select class="center" name="timetable" id="timetable">
                            <option value="">...</option>
                            <option value="MANANA">Mañana</option>
                            <option value="TARDE">Tarde</option>
                        </select>
                    </div>

                    <div class="align">
                        <label for="levelEducation">Nivel educativo</label>
                        <select class="center" name="levelEducation" id="levelEducation">
                            <option value="">...</option>
                            <option value="INFANTIL">Infantil</option>
                            <option value="JUVENIL">Juvenil</option>
                            <option value="ADOLESCENTE">Adolescente</option>
                        </select>
                    </div>
                </section>

                <section>
                    <div class="align">
                        <label for="asistents">Nº máximo de asistentes</label>
                        <input class="center" type="number" name="asistents" placeholder="0" min="0" max="1000">
                    </div>

                    <div class="align">
                        <label for="numberMonitor">Nº de monitores</label>
                        <input class="center" type="number" name="numberMonitor" placeholder="0" min="0" max="1000">
                    </div>
                </section>

                <div id="error-container" style="color: red;"></div> <!-- Contenedor para mensajes de error -->
                
                <h1><button>Aceptar</button></h1>
            </form>
        </div>
    <% } else { %>
        <%
            response.sendRedirect("../../../errorpage.html");
        %>
    <% } %>
</body>

<jsp:include page="/common/footer.jsp" />
</html>
