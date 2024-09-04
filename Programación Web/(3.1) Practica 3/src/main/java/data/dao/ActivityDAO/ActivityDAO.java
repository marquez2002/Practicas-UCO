package data.dao.ActivityDAO;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.Properties;

import business.activity.ActivityDTO;
import business.common.LevelEducation;
import business.common.Timetable;
import data.dao.common.ConexionBD;

/**
 * Clase que define un Data Access Object (DAO) para gestionar actividades.
 * 
 * @author Antonio Jiménez Jiménez
 * @author Gonzalo Márquez de Torres
 * @author José María Muñoz López
 * @version 1.0
 */
public class ActivityDAO implements IActivityDAO {
    private Connection connect;
    private Properties properties;

    /**
     * Inicializa una nueva instancia de la clase ActivityDAO.
     * Carga la configuración de la base de datos desde un archivo "sql.properties".
     * Este archivo se utiliza para definir consultas SQL y otros parámetros de configuración.
     */
    public ActivityDAO(Properties properties_) {
        properties = properties_;
        if (connect == null) {
            ConexionBD connection = new ConexionBD();
            connect = connection.getConnection();
        }
    }

    /**
     * Registra una nueva actividad en el sistema.
     *
     * @param activity La actividad que se desea registrar.
     * @return El número de registros afectados en la base de datos como resultado del registro.
     */
    public int registrarActividad(ActivityDTO activity) {
        int res = 0;
        try (PreparedStatement ps = connect.prepareStatement(properties.getProperty("RegistrarActividad"))) {
            ps.setString(1, activity.getName());
            ps.setString(2, activity.getLevelEducation().toString());
            ps.setString(3, activity.getTimetable().toString());
            ps.setInt(4, activity.getAsistents());
            ps.setInt(5, activity.getNumberMonitor());
            res = ps.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return res;
    }

    /**
     * Obtiene una lista de todas las actividades disponibles en el sistema.
     *
     * @return Una lista de ActivityDTO que representa las actividades disponibles.
     */
    public ArrayList<ActivityDTO> imprimirActividades() {
        ArrayList<ActivityDTO> activities = new ArrayList<>();
        try (Statement stmt = connect.createStatement();
             ResultSet rs = stmt.executeQuery(properties.getProperty("imprimirActividades"))) {
            while (rs.next()) {
                String name = rs.getString("name");
                LevelEducation levelEducation = LevelEducation.valueOf(rs.getString("levelEducation"));
                Timetable timetable = Timetable.valueOf(rs.getString("timetable"));
                int asistents = rs.getInt("asistents");
                int numberMonitor = rs.getInt("numberMonitor");

                ActivityDTO newActivity = new ActivityDTO(); 
                newActivity.setName(name);
                newActivity.setLevelEducation(levelEducation);
                newActivity.setTimetable(timetable);
                newActivity.setAsistents(asistents);
                newActivity.setNumberMonitor(numberMonitor);
                activities.add(newActivity);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        } catch (IllegalArgumentException e) {
            e.printStackTrace();
        }
        return activities;
    }

    /**
     * Recupera y devuelve una lista de objetos ActivityDTO con nombres y niveles de actividades desde la base de datos.
     *
     * @return Una lista de objetos ActivityDTO que contienen nombres y niveles de actividades.
     */
    public ArrayList<ActivityDTO> imprimirActividadNameAndLevel() {
        ArrayList<ActivityDTO> activities = new ArrayList<>();
        try (Statement stmt = connect.createStatement();
             ResultSet rs = stmt.executeQuery(properties.getProperty("imprimirActividades"))) {
            while (rs.next()) {
                String name = rs.getString("name");
                LevelEducation levelEducation = LevelEducation.valueOf(rs.getString("levelEducation"));

                ActivityDTO newActivity = new ActivityDTO();
                newActivity.setName(name);
                newActivity.setLevelEducation(levelEducation);
                activities.add(newActivity);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        } catch (IllegalArgumentException e) {
            e.printStackTrace();
        }
        return activities;
    }

    /**
     * Asocia un monitor a una actividad si hay capacidad disponible para más monitores.
     *
     * @param idMonitor      El ID del monitor a asociar.
     * @param name           El nombre de la actividad.
     * @param levelEducation El nivel educativo de la actividad.
     * @return El número de registros afectados en la base de datos.
     */
    public int asociarMonitor(int idMonitor, String name, LevelEducation levelEducation) {
        int res = 0;
        try (PreparedStatement ps = connect.prepareStatement(properties.getProperty("asociarMonitorActividad"))) {
            ps.setInt(1, idMonitor);
            ps.setString(2, name);
            ps.setString(3, levelEducation.toString());
            res = ps.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        } catch (IllegalArgumentException e) {
            e.printStackTrace();
        }
        return res;
    }

    /**
     * Cuenta el número de monitores asociados a una actividad con un nombre y nivel específicos en la base de datos.
     *
     * @param name           El nombre de la actividad.
     * @param levelEducation El nivel de educación de la actividad.
     * @return El número de monitores asociados a la actividad con el nombre y nivel dados.
     */
    public int contarMonitores(String name, LevelEducation levelEducation) {
        int count = 0;
        String sql = properties.getProperty("getActividadMonitores");

        try (PreparedStatement ps = connect.prepareStatement(sql)) {
            ps.setString(1, name);

            ResultSet rs = ps.executeQuery();
            while (rs.next()) {
                count++;
            }
        } catch (SQLException e) {
            e.printStackTrace(); // Considera usar un logger en lugar de printStackTrace
        }
        return count;
    }

    /**
     * Verifica si una actividad está asociada a un campamento específico en la base de datos.
     *
     * @param idCamp        El ID del campamento.
     * @param name          El nombre de la actividad.
     * @param level         El nivel de educación de la actividad.
     * @return true si la actividad está asociada al campamento dado, de lo contrario false.
     */
    public boolean activitidadAsociadaACamp(int idCamp, String name, LevelEducation levelEducation) {
        boolean asociate = false;
        try {
            String sql = properties.getProperty("estaAsociada");
            PreparedStatement ps = connect.prepareStatement(sql);
            ps.setInt(1, idCamp);
            ps.setString(2, name);
            ps.setString(3, levelEducation != null ? levelEducation.toString() : "");

            ResultSet rs = ps.executeQuery();
            if (rs.next()) {
                asociate = true;
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return asociate;
    }
}
