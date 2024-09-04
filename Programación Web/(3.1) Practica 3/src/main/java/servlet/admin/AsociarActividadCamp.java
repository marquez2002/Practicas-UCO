package servlet.admin;

import java.io.IOException;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import business.activity.ActivityDTO;
import business.common.LevelEducation;
import data.dao.CampDAO.CampDAO;

/**
 * Servlet implementation class AsociateaActivityToCamp
 * 
 * @author Antonio Jiménez Jiménez
 * @author Gonzalo Márquez de Torres
 * @author José María Muñoz López
 * @version 1.0
 */
//@WebServlet("/AsociateaActivityToCamp")

public class AsociarActividadCamp extends HttpServlet {
	private static final long serialVersionUID = 1L;      

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		RequestDispatcher dispatcher;
		HttpSession session = request.getSession();
		ServletContext application = session.getServletContext();
		String sqlProperties= application.getInitParameter("sqlproperties"); 
		java.io.InputStream myIO = application.getResourceAsStream(sqlProperties);
		java.util.Properties prop = new java.util.Properties();
		prop.load(myIO);
		ActivityDTO activityDTO=new ActivityDTO();
		String name = request.getParameter("name");
		LevelEducation levelEducation =LevelEducation.valueOf( request.getParameter("levelEducation"));
		int id = Integer.parseInt(request.getParameter("idCamp"));
		CampDAO camp=new CampDAO(prop);
		activityDTO.setLevelEducation(levelEducation);
		activityDTO.setName(name);
		
		camp.asociarActividad(activityDTO,id);
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
