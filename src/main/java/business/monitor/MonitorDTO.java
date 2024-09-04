package business.monitor;

/**
 * Clase que representa un monitor dentro del sistema.
 * 
 * @author Antonio Jiménez Jiménez
 * @author Gonzalo Márquez de Torres
 * @author José María Muñoz López
 * @version 1.0
 */
public class MonitorDTO {
    
    /**
     * Identificador del monitor.
     */
    private int id;
    
    /**
     * Nombre del monitor.
     */
    private String name;
    
    /**
     * Apellido del monitor.
     */
    private String surname;
    
    /**
     * Indica si el monitor es un educador especial.
     */
    private boolean special;
    
    /**
     * Constructor inicial de la clase MonitorDTO.
     * Inicializa los atributos con valores por defecto.
     */
    public MonitorDTO() {
        this.id = 0;
        this.name = "";
        this.surname = "";
        this.special = false;
    }
    
    /**
     * Constructor de la clase MonitorDTO.
     * 
     * @param id El identificador del monitor.
     * @param name El nombre del monitor.
     * @param surname El apellido del monitor.
     * @param special Indica si el monitor es un educador especial.
     */
    public MonitorDTO(int id, String name, String surname, boolean special) {
        this.id = id;
        this.name = name;
        this.surname = surname;
        this.special = special;
    }
    
    /**
     * Devuelve el identificador del monitor.
     * 
     * @return El identificador del monitor.
     */
    public int getId() {
        return id;
    }
    
    /**
     * Modifica el identificador del monitor.
     * 
     * @param id El identificador del monitor.
     */
    public void setId(int id) {
        this.id = id;
    }
    
    /**
     * Devuelve el nombre del monitor.
     * 
     * @return El nombre del monitor.
     */
    public String getName() {
        return name;
    }
    
    /**
     * Modifica el nombre del monitor.
     * 
     * @param name El nombre del monitor.
     */
    public void setName(String name) {
        this.name = name;
    }
    
    /**
     * Devuelve el apellido del monitor.
     * 
     * @return El apellido del monitor.
     */
    public String getSurname() {
        return surname;
    }
    
    /**
     * Modifica el apellido del monitor.
     * 
     * @param surname El apellido del monitor.
     */
    public void setSurname(String surname) {
        this.surname = surname;
    }
    
    /**
     * Devuelve si el monitor es un educador especial.
     * 
     * @return true si el monitor es un educador especial, false en caso contrario.
     */
    public boolean getSpecial() {
        return special;
    }
    
    /**
     * Modifica si el monitor es un educador especial.
     * 
     * @param special Indica si el monitor es un educador especial.
     */
    public void setSpecial(boolean special) {
        this.special = special;
    }
}
