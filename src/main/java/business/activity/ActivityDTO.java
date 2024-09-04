package business.activity;

import business.common.LevelEducation;
import business.common.Timetable;

/**
 * Clase que representa una actividad dentro del sistema.
 * @autor Antonio Jiménez Jiménez
 * @autor Gonzalo Márquez de Torres
 * @autor José María Muñoz López
 * @version 1.0
 */
public class ActivityDTO {

    /**
     * Nombre de la actividad.
     */
    private String name;

    /**
     * Nivel de educación requerido para la actividad.
     */
    private LevelEducation level;

    /**
     * Horario en el que se lleva a cabo la actividad.
     */
    private Timetable timetable;

    /**
     * Número de asistentes a la actividad.
     */
    private int asistents;

    /**
     * Número de monitores necesarios para la actividad.
     */
    private int numberMonitor;

    /**
     * Constructor vacío de la clase ActivityDTO.
     * Inicializa los atributos con valores predeterminados.
     */
    public ActivityDTO() {
        this.name = " ";
        this.level = LevelEducation.INFANTIL;
        this.timetable = Timetable.MANANA;
        this.asistents = 0;
        this.numberMonitor = 0;
    }

    /**
     * Constructor que inicializa la actividad con valores especificados.
     * @param name          Nombre de la actividad.
     * @param level         Nivel educativo requerido para la actividad.
     * @param timetable     Horario de la actividad.
     * @param asistents     Número de asistentes a la actividad.
     * @param numberMonitor Número de monitores necesarios para la actividad.
     */
    public ActivityDTO(String name, LevelEducation level, Timetable timetable, int asistents, int numberMonitor) {
        this.name = name;
        this.level = level;
        this.timetable = timetable;
        this.asistents = asistents;
        this.numberMonitor = numberMonitor;
    }

    /**
     * Devuelve el nombre de la actividad.
     * 
     * @return El nombre de la actividad.
     */
    public String getName() {
        return name;
    }

    /**
     * Modifica el nombre de la actividad.
     * 
     * @param name El nuevo nombre de la actividad.
     */
    public void setName(String name) {
        this.name = name;
    }

    /**
     * Devuelve el nivel educativo requerido para la actividad.
     * 
     * @return El nivel educativo de la actividad.
     */
    public LevelEducation getLevelEducation() {
        return level;
    }

    /**
     * Modifica el nivel educativo requerido para la actividad.
     * 
     * @param levelEducation El nuevo nivel educativo para la actividad.
     */
    public void setLevelEducation(LevelEducation levelEducation) {
        this.level = levelEducation;
    }

    /**
     * Devuelve el horario en el que se realiza la actividad.
     * 
     * @return El horario de la actividad.
     */
    public Timetable getTimetable() {
        return timetable;
    }

    /**
     * Modifica el horario de la actividad.
     * 
     * @param timetable El nuevo horario de la actividad.
     */
    public void setTimetable(Timetable timetable) {
        this.timetable = timetable;
    }

    /**
     * Devuelve el número de asistentes a la actividad.
     * 
     * @return El número de asistentes.
     */
    public int getAsistents() {
        return asistents;
    }

    /**
     * Modifica el número de asistentes a la actividad.
     * 
     * @param asistents El nuevo número de asistentes.
     */
    public void setAsistents(int asistents) {
        this.asistents = asistents;
    }

    /**
     * Devuelve el número de monitores necesarios para la actividad.
     * 
     * @return El número de monitores.
     */
    public int getNumberMonitor() {
        return numberMonitor;
    }

    /**
     * Modifica el número de monitores necesarios para la actividad.
     * 
     * @param numberMonitor El nuevo número de monitores.
     */
    public void setNumberMonitor(int numberMonitor) {
        this.numberMonitor = numberMonitor;
    }
}
