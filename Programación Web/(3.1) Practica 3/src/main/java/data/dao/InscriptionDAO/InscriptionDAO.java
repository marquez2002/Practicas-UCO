package data.dao.InscriptionDAO;

import java.sql.Connection;
import java.sql.Date;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.sql.Timestamp;
import java.util.ArrayList;
import java.util.Properties;

import business.inscription.InscriptionDTO;
import business.inscription.TardiaInscriptionDTO;
import business.inscription.TempranaInscriptionDTO;
import data.dao.common.ConexionBD;

/**
 * Clase de InscriptionDAO para gestionar inscripciones.
 * 
 * @author Antonio Jiménez Jiménez
 * @author Gonzalo Márquez de Torres
 * @author José María Muñoz López
 * @since 05-11-2023
 * @version 1.0
 */
public class InscriptionDAO {

    private Connection connect;
    private Properties properties;

    /**
     * Constructor de la clase InscriptionDAO. Inicializa la clase y carga las propiedades SQL desde un archivo externo.
     */
    public InscriptionDAO(Properties properties_) {
        properties = properties_;
        ConexionBD connection = new ConexionBD();
        connect = connection.getConnection();
    }

    /**
     * Cuenta el número de inscripciones en un campamento específico.
     *
     * @param camp El ID del campamento del que se desea contar las inscripciones.
     * @return El número de inscripciones en el campamento dado.
     */
    public int contarInscriptionsCamp(int camp) {
        int count = 0;       
        String query = properties.getProperty("getInscriptionsCamp");
        
        try (PreparedStatement pstmt = connect.prepareStatement(query)) {
            pstmt.setInt(1, camp); 
            try (ResultSet rs = pstmt.executeQuery()) {
                if (rs.next()) {
                    count = rs.getInt(1); 
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return count;
    }

    /**
     * Registra una inscripción en la base de datos.
     *
     * @param inscription El objeto InscriptionDTO a registrar.
     * @return Un entero que representa el resultado del registro.
     */
    public int registrarInscription(InscriptionDTO inscription) {
        int res = 0;
        String query = properties.getProperty("registrarInscription");
        try (PreparedStatement ps = connect.prepareStatement(query)) {
            ps.setInt(1, inscription.getIdAsistent());
            ps.setInt(2, inscription.getIdCamp());
            ps.setTimestamp(3, new Timestamp(inscription.getInscriptionDate().getTime()));
            ps.setFloat(4, inscription.getPrice());
            ps.setBoolean(5, inscription.getCompletada());
            ps.setBoolean(6, inscription.getCancelada());

            res = ps.executeUpdate();
        } catch (SQLException e) {
            System.err.println("Error registering inscription: " + e.getMessage());
        }
        
        return res;
    }

    /**
     * Obtiene y devuelve todas las inscripciones almacenadas en la base de datos.
     *
     * @return Un ArrayList de objetos InscriptionDTO que representan todas las inscripciones almacenadas. 
     *         Devuelve una lista vacía si no hay inscripciones disponibles.
     */
    public ArrayList<InscriptionDTO> printInscriptions() {
        ArrayList<InscriptionDTO> inscriptions = new ArrayList<>();
        try (Statement stmt = connect.createStatement();
             ResultSet rs = stmt.executeQuery(properties.getProperty("imprimirInscriptions"))) {
            while (rs.next()) {
                InscriptionDTO inscription = crearInscriptionFromResultSet(rs);
                if (inscription != null) {
                    inscriptions.add(inscription);
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        
        return inscriptions;
    }

    /**
     * Crea una InscriptionDTO a partir de un ResultSet.
     * 
     * @param rs ResultSet con los datos de inscripción.
     * @return Un objeto InscriptionDTO correspondiente a los datos del ResultSet.
     */
    private InscriptionDTO crearInscriptionFromResultSet(ResultSet rs) throws SQLException {
        int p_id = rs.getInt("idAsistent");
        int c_id = rs.getInt("idCamp");
        Timestamp formatted = rs.getTimestamp("inscriptionDate");
        Date date = new Date(formatted.getTime());
        Float price = rs.getFloat("price");
        Boolean complete = rs.getBoolean("completada_");
        Boolean cancelada_ = rs.getBoolean("cancelada_");

        if (cancelada_) {
            TempranaInscriptionDTO ins = new TempranaInscriptionDTO();
            return complete ? ins.RegistrationCompleta(p_id, c_id, date, price, complete)
                           : ins.RegistrationParcial(p_id, c_id, date, price, complete);
        } else {
            TardiaInscriptionDTO ins = new TardiaInscriptionDTO();
            return complete ? ins.RegistrationCompleta(p_id, c_id, date, price, complete)
                           : ins.RegistrationParcial(p_id, c_id, date, price, complete);
        }
    }

    /**
     * Obtiene una lista de inscripciones de un participante según su ID.
     *
     * @param idAsistent El ID del asistente del que se desean obtener las inscripciones.
     * @return Una lista de objetos InscriptionDTO que representan las inscripciones del asistente.
     */
    public ArrayList<InscriptionDTO> getAsistentInscriptionsById(int idAsistent) {
        ArrayList<InscriptionDTO> inscriptionsAsistent = new ArrayList<>();

        // Utilizar PreparedStatement en lugar de Statement para prevenir inyecciones SQL.
        String query = properties.getProperty("InscriptionByID");

        try (PreparedStatement pstmt = connect.prepareStatement(query)) {
            // Asignar el valor del parámetro al PreparedStatement
            pstmt.setInt(1, idAsistent);

            // Ejecutar la consulta
            try (ResultSet rs = pstmt.executeQuery()) {
                // Recorrer los resultados y crear InscriptionDTO
                while (rs.next()) {
                    InscriptionDTO inscription = crearInscriptionFromResultSet(rs);
                    if (inscription != null) {
                        inscriptionsAsistent.add(inscription); 
                    }
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return inscriptionsAsistent;
    }


    /**
     * Elimina una inscripción basada en el ID del participante y el ID del campamento.
     *
     * @param idAsistent El ID del participante.
     * @param idCamp     El ID del campamento.
     * @return true si se elimina con éxito la inscripción, de lo contrario false.
     */
    public boolean eliminarInscriptionByAsistentAndIdCamp(int idAsistent, int idCamp) {
        boolean deleted = false;

        try (PreparedStatement stmt = connect.prepareStatement(properties.getProperty("eliminarInscription"))) {
            stmt.setInt(1, idAsistent);
            stmt.setInt(2, idCamp);

            int rowsAffected = stmt.executeUpdate();
            deleted = (rowsAffected > 0);
        } catch (SQLException e) {
            e.printStackTrace();
        }
        
        return deleted;
    }

    /**
     * Calcula el precio total de una inscripción completa basado en el número de actividades y el tipo de inscripción.
     *
     * @param numActivities   El número de actividades seleccionadas.
     * @param inscriptionType El tipo de inscripción (COMPLETA o PARCIAL).
     * @return El precio total de la inscripción completa.
     */
    public int calcularPrecioCompleto(int numActivities, String inscriptionType) {
        if ("COMPLETA".equals(inscriptionType)) {
            int initialCost = 300;
            return numActivities * 20 + initialCost;
        }
        return 0; // Precio cero si no es una inscripción completa
    }

    /**
     * Calcula el precio de una inscripción parcial basado en el número de actividades y el tipo de inscripción.
     *
     * @param numActivities   El número de actividades seleccionadas.
     * @param inscriptionType El tipo de inscripción (COMPLETA o PARCIAL).
     * @return El precio de la inscripción parcial.
     */
    public int calcularPrecioParcial(int numActivities, String inscriptionType) {
        if ("PARCIAL".equals(inscriptionType)) {
            int initialCost = 100;
            return numActivities * 20 + initialCost;
        }
        return 0; // Precio cero si no es una inscripción parcial
    }

    /**
     * Obtiene una lista de IDs de los asistentes en un campamento específico.
     *
     * @param idCamp El ID del campamento del que se desean obtener los asistentes.
     * @return Una lista de IDs de los asistentes en el campamento.
     */
    public ArrayList<Integer> getAsistentsEnCamp(int idCamp) {
        ArrayList<Integer> asistents = new ArrayList<>();
        String query = properties.getProperty("getAsistentsEnCamp");

        try (PreparedStatement pstmt = connect.prepareStatement(query)) {
            pstmt.setInt(1, idCamp); 
            
            try (ResultSet rs = pstmt.executeQuery()) {
                while (rs.next()) {
                    int id = rs.getInt("idAsistent");
                    asistents.add(id); 
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }        
        return asistents; 
    }

}
