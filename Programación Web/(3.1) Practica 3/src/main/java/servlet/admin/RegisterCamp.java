package servlet.admin;

import java.io.IOException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import data.dao.CampDAO.CampDAO;
import business.camp.CampDTO;
import business.common.LevelEducation;
import display.userbean.userBean;

/**
 * Servlet implementation class RegisterCamp
 * 
 * @author Antonio Jiménez Jiménez
 * @author Gonzalo Márquez de Torres
 * @author José María Muñoz López
 * @version 1.0
 */
public class RegisterCamp extends HttpServlet {
	private static final long serialVersionUID = 1L;
       	
	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
	    RequestDispatcher dispatcher;
	    HttpSession session = request.getSession();
	    ServletContext application = session.getServletContext();
	    userBean userBean = (userBean) session.getAttribute("userBean");
	
	    String sqlProperties = application.getInitParameter("sqlproperties");
	    java.io.InputStream myIO = application.getResourceAsStream(sqlProperties);
	    java.util.Properties prop = new java.util.Properties();
	    prop.load(myIO);
	
	    CampDAO campDAO = new CampDAO(prop);
	
	    // Caso 1: Usuario no está logueado -> Volvemos al index
	    if (userBean == null || userBean.getEmail().equals("") || userBean.getRole() == 0) {
	        response.sendRedirect("index.jsp");
	    } else {
	        String startDateString = request.getParameter("startDate");
	        String endDateString = request.getParameter("endDate");
	        
	        // Validamos que los parámetros de fecha no sean nulos o vacíos
	        if (startDateString == null || startDateString.isEmpty() || endDateString == null || endDateString.isEmpty()) {	            
	            request.setAttribute("error", "Las fechas de inicio y fin son obligatorias.");
	            dispatcher = request.getRequestDispatcher("/mvc/view/admin/registercamp.jsp");
	            dispatcher.forward(request, response);
	            return; // Detenemos la ejecución para evitar errores adicionales
	        }
	
	        SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd");
	        Date startDate = null;
	        Date endDate = null;
	
	        try {
	            startDate = dateFormat.parse(startDateString);
	            endDate = dateFormat.parse(endDateString);
	        } catch (ParseException e) {
	            e.printStackTrace(); 
	            request.setAttribute("error", "Formato de fecha inválido.");
	            dispatcher = request.getRequestDispatcher("/mvc/view/admin/registercamp.jsp");
	            dispatcher.forward(request, response);
	            return; // Detenemos la ejecución si hay un error de formato de fecha
	        }
	
	        String StringLevel = request.getParameter("levelEducation");
	        if (StringLevel == null) {
	            dispatcher = request.getRequestDispatcher("/mvc/view/admin/registercamp.jsp");
	            dispatcher.forward(request, response);
	        } else {
	            LevelEducation level = LevelEducation.valueOf(StringLevel);
	            String StringmaximunAsistent = request.getParameter("maximunAsistent");
	            int maximunAsistent = Integer.parseInt(StringmaximunAsistent);
	
	            CampDTO camp = new CampDTO();
	            camp.setStartDate(startDate);
	            camp.setEndDate(endDate);
	            camp.setLevelEducation(level);
	            camp.setMaximunAsistent(maximunAsistent);
	            campDAO.registrarCamp(camp);
	
	            request.setAttribute("mensaje", "Se ha creado con &eacute;xito el campamento");
	            dispatcher = request.getRequestDispatcher("/mvc/view/admin/adminmenu.jsp");
	            dispatcher.forward(request, response);
	        }
	    }   
	}
	
	
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		doPost(request,response);
	}
}