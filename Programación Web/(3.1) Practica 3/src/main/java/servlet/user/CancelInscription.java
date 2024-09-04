package servlet.user;

import java.io.IOException;
import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import data.dao.InscriptionDAO.InscriptionDAO;
import display.userbean.userBean;

/**
 * Servlet implementation class CancelInscription
 * Este servlet maneja la cancelación de inscripciones por parte de los usuarios.
 * 
 * @autor Antonio Jiménez Jiménez
 * @autor Gonzalo Márquez de Torres
 * @autor José María Muñoz López
 * @version 1.0
 */
public class CancelInscription extends HttpServlet {
    private static final long serialVersionUID = 1L;

    /**
     * Maneja las solicitudes POST, que se generan cuando el usuario desea cancelar una inscripción.
     * 
     * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
     */
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession();
        ServletContext application = session.getServletContext();
        
        userBean userBean = (userBean) session.getAttribute("userBean");

        // Verificar si el usuario no está autenticado o si tiene un rol que no permite la acción
        if (userBean == null || userBean.getEmail().isEmpty() || userBean.getRole() == 1) {
            response.sendRedirect("index.jsp");
            return;
        }

        // Obtener la ruta al archivo de propiedades SQL desde el contexto de la aplicación
        String sqlProperties = application.getInitParameter("sqlproperties"); 
        try (java.io.InputStream myIO = application.getResourceAsStream(sqlProperties)) {
            java.util.Properties prop = new java.util.Properties();
            prop.load(myIO);

            InscriptionDAO inscriptionDAO = new InscriptionDAO(prop);
            String idAsistent = request.getParameter("idAsistent");
            String idCamp = request.getParameter("idCamp");
            
            if (idAsistent != null && !idAsistent.isEmpty() && idCamp != null && !idCamp.isEmpty()) {                
                int idAsistentInt = Integer.parseInt(idAsistent);
                int idCampInt = Integer.parseInt(idCamp);
                               
                inscriptionDAO.eliminarInscriptionByAsistentAndIdCamp(idAsistentInt, idCampInt);
                
                request.setAttribute("mensaje", "Se ha cancelado con éxito la inscripción");
            } else {
                request.setAttribute("mensaje", "Error: Datos de inscripción no válidos.");
            }
        } catch (IOException e) {
            e.printStackTrace();
            request.setAttribute("mensaje", "Error al cargar las propiedades de la base de datos.");
        }

        // Redirigir al menú del usuario después de intentar cancelar la inscripción
        RequestDispatcher dispatcher = request.getRequestDispatcher("/mvc/view/user/usermenu.jsp");
        dispatcher.forward(request, response);
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
