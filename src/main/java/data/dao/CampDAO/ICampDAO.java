package data.dao.CampDAO;

import java.util.ArrayList;

import business.activity.ActivityDTO;
import business.camp.CampDTO;

/**
 * Interfaz para acceder y gestionar campamentos en el sistema.
 * 
 * @autor Antonio Jiménez Jiménez
 * @autor Gonzalo Márquez de Torres
 * @autor José María Muñoz López
 * @version 1.0
 */
public interface ICampDAO {

    /**
     * Obtiene un campamento por su identificador único.
     *
     * @param id El identificador único del campamento que se desea obtener.
     * @return Una instancia de CampDTO que representa el campamento encontrado, o null si no se encontró ningún campamento con el identificador especificado.
     */
    CampDTO getCamp(int id);

    /**
     * Registra un nuevo campamento en el sistema.
     *
     * @param camp El campamento que se desea registrar.
     * @return El número de registros afectados en la base de datos como resultado del registro.
     */
    int registrarCamp(CampDTO camp);

    /**
     * Obtiene una lista de todos los campamentos disponibles en el sistema.
     *
     * @return Una lista de CampDTO que representa los campamentos disponibles.
     */
    ArrayList<CampDTO> imprimirCamps();

    /**
     * Obtiene el número de actividades asociadas a un campamento específico.
     *
     * @param idCamp El identificador único del campamento.
     * @return El número de actividades asociadas al campamento.
     */
    int contarActividadesCamp(int idCamp);

    /**
     * Verifica si una actividad ya existe en la base de datos del campamento para un ID dado.
     *
     * @param id El ID del campamento.
     * @param a  La actividad a verificar.
     * @return Devuelve verdadero si la actividad ya existe en la base de datos del campamento identificado por el ID proporcionado; de lo contrario, falso.
     */
    Boolean comprobarActividad(int id, ActivityDTO a);

    /**
     * Asocia una actividad a un campamento si es posible.
     *
     * @param activity La actividad que se desea asociar al campamento.
     * @param camp El campamento al que se desea asociar la actividad.
     * @return El resultado de la operación de asociación (por ejemplo, éxito o fracaso).
     */
    int asociarActividad(ActivityDTO activity, int camp);

    /**
     * Asocia un monitor a un campamento si es posible.
     *
     * @param id_monitor El ID del monitor que se desea asociar al campamento.
     * @param id_camp El ID del campamento al que se desea asociar al monitor.
     * @return El resultado de la operación de asociación (por ejemplo, éxito o fracaso).
     */
    int asociarMonitor(int idMonitor, int idCamp);

    /**
     * Asocia un monitor especializado a un campamento si es posible.
     *
     * @param id_monitor El ID del monitor especializado que se desea asociar al campamento.
     * @param id_camp El ID del campamento al que se desea asociar al monitor especializado.
     * @return El resultado de la operación de asociación (por ejemplo, éxito o fracaso).
     */
    int asociarSpecialMonitor(int idMonitor, int idCamp);

    /**
     * Busca campamentos disponibles en el sistema.
     *
     * @return Una lista de CampDTO que representa los campamentos disponibles en el sistema.
     */
    ArrayList<CampDTO> buscarCampDisponibles();

    /**
     * Obtiene una lista de nombres de actividades asociadas a un campamento específico.
     *
     * @param id El ID del campamento del que se desean obtener las actividades.
     * @return Una lista de nombres de actividades asociadas al campamento dado.
     */
    ArrayList<String> getActivitiesEnCamp(int id);

    /**
     * Obtiene una lista de objetos ActivityDTO que representan las actividades asociadas a un campamento específico.
     *
     * @param id El ID del campamento del que se desean obtener las actividades.
     * @return Una lista de objetos ActivityDTO que representan las actividades asociadas al campamento dado.
     */
    ArrayList<ActivityDTO> getActivitiesEnCamp2(int id);

    /**
     * Obtiene una lista de IDs de campamentos disponibles en el sistema.
     *
     * @return Una lista de IDs de campamentos.
     */
    ArrayList<Integer> imprimirCampsID();
}
