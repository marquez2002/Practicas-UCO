package data.dao.ActivityDAO;

import java.util.ArrayList;

import business.activity.ActivityDTO;
import business.common.LevelEducation;

/**
 * Interfaz para acceder y gestionar actividades en el sistema.
 * 
 * @author Antonio Jiménez Jiménez
 * @author Gonzalo Márquez de Torres
 * @author José María Muñoz López
 * @version 1.0
 */
public interface IActivityDAO {

    /**
     * Registra una nueva actividad en el sistema.
     *
     * @param newActivity La actividad que se desea registrar.
     * @return El identificador único de la actividad registrada.
     */
    int registrarActividad(ActivityDTO newActivity);

    /**
     * Obtiene una lista de todas las actividades disponibles en el sistema.
     *
     * @return Una lista de ActivityDTO que representa las actividades disponibles.
     */
    ArrayList<ActivityDTO> imprimirActividades();

    /**
     * Asocia un monitor a una actividad si hay capacidad disponible para más monitores.
     *
     * @param idMonitor      El ID del monitor a asociar.
     * @param name           El nombre de la actividad.
     * @param levelEducation El nivel educativo de la actividad.
     * @return {@code true} si se pudo asociar el monitor a la actividad debido a la disponibilidad, de lo contrario, {@code false}.
     */
    int asociarMonitor(int idMonitor, String name, LevelEducation levelEducation); 

    /**
     * Recupera y devuelve una lista de objetos ActivityDTO con nombres y niveles de actividades desde la base de datos.
     *
     * @return Una lista de objetos ActivityDTO que contienen nombres y niveles de actividades.
     */
    ArrayList<ActivityDTO> imprimirActividadNameAndLevel(); 

    /**
     * Cuenta el número de monitores asociados a una actividad con un nombre y nivel específicos en la base de datos.
     *
     * @param name           El nombre de la actividad.
     * @param levelEducation El nivel de educación de la actividad.
     * @return El número de monitores asociados a la actividad con el nombre y nivel dados.
     */
    int contarMonitores(String name, LevelEducation levelEducation);

    /**
     * Verifica si una actividad está asociada a un campamento específico en la base de datos.
     *
     * @param idCamp        El ID del campamento.
     * @param nameActivity  El nombre de la actividad.
     * @param levelEducation El nivel de educación de la actividad.
     * @return true si la actividad está asociada al campamento dado, de lo contrario false.
     */
    boolean activitidadAsociadaACamp(int idCamp, String name, LevelEducation levelEducation); // Corregido "id_camp" y "name_activity"
}
