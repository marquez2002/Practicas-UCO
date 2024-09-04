package data.dao.AsistentDAO;

import java.sql.*;
import java.util.Properties;

import data.dao.common.ConexionBD;
import business.asistent.*; 

/**
 * Clase que define un Data Access Object (DAO) para gestionar asistentes.
 * 
 * @autor Antonio Jiménez Jiménez
 * @autor Gonzalo Márquez de Torres
 * @autor José María Muñoz López
 * @version 1.0
 */
public class AsistentDAO {

    private Connection connect;
    private Properties properties;

    /**
     * Inicializa una nueva instancia de la clase AsistentDAO, cargando la configuración desde el properties.
     * Este archivo se utiliza para definir consultas SQL y otros parámetros de configuración.
     *
     * @param properties_ Propiedades de configuración para la conexión a la base de datos.
     */
    public AsistentDAO(Properties properties_) {
        properties = properties_; 
        if (connect == null) {
            ConexionBD connection = new ConexionBD(); 
            connect = connection.getConnection(); 
        }
    }

    /**
     * Recupera un objeto AsistentDTO basado en la dirección de correo electrónico proporcionada.
     * Si no se encuentra ningún asistente con la dirección de correo electrónico dada, se devuelve un objeto AsistentDTO vacío.
     *
     * @param email La dirección de correo electrónico del asistente a buscar.
     * @return Un objeto AsistentDTO que representa al asistente correspondiente a la dirección de correo electrónico proporcionada, o un objeto vacío si no se encuentra ningún asistente.
     */
    public AsistentDTO getAsistentConEmail(String email) {
        AsistentDTO asistent = null; 
        String sql = properties.getProperty("getAsistentConEmail");

        try (PreparedStatement ps = connect.prepareStatement(sql)) {
            ps.setString(1, email); 
            ResultSet rs = ps.executeQuery(); 
            if (rs.next()) { 
                asistent = new AsistentDTO(); 
                asistent.setID(rs.getInt("id"));
                asistent.setName(rs.getString("name"));
                asistent.setSurname(rs.getString("surname"));
                asistent.setEmail(rs.getString("email"));
                asistent.setPassword(rs.getString("password"));
                asistent.setRole(rs.getInt("role"));
                asistent.setDate(new Date(rs.getTimestamp("date").getTime())); 
                asistent.setEspecial(rs.getBoolean("special"));
            }
        } catch (SQLException e) {
            e.printStackTrace(); 
        } catch (IllegalArgumentException e) {
            e.printStackTrace(); 
        }
        
        return asistent; 
    }

    /**
     * Verifica la existencia de un asistente en la base de datos utilizando su correo electrónico y contraseña.
     *
     * @param email    La dirección de correo electrónico del asistente.
     * @param password La contraseña del asistente.
     * @return Devuelve verdadero si el asistente existe en la base de datos; de lo contrario, falso.
     */
    public Boolean esAsistentExiste(String email, String password) {
        boolean exists = false; 
        String sql = properties.getProperty("getAsistentConEmail") + " AND password = ?";

        try (PreparedStatement ps = connect.prepareStatement(sql)) {
            ps.setString(1, email); 
            ps.setString(2, password);
            ResultSet rs = ps.executeQuery(); 
            exists = rs.next(); 
        } catch (SQLException e) {
            e.printStackTrace(); 
        } catch (IllegalArgumentException e) {
            e.printStackTrace(); 
        }     
        return exists; 
    }


    /**
     * Verifica si un asistente está registrado en el sistema utilizando su dirección de correo electrónico.
     *
     * @param email La dirección de correo electrónico del asistente a verificar.
     * @return true si el asistente está registrado en el sistema, de lo contrario false.
     */
    public Boolean esAsistentRegistrado(String email) {
   	    if (email == null || email.isEmpty()) {
   	        return false; 
   	    }

   	    // Variable para almacenar el resultado
   	    boolean isRegistered = false;
   	    String query = properties.getProperty("existeEmail");
   	    try (PreparedStatement pstmt = connect.prepareStatement(query)) {
   	        pstmt.setString(1, email);
   	        
   	        try (ResultSet rs = pstmt.executeQuery()) {
   	            isRegistered = rs.next(); 
   	        }
   	    } catch (SQLException e) {
   	        e.printStackTrace();
   	    } catch (IllegalArgumentException e) {
   	        e.printStackTrace();
   	    }
    	    return isRegistered; 
   	}



    /**
     * Verifica si un asistente tiene un estado especial identificado por un ID específico.
     *
     * @param id El ID del estado especial del asistente a verificar.
     * @return true si el asistente tiene un estado especial identificado por el ID proporcionado, de lo contrario false.
     */
    public Boolean esAsistentSpecial(int id) {
        boolean special = false;
        String query = properties.getProperty("isSpecial");

        try (PreparedStatement pstmt = connect.prepareStatement(query)) {
            pstmt.setInt(1, id);

            try (ResultSet rs = pstmt.executeQuery()) {
                if (rs.next()) {
                    special = rs.getBoolean("special");
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return special;
    }


    /**
     * Registra un nuevo asistente en la base de datos.
     *
     * @param name     El nombre del asistente.
     * @param surname  El apellido del asistente.
     * @param email    La dirección de correo electrónico del asistente.
     * @param password La contraseña del asistente.
     * @param role     El rol del asistente.
     * @param date     La fecha asociada al asistente.
     * @param special  Indica si el asistente tiene atención especial.
     * @return Un entero que representa el estado del registro.
     */
    public int registrarAsistent(String name, String surname, String email, String password, int role, String date, Boolean special) { 
        int status = 0; 
        try {
            int specialInt = special ? 1 : 0; 
            PreparedStatement ps = connect.prepareStatement(properties.getProperty("registrarAsistent"));
            ps.setString(1, name);
            ps.setString(2, surname);
            ps.setString(3, email);
            ps.setString(4, password);
            ps.setInt(5, role);
            ps.setString(6, date);
            ps.setInt(7, specialInt);
            status = ps.executeUpdate(); 
        } catch (SQLException e) {
            e.printStackTrace(); 
        } catch (IllegalArgumentException e) {
            e.printStackTrace(); 
        }
        return status;
    }

    /**
     * Modifica la información de un asistente existente en el sistema.
     *
     * @param name     El nombre del asistente.
     * @param surname  El apellido del asistente.
     * @param email    La dirección de correo electrónico del asistente.
     * @param password La nueva contraseña del asistente.
     * @param role     El nuevo rol del asistente.
     * @param date     La nueva fecha asociada al asistente.
     * @param special  Indica si el asistente tiene atención especial.
     * @return El número de registros afectados en la base de datos como resultado de la modificación.
     */
    public int modificarAsistent(String name, String surname, String email, String password, int role, String date, Boolean special) {
        int status = 0; 
        try {
            int specialInt = special ? 1 : 0; 
            PreparedStatement ps = connect.prepareStatement(properties.getProperty("modificarAsistent"));
            ps.setString(1, name);
            ps.setString(2, surname);
            ps.setString(3, password);
            ps.setInt(4, role);
            ps.setString(5, date);
            ps.setInt(6, specialInt);
            ps.setString(7, email); 
            status = ps.executeUpdate(); 
        } catch (SQLException e) {
            e.printStackTrace(); 
        } catch (IllegalArgumentException e) {
            e.printStackTrace(); 
        }
        return status; 
    }
}
