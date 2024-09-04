package servlet.user;

import java.io.IOException;
import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import display.userbean.userBean;

/**
 * Servlet implementation class AcceptInscription
 * Este servlet maneja la aceptación de inscripciones por parte de los usuarios.
 * 
 * @autor Antonio Jiménez Jiménez
 * @autor Gonzalo Márquez de Torres
 * @autor José María Muñoz López
 * @version 1.0
 */
public class AcceptInscription extends HttpServlet {
    private static final long serialVersionUID = 1L;

    /**
     * Maneja las solicitudes POST, que se generan cuando el usuario acepta una inscripción.
     * 
     * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
     */
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession();
        userBean userBean = (userBean) session.getAttribute("userBean");

        // Verifica si el usuario no está autenticado o si tiene un rol que no permite la acción
        if (userBean == null || userBean.getEmail().isEmpty() || userBean.getRole() == 1) {
            response.sendRedirect("index.jsp");
            return; // Asegura que no se ejecute más código después de la redirección
        }

        // Obtener el contexto de la aplicación y cargar las propiedades SQL
        ServletContext application = session.getServletContext();
        String sqlProperties = application.getInitParameter("sqlproperties"); 

        java.util.Properties prop = new java.util.Properties();
        try (java.io.InputStream myIO = application.getResourceAsStream(sqlProperties)) {
            if (myIO == null) {
                throw new IOException("No se pudo cargar el archivo de propiedades: " + sqlProperties);
            }
            prop.load(myIO);
        } catch (IOException e) {
            e.printStackTrace();
            // Manejar el error de carga de propiedades, se puede redirigir a una página de error
            response.sendRedirect("errorpage.jsp");
            return; // Asegura que no se ejecute más código después de la redirección
        }

        // Si el usuario está autenticado y tiene el rol adecuado, redirigir a la página de aceptación de pago
        RequestDispatcher dispatcher = request.getRequestDispatcher("/mvc/view/user/acceptPay.jsp");
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
