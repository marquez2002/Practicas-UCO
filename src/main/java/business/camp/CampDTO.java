package business.camp;

import java.util.Date;
import java.util.concurrent.TimeUnit;

import business.common.LevelEducation;

/**
 * Clase que representa un campamento dentro del sistema.
 * 
 * @autor Antonio Jiménez Jiménez
 * @autor Gonzalo Márquez de Torres
 * @autor José María Muñoz López
 * @version 1.0
 */

public class CampDTO {

    /**
     * Identificador único del campamento.
     */
    private int id;

    /**
     * Fecha de inicio del campamento.
     */
    private Date startDate;

    /**
     * Fecha de finalización del campamento.
     */
    private Date endDate;

    /**
     * Nivel educativo requerido para participar en el campamento.
     */
    private LevelEducation level;

    /**
     * Número máximo de asistentes permitidos en el campamento.
     */
    private int maximunAsistent;

    /**
     * Número de monitores asignados al campamento.
     */
    private int monitor;

    /**
     * Número de monitores especializados asignados al campamento.
     */
    private int specialMonitor;

    /**
     * Constructor vacío de la clase CampDTO.
     * Inicializa los atributos con valores predeterminados.
     */
    public CampDTO() {
        this.id = 0;
        this.startDate = new Date();
        this.endDate = new Date();
        this.level = LevelEducation.INFANTIL;
        this.maximunAsistent = 0;
        this.monitor = 0;
        this.specialMonitor = 0;
    }

    /**
     * Constructor que inicializa un campamento con valores especificados.
     * 
     * @param id             Identificador del campamento.
     * @param startDate      Fecha de inicio del campamento.
     * @param endDate        Fecha de finalización del campamento.
     * @param levelEducation Nivel educativo requerido para el campamento.
     * @param maximunAsistent Número máximo de asistentes permitidos en el campamento.
     */
    public CampDTO(int id, Date startDate, Date endDate, LevelEducation levelEducation, int maximunAsistent) {
        this.id = id;
        this.startDate = startDate;
        this.endDate = endDate;
        this.level = levelEducation;
        this.maximunAsistent = maximunAsistent;
        this.monitor = 0;
        this.specialMonitor = 0;
    }

    /**
     * Devuelve el identificador del campamento.
     * 
     * @return id El identificador del campamento.
     */
    public int getID() {
        return id;
    }

    /**
     * Modifica el identificador del campamento.
     * 
     * @param id El nuevo identificador del campamento.
     */
    public void setID(int id) {
        this.id = id;
    }

    /**
     * Devuelve la fecha de inicio del campamento.
     * 
     * @return startDate La fecha de inicio del campamento.
     */
    public Date getStartDate() {
        return startDate;
    }

    /**
     * Modifica la fecha de inicio del campamento.
     * 
     * @param startDate La nueva fecha de inicio del campamento.
     */
    public void setStartDate(Date startDate) {
        this.startDate = startDate;
    }

    /**
     * Devuelve la fecha de finalización del campamento.
     * 
     * @return endDate La fecha de finalización del campamento.
     */
    public Date getEndDate() {
        return endDate;
    }

    /**
     * Modifica la fecha de finalización del campamento.
     * 
     * @param endDate La nueva fecha de finalización del campamento.
     */
    public void setEndDate(Date endDate) {
        this.endDate = endDate;
    }

    /**
     * Devuelve el nivel educativo requerido para el campamento.
     * 
     * @return level El nivel educativo requerido para el campamento.
     */
    public LevelEducation getLevelEducation() {
        return level;
    }

    /**
     * Modifica el nivel educativo requerido para el campamento.
     * 
     * @param levelEducation El nuevo nivel educativo requerido para el campamento.
     */
    public void setLevelEducation(LevelEducation levelEducation) {
        this.level = levelEducation;
    }

    /**
     * Devuelve el número máximo de asistentes permitidos en el campamento.
     * 
     * @return maximunAsistent El número máximo de asistentes.
     */
    public int getMaximunAsistent() {
        return maximunAsistent;
    }

    /**
     * Modifica el número máximo de asistentes permitidos en el campamento.
     * 
     * @param maximunAsistent El nuevo número máximo de asistentes.
     */
    public void setMaximunAsistent(int maximunAsistent) {
        this.maximunAsistent = maximunAsistent;
    }

    /**
     * Devuelve el número de monitores asignados al campamento.
     * 
     * @return monitor El número de monitores asignados.
     */
    public int getMonitor() {
        return monitor;
    }

    /**
     * Modifica el número de monitores asignados al campamento.
     * 
     * @param monitor El nuevo número de monitores asignados.
     */
    public void setMonitor(int monitor) {
        this.monitor = monitor;
    }

    /**
     * Devuelve el número de monitores especializados asignados al campamento.
     * 
     * @return specialMonitor El número de monitores especializados asignados.
     */
    public int getSpecialMonitor() {
        return specialMonitor;
    }

    /**
     * Modifica el número de monitores especializados asignados al campamento.
     * 
     * @param specialMonitor El nuevo número de monitores especializados asignados.
     */
    public void setSpecialMonitor(int specialMonitor) {
        this.specialMonitor = specialMonitor;
    }

    /**
     * Calcula la diferencia en horas entre la fecha de inicio del campamento y la fecha actual.
     * 
     * @return La diferencia en horas entre la fecha de inicio del campamento y la fecha actual.
     */
    public long calculoHoras() {
        long res;
        Date campDate = this.getStartDate();
        Date today = new Date();
        res = campDate.getTime() - today.getTime();
        return TimeUnit.HOURS.convert(res, TimeUnit.MILLISECONDS);
    }
}
