<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ page import="display.userbean.userBean"%>
<%@ page import="servlet.admin.RegisterCamp"%>

<jsp:useBean id="userBean" class="display.userbean.userBean" scope="session" />

<!-- 
    Esta página JSP permite registrar un determinado campamento. 
-->

<!DOCTYPE html>
<html lang="es">
<head>
    <meta charset="UTF-8">
    <title>Registrar Campamento</title>
    <link rel="stylesheet" type="text/css" href="<%= request.getContextPath() %>/css/header.css">
    <link rel="stylesheet" type="text/css" href="<%= request.getContextPath() %>/css/common.css">
    <link rel="stylesheet" type="text/css" href="<%= request.getContextPath() %>/css/footer.css">
    <link rel="icon" type="image/png" href="<%= request.getContextPath() %>/images/campFire_favicon.png" sizes="16x16">
    <script src="../../../JS/RegisterCamp.js"></script>
</head>

<jsp:include page="/common/logout.jsp" />

<body>
    <% if (userBean.getRole() == 1) { %>
        <br><br><br><br><br><br>
        <h1>Registra un nuevo campamento</h1>

        <div>
            <form action="<%= request.getContextPath() %>/RegisterCamp" method="post" onsubmit="return validateForm()">
                <section>
                    <div class="align">
                        <label for="start">Fecha de inicio</label>
                        <input class="center" type="date" name="startDate" placeholder="yyyy-MM-dd">
                    </div>
                    <div class="align">
                        <label for="end">Fecha de finalización</label>
                        <input class="center" type="date" name="endDate" placeholder="yyyy-MM-dd">
                    </div>
                </section>

                <section>
                    <div class="align">
                        <label for="levelEducation">Nivel educativo</label>
                        <select class="center" name="levelEducation" id="level">
                            <option value="">...</option>
                            <option value="INFANTIL">Infantil</option>
                            <option value="JUVENIL">Juvenil</option>
                            <option value="ADOLESCENTE">Adolescente</option>
                        </select>
                    </div>
                    <div class="align">
                        <label for="maximunAsistent">Nº máximo de asistentes</label>
                        <input class="center" type="number" name="maximunAsistent" min="0" max="1000">
                    </div>
                </section>

                <div id="error-container" style="color: red;"></div> <!-- Contenedor para mensajes de error -->
                
                <h1><button type="submit">Aceptar</button></h1>
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
