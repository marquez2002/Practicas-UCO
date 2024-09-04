package servlet.user;

import java.io.IOException;
import java.util.Date;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import business.camp.CampDTO;
import business.inscription.CompletaInscriptionDTO;
import business.inscription.InscriptionDTO;
import business.inscription.ParcialInscriptionDTO;
import data.dao.CampDAO.CampDAO;
import data.dao.InscriptionDAO.InscriptionDAO;
import display.userbean.userBean;

/**
 * Servlet que maneja la inscripción de usuarios en campamentos.
 * Implementa la lógica para registrar inscripciones completas o parciales 
 * según los datos proporcionados por el usuario.
 * 
 * @autor Antonio Jiménez Jiménez
 * @autor Gonzalo Márquez de Torres
 * @autor José María Muñoz López
 * @version 1.0
 */
public class RegisterInscription extends HttpServlet {
    private static final long serialVersionUID = 1L;

    /**
     * Maneja las solicitudes POST para registrar una inscripción.
     * 
     * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
     */
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        RequestDispatcher dispatcher;
        HttpSession session = request.getSession();
        ServletContext application = session.getServletContext();
        userBean userBean = (userBean) session.getAttribute("userBean");		

        // Verificar si el usuario está logueado
        if (userBean == null || userBean.getEmail().isEmpty() || userBean.getRole() == 1) {
            response.sendRedirect("index.jsp");
            return; 
        }

        // Obtener propiedades SQL
        String sqlProperties = application.getInitParameter("sqlproperties"); 
        try (java.io.InputStream myIO = application.getResourceAsStream(sqlProperties)) {
            java.util.Properties prop = new java.util.Properties();
            prop.load(myIO);
            InscriptionDAO inscriptionDAO = new InscriptionDAO(prop);

            // Obtener parámetros del request
            String StringidAsistent = request.getParameter("idAsistent");
            String StringidCamp = request.getParameter("idCamp");

            // Validar los parámetros
            if (StringidAsistent == null || StringidCamp == null) {                
                dispatcher = request.getRequestDispatcher("/mvc/view/user/acceptPay.jsp");
                dispatcher.forward(request, response);
                return; 
            }

            int idAsistent = Integer.parseInt(StringidAsistent);
            int idCamp = Integer.parseInt(StringidCamp);
            Date currentDate = new Date();

            // Obtener información de la inscripción
            boolean completada = Boolean.parseBoolean(request.getParameter("completada_"));
            boolean cancelada = Boolean.parseBoolean(request.getParameter("cancelada_"));
            
            float price = 1;
            CampDAO campDAO = new CampDAO(prop);
            CampDTO camp = campDAO.getCamp(idCamp);
            if (camp == null) {
                request.setAttribute("errorMessage", "El campamento no existe.");
                dispatcher = request.getRequestDispatcher("/mvc/view/user/acceptPay.jsp");
                dispatcher.forward(request, response);
                return;
            }
            
            InscriptionDTO inscription;
            if (completada) {
                inscription = new CompletaInscriptionDTO();
                price = inscriptionDAO.calcularPrecioCompleto(campDAO.contarActividadesCamp(idCamp), "COMPLETA");
                
            } else {
                inscription = new ParcialInscriptionDTO();
                price = inscriptionDAO.calcularPrecioParcial(campDAO.contarActividadesCamp(idCamp), "PARCIAL");
            }

            // Establecer atributos de la inscripción
            inscription.setIdAsistent(idAsistent);
            inscription.setIdCamp(idCamp);
            inscription.setInscriptionDate(currentDate);
            inscription.setPrice(price);
            inscription.setCompletada(completada);
            inscription.setCancelada(cancelada);

            // Registrar inscripción
            inscriptionDAO.registrarInscription(inscription);
            request.setAttribute("mensaje", "Se ha creado con &eacute;xito la inscripción");

            // Redirigir a la página de menú del usuario
            dispatcher = request.getRequestDispatcher("/mvc/view/user/usermenu.jsp");
            dispatcher.forward(request, response);
        } catch (IOException e) {
            e.printStackTrace();
            request.setAttribute("errorMessage", "Error al cargar las propiedades de la base de datos.");
            dispatcher = request.getRequestDispatcher("/mvc/view/user/acceptPay.jsp");
            dispatcher.forward(request, response);
        } catch (NumberFormatException e) {
            e.printStackTrace();
            request.setAttribute("errorMessage", "Error en los parámetros de inscripción. Asegúrese de que los valores son válidos.");
            dispatcher = request.getRequestDispatcher("/mvc/view/user/acceptPay.jsp");
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
