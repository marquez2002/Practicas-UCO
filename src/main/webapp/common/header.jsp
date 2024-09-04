<jsp:useBean id="userBean" class="display.userbean.userBean"
	scope="session" />

<%
if(userBean.getRole()==0) {
	%>
<header>
	<form class="edit" action="<%= request.getContextPath() %>/mvc/view/user/modifyuser.jsp" method="post">
		<p>
			<input class="header-input edit left" type="submit" value="Editar Datos Usuario">
		</p>
	</form>
	<form action="<%= request.getContextPath() %>/mvc/control/logoutControlador.jsp" method="post">
		<p>
			<input class="header-input edit" type="submit" value="Cerrar Sesi&oacute;n">
		</p>
	</form>
</header>
<%
} else {
	%>
	<header>
	<form class="edit" action="<%= request.getContextPath() %>/mvc/view/admin/modifyadmin.jsp" method="post">
		<p>
			<input class="header-input edit left" type="submit" value="Editar Datos Admin">
		</p>
	</form>
	<form action="<%= request.getContextPath() %>/mvc/control/logoutControlador.jsp" method="post">
		<p>
			<input class="header-input edit" type="submit" value="Cerrar Sesi&oacute;n">
		</p>
	</form>
</header>
	<%
}
%>
