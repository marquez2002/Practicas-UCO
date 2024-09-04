package servlet.admin;

import java.io.IOException;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import data.dao.MonitorDAO.MonitorDAO;
import business.monitor.MonitorDTO;
import display.userbean.userBean;

/**
 * Servlet implementation class RegisterMonitor
 * 
 * @author Antonio Jiménez Jiménez
 * @author Gonzalo Márquez de Torres
 * @author José María Muñoz López
 * @version 1.0
 */
public class RegisterMonitor extends HttpServlet {
	private static final long serialVersionUID = 1L;
       	
	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
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
		
		// Caso 2: Usuario logueado, creamos monitor
		else {
		    String name = request.getParameter("name");
		    String surname = request.getParameter("surname");
		    String specialParam = request.getParameter("special"); 
	        boolean special = Boolean.parseBoolean(specialParam);


		    // Caso 2a: Si no hay parámetros en el request -> A la vista
		    if (name == null || surname == null) {
		        dispatcher = request.getRequestDispatcher("/mvc/view/admin/registermonitor.jsp");
		        dispatcher.forward(request, response);
		    
		    // Caso 2b: Hay parámetros en el request (viene de la vista)
		    } else {
		        MonitorDAO monitorDAO = new MonitorDAO(prop);
		        MonitorDTO monitor = new MonitorDTO();
		        
		        monitor.setName(name);
		        monitor.setSurname(surname);
		        monitor.setSpecial(special);
		        int result = monitorDAO.registrarMonitor(monitor); 
		        
		        if (result > 0) {
		            request.setAttribute("mensaje", "Se ha creado con &eacute;xito el monitor");
		        } else {
		            request.setAttribute("mensaje", "Error al crear el monitor");
		        }
		        
		        dispatcher = request.getRequestDispatcher("/mvc/view/admin/adminmenu.jsp");
		        dispatcher.forward(request, response);
		    }
		}
	
	}
	
	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		doPost(request,response);
	}
}
