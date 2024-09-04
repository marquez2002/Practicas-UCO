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
import business.common.Timetable;
import business.activity.ActivityDTO;
import data.dao.ActivityDAO.ActivityDAO;
import display.userbean.userBean;

/**
 * Servlet implementation class RegisterActivity
 * 
 * @author Antonio Jiménez Jiménez
 * @author Gonzalo Márquez de Torres
 * @author José María Muñoz López
 * @version 1.0
 */
//@WebServlet("/RegisterActivity")
public class RegisterActivity extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		RequestDispatcher dispatcher;
		HttpSession session = request.getSession();
		ServletContext application = session.getServletContext();
		userBean userBean = (userBean) session.getAttribute("userBean");
		
		//Obtenemos el valor del parametro sqlproperties, es decir, la ruta relativa al fichero sql.properties
		String sqlProperties= application.getInitParameter("sqlproperties"); 
		java.io.InputStream myIO = application.getResourceAsStream(sqlProperties);
		java.util.Properties prop = new java.util.Properties();
		prop.load(myIO);
		
		//Caso 1: Usuario no esta logueado -> Volvemos al index
		if (userBean == null || userBean.getEmail().equals("") || userBean.getRole() == 0)
		{
			response.sendRedirect("index.jsp");
		}
		
		//Caso 2: Usuario logueado, creamos actividad
		else
		{
			String name = request.getParameter("name");
			Timetable timetable = Timetable.valueOf(request.getParameter("timetable"));
			LevelEducation levelEducation = LevelEducation.valueOf(request.getParameter("levelEducation"));
			int asistents = Integer.parseInt(request.getParameter("asistents"));
			int numberMonitor = Integer.parseInt(request.getParameter("numberMonitor"));
			
			//Caso 2a: Si no hay parametros en el request -> A la vista
			if (name == null ) {				
				dispatcher = request.getRequestDispatcher("/mvc/view/admin/registermonitor.jsp");
				dispatcher.forward(request, response);
			
			//Caso 2b: Hay parametros en el request (viene de la vista)
			} else {
				ActivityDAO activityDAO= new ActivityDAO(prop);
				ActivityDTO activity = new ActivityDTO();
				
				activity.setName(name);
				activity.setLevelEducation(levelEducation);
				activity.setTimetable(timetable);
				activity.setNumberMonitor(numberMonitor);
				activity.setAsistents(asistents);
				activityDAO.registrarActividad(activity);
				
				
				request.setAttribute("mensaje", "Se ha creado con &eacute;xito la actividad");
				dispatcher = request.getRequestDispatcher("/mvc/view/admin/adminmenu.jsp");
				dispatcher.forward(request, response);
			}
		}	
	}	
	
	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		response.getWriter().append("Served at: ").append(request.getContextPath());
	}
}
