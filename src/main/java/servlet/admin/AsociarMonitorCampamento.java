package servlet.admin;

import java.io.IOException;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import data.dao.CampDAO.CampDAO;

/**
 * Servlet implementation class AssociateMonitorToCamp
 * 
 * @author Antonio Jiménez Jiménez
 * @author Gonzalo Márquez de Torres
 * @author José María Muñoz López
 * @version 1.0
 */
//@WebServlet("/AssociateMonitorToCamp")
public class AsociarMonitorCampamento extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public AsociarMonitorCampamento() {
        super();
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		RequestDispatcher dispatcher;
		HttpSession session = request.getSession();
		ServletContext application = session.getServletContext();
		String sqlProperties= application.getInitParameter("sqlproperties"); 
		java.io.InputStream myIO = application.getResourceAsStream(sqlProperties);
		java.util.Properties prop = new java.util.Properties();
		prop.load(myIO);
		
		int id = Integer.parseInt(request.getParameter("id"));
		int idMonitor = Integer.parseInt(request.getParameter("idMonitor"));
		int special = Integer.parseInt(request.getParameter("special"));
		CampDAO campDAO=new CampDAO(prop);
		
		
		if(special==1){
			campDAO.asociarSpecialMonitor(idMonitor, id);
		}else {
			campDAO.asociarMonitor(idMonitor, id);
		}
		request.setAttribute("mensaje", "Se ha creado con &eacute;xito la actividad");
		dispatcher = request.getRequestDispatcher("/mvc/view/admin/adminmenu.jsp");
		dispatcher.forward(request, response);
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		doGet(request, response);
	}

}
