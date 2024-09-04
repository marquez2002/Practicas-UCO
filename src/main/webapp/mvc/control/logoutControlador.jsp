<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ page import="display.userbean.userBean" %>
<jsp:useBean id="userBean" scope="session" class="display.userbean.userBean" />

<%
    // Página a la que se redirigirá tras el cierre de sesión
    String nextPage = "../../index.jsp"; 
    String msgNextPage = "Logout successful"; // Mensaje de éxito

    // Verifica si el objeto userBean no es nulo
    if (userBean != null) {
        // Elimina el bean de usuario de la sesión y cierra la sesión
        request.getSession().removeAttribute("userBean");
        request.getSession().invalidate();
    }
%>

<!-- Redirige a la página correspondiente con el mensaje -->
<jsp:forward page="<%=nextPage%>">
    <jsp:param name="message" value="<%=msgNextPage%>" />
</jsp:forward>
