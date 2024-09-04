package data.dao.CampDAO;

import java.sql.Connection;
import java.sql.Date;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Properties;

import business.activity.ActivityDTO;
import business.camp.CampDTO;
import business.common.LevelEducation;
import data.dao.common.ConexionBD;

/**
 * Clase que define un Data Access Object (DAO) para gestionar campamentos.ç
 * 
 * @autor Antonio Jiménez Jiménez
 * @autor Gonzalo Márquez de Torres
 * @autor José María Muñoz López
 * @version 1.0
 */
public class CampDAO implements ICampDAO {
    private Connection connect;
    private Properties properties;

    /**
     * Inicializa una nueva instancia de la clase CampDAO.
     * Carga la configuración de la base de datos desde un archivo "sql.properties".
     */
    public CampDAO(Properties properties_) {
        properties = properties_;
        if (connect == null) {
            ConexionBD connection = new ConexionBD();
            connect = connection.getConnection();
        }
    }

    /**
     * Obtiene un campamento por su identificador único.
     * @param id El identificador único del campamento.
     * @return Una instancia de CampDTO que representa el campamento encontrado.
     */
    public CampDTO getCamp(int id) {
        CampDTO camp = null; 
        String query = properties.getProperty("getIDCamp");
        
        try (PreparedStatement pstmt = connect.prepareStatement(query)) {
            pstmt.setInt(1, id); 
            
            try (ResultSet rs = pstmt.executeQuery()) {
                if (rs.next()) {
                    camp = new CampDTO(); 
                    camp.setID(rs.getInt("id"));
                    camp.setStartDate(new Date(rs.getTimestamp("startDate").getTime()));
                    camp.setMonitor(rs.getInt("idMonitor"));
                    camp.setLevelEducation(LevelEducation.valueOf(rs.getString("levelEducation")));
                    camp.setSpecialMonitor(rs.getInt("special"));
                    camp.setEndDate(new Date(rs.getTimestamp("endDate").getTime()));
                    camp.setMaximunAsistent(rs.getInt("maximunAsistent"));
                }
            }
        } catch (SQLException | IllegalArgumentException e) {
            e.printStackTrace();
        }
        return camp; 
    }


    /**
     * Registra un nuevo campamento en el sistema.
     * @param camp El campamento que se desea registrar.
     * @return El número de registros afectados en la base de datos.
     */
    public int registrarCamp(CampDTO camp) {
        int status = 0;
        String startDate = new SimpleDateFormat("yyyy-MM-dd").format(camp.getStartDate());
        String endDate = new SimpleDateFormat("yyyy-MM-dd").format(camp.getEndDate());

        try (PreparedStatement ps = connect.prepareStatement(properties.getProperty("RegistrarCamp"))) {
            ps.setString(1, startDate);
            ps.setString(2, endDate);
            ps.setInt(3, camp.getMaximunAsistent());
            ps.setString(4, camp.getLevelEducation().toString());
            status = ps.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return status;
    }

    /**
     * Obtiene una lista de todos los campamentos disponibles en el sistema.
     * @return Una lista de CampDTO que representa los campamentos disponibles.
     */
    public ArrayList<CampDTO> imprimirCamps() {
        ArrayList<CampDTO> camps = new ArrayList<>();
        try (Statement stmt = connect.createStatement(); 
             ResultSet rs = stmt.executeQuery(properties.getProperty("imprimirCamps"))) {
            while (rs.next()) {
                CampDTO newCamp = new CampDTO();
                newCamp.setID(rs.getInt("id"));
                newCamp.setStartDate(new Date(rs.getTimestamp("startDate").getTime()));
                newCamp.setMonitor(rs.getInt("idMonitor"));
                newCamp.setLevelEducation(LevelEducation.valueOf(rs.getString("levelEducation")));
                newCamp.setSpecialMonitor(rs.getInt("special"));
                newCamp.setEndDate(new Date(rs.getTimestamp("endDate").getTime()));
                newCamp.setMaximunAsistent(rs.getInt("maximunAsistent"));
                camps.add(newCamp);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return camps; // Return the list of camps
    }

    /**
     * Obtiene una lista de nombres de actividades asociadas a un campamento específico.
     * @param id El ID del campamento del que se desean obtener las actividades.
     * @return Una lista de nombres de actividades asociadas al campamento dado.
     */
    public ArrayList<String> getActivitiesEnCamp(int id) {
        ArrayList<String> activities = new ArrayList<>();
        String query = properties.getProperty("getCamp-Activity");

        try (PreparedStatement stmt = connect.prepareStatement(query)) {
            stmt.setInt(1, id); 
            try (ResultSet rs = stmt.executeQuery()) {
                while (rs.next()) {
                    activities.add(rs.getString("name")); 
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return activities; // Devuelve la lista de nombres de actividades
    }

    /**
     * Obtiene una lista de objetos ActivityDTO que representan las actividades asociadas a un campamento específico.
     * @param id El ID del campamento del que se desean obtener las actividades.
     * @return Una lista de objetos ActivityDTO que representan las actividades.
     */
    public ArrayList<ActivityDTO> getActivitiesEnCamp2(int id) {
        ArrayList<ActivityDTO> activities = new ArrayList<>();
        String query = properties.getProperty("getCamp-Activity");

        try (PreparedStatement pstmt = connect.prepareStatement(query)) {
            pstmt.setInt(1, id); 
            
            try (ResultSet rs = pstmt.executeQuery()) {
                while (rs.next()) {
                    ActivityDTO newActivity = new ActivityDTO();
                    newActivity.setName(rs.getString("name"));
                    newActivity.setLevelEducation(LevelEducation.valueOf(rs.getString("levelEducation")));
                    activities.add(newActivity); 
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return activities; 
    }


    /**
     * Obtiene el número de actividades asociadas a un campamento específico.
     * @param idCamp El identificador único del campamento.
     * @return El número de actividades asociadas al campamento.
     */
    public int contarActividadesCamp(int idCamp) {
        int countActivities = 0;
        String query = properties.getProperty("countActivity"); 

        try (PreparedStatement stmt = connect.prepareStatement(query)) {
            stmt.setInt(1, idCamp); 
            try (ResultSet rs = stmt.executeQuery()) {
                if (rs.next()) {
                    countActivities = rs.getInt("activityCount");
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return countActivities; // Devuelve el conteo de actividades
    }


    /**
     * Verifica si una actividad ya existe en la base de datos del campamento.
     * @param id El ID del campamento.
     * @param a La actividad a verificar.
     * @return Devuelve verdadero si la actividad ya existe; de lo contrario, falso.
     */
    public Boolean comprobarActividad(int id, ActivityDTO a) {
        boolean valid = true;
        String query = properties.getProperty("getCamp-Activity");

        try (PreparedStatement stmt = connect.prepareStatement(query)) {
            // Establecer el parámetro de la consulta
            stmt.setInt(1, id);

            try (ResultSet rs2 = stmt.executeQuery()) {
                while (rs2.next()) {
                    String activityName = rs2.getString("name");
                    LevelEducation levelEducation = LevelEducation.valueOf(rs2.getString("level"));

                    // Comparar nombres de actividad y niveles educativos
                    if (a.getName().equals(activityName) && a.getLevelEducation().equals(levelEducation)) {
                        valid = false; // La actividad ya existe
                        break;
                    }
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return valid; // Devuelve si la actividad es válida (no existe previamente)
    }


    /**
     * Asocia una actividad a un campamento específico en el sistema.
     * @param activity La actividad que se desea asociar al campamento.
     * @param camp El campamento al que se desea asociar la actividad.
     * @return El número de registros afectados en la base de datos.
     */
    public int asociarActividad(ActivityDTO activity, int idCamp) {
        if (!comprobarActividad(idCamp, activity)) {
            return -1; 
        }
        int res = 0;
        try (PreparedStatement ps = connect.prepareStatement(properties.getProperty("asociarActividad"))) {
            ps.setInt(1, idCamp);
            ps.setString(2, activity.getName());
            ps.setString(3, activity.getLevelEducation().toString());
            res = ps.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return res; // Return the number of records affected
    }

    /**
     * Asocia un monitor a un campamento específico en el sistema.
     * @param idMonitor El ID del monitor a asociar.
     * @param idCamp El ID del campamento al que se desea asociar el monitor.
     * @return El número de registros afectados en la base de datos.
     */
    public int asociarMonitor(int idMonitor, int idCamp) {
        int res = 0;
        try (PreparedStatement ps = connect.prepareStatement(properties.getProperty("asociarMonitor"))) {
            ps.setInt(1, idMonitor);
            ps.setInt(2, idCamp);
            res = ps.executeUpdate(); // Execute update and get result
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return res; // Return the number of records affected
    }
    
    /**
     * Asocia un monitor especial a un campamento en la base de datos.
     *
     * @param id_monitor El ID del monitor especial a asociar.
     * @param id_camp    El ID del campamento al que se va a asociar el monitor.
     * @return Un entero que indica el resultado de la asociación:
     */
    public int asociarSpecialMonitor(int idMonitor, int idCamp) {
        int res = 0;

        try {
            String query = properties.getProperty("asociarSpecialMonitor");
            PreparedStatement ps = connect.prepareStatement(query);

            ps.setInt(1, idMonitor);
            ps.setInt(2, idCamp); 
            res = ps.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace(); 
        } catch (IllegalArgumentException e) {
            e.printStackTrace(); 
        }

        return res;
    }


    /**
     * Encuentra y devuelve una lista de campamentos disponibles en el sistema.
     *
     * @return Una lista de campamentos disponibles con sus respectivas actividades.
     */
    public ArrayList<CampDTO> buscarCampDisponibles() {
        ArrayList<CampDTO> availableCamps = new ArrayList<>();
        
        String sql = properties.getProperty("getCampsDisponibles");
              
        try (Statement stmt = connect.createStatement();
             ResultSet rs = stmt.executeQuery(sql)) {
             
            while (rs.next()) { 
                CampDTO newCamp = new CampDTO(); 
                newCamp.setID(rs.getInt("id"));
                newCamp.setStartDate(new Date(rs.getTimestamp("startDate").getTime())); 
                newCamp.setLevelEducation(LevelEducation.valueOf(rs.getString("levelEducation"))); 
                newCamp.setMonitor(rs.getInt("idMonitor")); 
                newCamp.setSpecialMonitor(rs.getInt("special")); 
                newCamp.setEndDate(new Date(rs.getTimestamp("endDate").getTime())); 
                newCamp.setMaximunAsistent(rs.getInt("maximunAsistent")); 

                availableCamps.add(newCamp); 
            }
        } catch (SQLException e) {
            e.printStackTrace(); 
        } catch (IllegalArgumentException e) {
            e.printStackTrace();
        }                    
        return availableCamps; 
    }


    /**
     * Obtiene una lista de IDs de campamentos disponibles en la base de datos.
     *
     * @return Una lista de IDs de campamentos.
     */
    public ArrayList<Integer> imprimirCampsID() {
        ArrayList<Integer> camps = new ArrayList<Integer>(); 
        
        try {
            Statement stmt = connect.createStatement();
            ResultSet rs = stmt.executeQuery(properties.getProperty("imprimirCamps")); 
            while (rs.next()) { 
                int id = rs.getInt("id"); 
                camps.add(id); 
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return camps; 
    }

}
