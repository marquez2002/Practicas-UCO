package servlet.user;

import java.io.IOException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import business.camp.CampDTO;
import data.dao.CampDAO.CampDAO;
import display.userbean.userBean;

/**
 * Servlet implementation class listarCampDisponible
 * Este servlet maneja la búsqueda de campamentos disponibles entre dos fechas.
 * 
 * @autor Antonio Jiménez Jiménez
 * @autor Gonzalo Márquez de Torres
 * @autor José María Muñoz López
 * @version 1.0
 */
public class listarCampDisponible extends HttpServlet {
    private static final long serialVersionUID = 1L;

    /**
     * Maneja las solicitudes POST para listar campamentos disponibles.
     *
     * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
     */
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
    	HttpSession session = request.getSession();
        ServletContext application = session.getServletContext();
        userBean userBean = (userBean) session.getAttribute("userBean");

      //Obtenemos el valor del parametro sqlproperties, es decir, la ruta relativa al fichero sql.properties
        String sqlProperties = application.getInitParameter("sqlproperties");
        java.io.InputStream myIO = application.getResourceAsStream(sqlProperties);
        java.util.Properties prop = new java.util.Properties();
        prop.load(myIO);

        CampDAO campDAO = new CampDAO(prop);
        ArrayList<CampDTO> array = campDAO.imprimirCamps();

      //Caso 1: Usuario no esta logueado -> Volvemos al index
        if (userBean == null || userBean.getEmail().equals("") || userBean.getRole() == 1) {
            response.sendRedirect("index.jsp");
        //Caso 2: Obtenemos campamentos disponibles
        } else {
        	String date1String = request.getParameter("startDate");
            String date2String = request.getParameter("endDate");

            SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd");
            Date date1 = null;
            Date date2 = null;

            try {
                date1 = dateFormat.parse(date1String);
                date2 = dateFormat.parse(date2String);
            } catch (ParseException e) {
                e.printStackTrace();
            }

            ArrayList<CampDTO> campsInRange = new ArrayList<>();

            for (CampDTO camp : array) {
                Date campStartDate = camp.getStartDate();

                if (campStartDate.after(date1) && campStartDate.before(date2)) {
                    campsInRange.add(camp);
                }
            }

            
            request.setAttribute("campsInRange", campsInRange);

            RequestDispatcher dispatcher = request.getRequestDispatcher("/mvc/view/user/listavailablecamps.jsp");
            dispatcher.forward(request, response);
        }
    }



    /**
     * Maneja las solicitudes GET redirigiéndolas a doPost.
     *
     * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
     */
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doPost(request, response);
    }
}
