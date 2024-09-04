package data.dao.MonitorDAO;

import java.util.ArrayList;

import business.common.LevelEducation;
import business.monitor.MonitorDTO;

/**
 * Esta interfaz define métodos para operaciones relacionadas con monitores en el sistema.
 * 
 * @author Antonio Jiménez Jiménez
 * @author Gonzalo Márquez de Torres
 * @author José María Muñoz López
 * @version 1.0
 */
public interface IMonitorDAO {

    /**
     * Registra un nuevo monitor en el sistema.
     *
     * @param newMonitor El monitor que se desea registrar.
     * @return El resultado de la operación de registro. Un valor entero que indica el éxito o el fracaso.
     */
    int registrarMonitor(MonitorDTO newMonitor);

    /**
     * Recupera una lista de monitores de la base de datos.
     *
     * @return Una lista de objetos MonitorDTO que representan a los monitores almacenados en la base de datos.
     */
    ArrayList<MonitorDTO> imprimirMonitores();

    /**
     * Verifica si un monitor está asociado a una actividad específica.
     *
     * @param idMonitor      El ID del monitor.
     * @param nameActivity   El nombre de la actividad.
     * @param levelEducation El nivel educativo de la actividad.
     * @return true si el monitor está asociado a la actividad, de lo contrario false.
     */
    boolean esMonitorAsociadaAActividad(int idMonitor, String nameActivity, LevelEducation levelEducation);
}
