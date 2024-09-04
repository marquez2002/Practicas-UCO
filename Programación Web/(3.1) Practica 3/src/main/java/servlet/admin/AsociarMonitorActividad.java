package servlet.admin;

import java.io.IOException;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import business.common.LevelEducation;
import data.dao.ActivityDAO.ActivityDAO;

/**
 * Servlet implementation class AsociateMonitorToActivity
 * 
 * @author Antonio Jiménez Jiménez
 * @author Gonzalo Márquez de Torres
 * @author José María Muñoz López
 * @version 1.0
 */
//@WebServlet("/AsociateMonitorToActivity")
public class AsociarMonitorActividad extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
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
		String name = request.getParameter("name");
		LevelEducation levelEducation = LevelEducation.valueOf(request.getParameter("levelEducation"));
		int id = Integer.parseInt(request.getParameter("idMonitor"));
		ActivityDAO activityDAO=new ActivityDAO(prop);
		
		
		activityDAO.asociarMonitor(id, name, levelEducation);
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
