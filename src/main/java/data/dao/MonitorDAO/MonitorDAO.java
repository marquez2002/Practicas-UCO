package data.dao.MonitorDAO;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.Properties;

import business.common.LevelEducation;
import business.monitor.MonitorDTO;
import data.dao.common.ConexionBD;

/**
 * Clase que define un Data Access Object (DAO) para gestionar monitores.
 * 
 * @author Antonio Jiménez Jiménez
 * @author Gonzalo Márquez de Torres
 * @author José María Muñoz López
 * @version 1.0
 */
public class MonitorDAO implements IMonitorDAO {
    private Connection connect;
    private Properties properties;

    /**
     * Inicializa una nueva instancia de la clase MonitorDAO.
     * Carga la configuración de la base de datos desde un archivo "sql.properties".
     * Este archivo se utiliza para definir consultas SQL y otros parámetros de configuración.
     *
     * @param properties_ Las propiedades de configuración de la base de datos.
     */
    public MonitorDAO(Properties properties_) {
        properties = properties_;
        if (connect == null) {
            ConexionBD connection = new ConexionBD();
            connect = connection.getConnection();
        }
    }

    /**
     * Registra un nuevo monitor en la base de datos.
     *
     * @param newMonitor El objeto MonitorDTO que contiene la información del nuevo monitor.
     * @return El resultado de la operación de registro. Devuelve un valor entero que indica el éxito o el fracaso.
     */
    public int registrarMonitor(MonitorDTO newMonitor) {
        int status = 0;

        String query = properties.getProperty("RegistrarMonitor");
        try (PreparedStatement ps = connect.prepareStatement(query)) {
            ps.setString(1, newMonitor.getName());
            ps.setString(2, newMonitor.getSurname());
            ps.setBoolean(3, newMonitor.getSpecial());

            status = ps.executeUpdate();
        } catch (SQLException e) {
            System.out.println("Error al registrar el monitor: " + e.getMessage());
        }
        return status;
    }

    /**
     * Recupera una lista de monitores de la base de datos.
     *
     * @return Una lista de objetos MonitorDTO que representan a los monitores almacenados en la base de datos.
     */
    public ArrayList<MonitorDTO> imprimirMonitores() {
        ArrayList<MonitorDTO> monitors = new ArrayList<>();
        String query = properties.getProperty("imprimirMonitores");

        try (Statement stmt = connect.createStatement();
             ResultSet rs = stmt.executeQuery(query)) {

            while (rs.next()) {
                int id = rs.getInt("id");
                String name = rs.getString("name");
                String surname = rs.getString("surname");
                boolean special = rs.getBoolean("special");
                monitors.add(new MonitorDTO(id, name, surname, special));
            }
        } catch (SQLException e) {
            System.out.println("Error al recuperar los monitores: " + e.getMessage());
        } catch (IllegalArgumentException e) {
            System.out.println("Error en los argumentos: " + e.getMessage());
        }
        return monitors;
    }

    /**
     * Verifica si un monitor está asociado a una actividad específica.
     *
     * @param idMonitor      El ID del monitor.
     * @param name           El nombre de la actividad.
     * @param levelEducation El nivel educativo de la actividad.
     * @return true si el monitor está asociado a la actividad, de lo contrario false.
     */
    public boolean esMonitorAsociadaAActividad(int idMonitor, String name, LevelEducation levelEducation) {
        boolean associated = false;
        String sql = "SELECT * FROM Monitor_Activity WHERE idMonitor = ? AND name = ? AND levelEducation = ?";

        try (PreparedStatement ps = connect.prepareStatement(sql)) {
            ps.setInt(1, idMonitor);
            ps.setString(2, name);
            ps.setString(3, levelEducation.toString());

            ResultSet rs = ps.executeQuery();
            associated = rs.next();
        } catch (SQLException e) {
            System.out.println("Error al verificar la asociación del monitor: " + e.getMessage());
        }

        return associated;
    }

    /**
     * Cierra la conexión actual a la base de datos.
     */
    public void closeConnection() {
        try {
            if (connect != null && !connect.isClosed()) {
                connect.close();
            }
        } catch (SQLException e) {
            System.out.println("Error al cerrar la conexión: " + e.getMessage());
        }
    }
}
