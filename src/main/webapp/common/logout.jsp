<jsp:useBean id="userBean" class="display.userbean.userBean"
	scope="session" />

<%
if(userBean.getRole()==0) {
	%>
	<header>
	<form class="edit" action="<%= request.getContextPath() %>/mvc/view/user/usermenu.jsp" method="post">
		<p>
			<input class="header-input edit left" type="submit" value="Atr&aacute;s">
		</p>
	</form>
	<form action="<%= request.getContextPath() %>/mvc/control/logoutControlador.jsp" method="post">
		<p>
			<input class="header-input edit" type="submit" value="Cerrar Sesi&oacute;n">
		</p>
	</form>
</header>
	<%
} else if(userBean.getRole()==1) {
	%>
	<header>
	<form class="edit" action="<%= request.getContextPath() %>/mvc/view/admin/adminmenu.jsp" method="post">
		<p>
			<input class="header-input edit left" type="submit" value="Atr&aacute;s">
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

