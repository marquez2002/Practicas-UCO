package business.asistent;

import java.util.Date;

/**
 * Clase que representa un asistente dentro del sistema.
 * 
 * @autor Antonio Jiménez Jiménez
 * @autor Gonzalo Márquez de Torres
 * @autor José María Muñoz López
 * @version 1.0
 */
public class AsistentDTO {

    /**
     * Identificador único del asistente.
     */
    private int id;

    /**
     * Nombre del asistente.
     */
    private String name;

    /**
     * Apellido del asistente.
     */
    private String surname;

    /**
     * Correo electrónico del asistente.
     */
    private String email;

    /**
     * Rol del asistente dentro del sistema.
     */
    private int role;

    /**
     * Fecha de nacimiento del asistente.
     */
    private Date date;

    /**
     * Indica si el asistente requiere atención especial.
     */
    private boolean especial;

    /**
     * Contraseña del asistente.
     */
    private String password;

    /**
     * Constructor vacío de la clase AsistentDTO.
     * Inicializa los atributos con valores predeterminados.
     */
    public AsistentDTO() {
        this.id = 0;
        this.name = "";
        this.surname = " ";
        this.email = "";
        this.password = "";
        this.role = 0;
        this.date = new Date();
        this.especial = false;
    }

    /**
     * Constructor que inicializa un asistente con valores especificados.
     * 
     * @param id        Identificador del asistente.
     * @param name      Nombre del asistente.
     * @param surname   Apellido del asistente.
     * @param password  Contraseña del asistente.
     * @param email     Correo electrónico del asistente.
     * @param role      Rol del asistente dentro del sistema.
     * @param date      Fecha de nacimiento del asistente.
     * @param especial  Indica si el asistente requiere atención especial.
     */
    public AsistentDTO(int id, String name, String surname, String password, String email, int role, Date date, boolean especial) {
        this.id = id;
        this.name = name;
        this.surname = surname;
        this.password = password;
        this.email = email;
        this.role = role;
        this.date = date;
        this.especial = especial;
    }

    /**
     * Devuelve el identificador del asistente.
     * 
     * @return id El identificador del asistente.
     */
    public int getID() {
        return id;
    }

    /**
     * Modifica el identificador del asistente.
     * 
     * @param id El nuevo identificador del asistente.
     */
    public void setID(int id) {
        this.id = id;
    }

    /**
     * Devuelve el nombre del asistente.
     * 
     * @return name El nombre del asistente.
     */
    public String getName() {
        return name;
    }

    /**
     * Modifica el nombre del asistente.
     * 
     * @param name El nuevo nombre del asistente.
     */
    public void setName(String name) {
        this.name = name;
    }

    /**
     * Devuelve el correo electrónico del asistente.
     * 
     * @return email El correo electrónico del asistente.
     */
    public String getEmail() {
        return email;
    }

    /**
     * Modifica el correo electrónico del asistente.
     * 
     * @param email El nuevo correo electrónico del asistente.
     */
    public void setEmail(String email) {
        this.email = email;
    }

    /**
     * Devuelve el apellido del asistente.
     * 
     * @return surname El apellido del asistente.
     */
    public String getSurname() {
        return surname;
    }

    /**
     * Modifica el apellido del asistente.
     * 
     * @param surname El nuevo apellido del asistente.
     */
    public void setSurname(String surname) {
        this.surname = surname;
    }

    /**
     * Devuelve la contraseña del asistente.
     * 
     * @return password La contraseña del asistente.
     */
    public String getPassword() {
        return password;
    }

    /**
     * Modifica la contraseña del asistente.
     * 
     * @param password La nueva contraseña del asistente.
     */
    public void setPassword(String password) {
        this.password = password;
    }

    /**
     * Devuelve el rol del asistente dentro del sistema.
     * 
     * @return role El rol del asistente.
     */
    public int getRole() {
        return role;
    }

    /**
     * Modifica el rol del asistente dentro del sistema.
     * 
     * @param role El nuevo rol del asistente.
     */
    public void setRole(int role) {
        this.role = role;
    }

    /**
     * Devuelve la fecha de nacimiento del asistente.
     * 
     * @return date La fecha de nacimiento del asistente.
     */
    public Date getDate() {
        return date;
    }

    /**
     * Modifica la fecha de nacimiento del asistente.
     * 
     * @param date La nueva fecha de nacimiento del asistente.
     */
    public void setDate(Date date) {
        this.date = date;
    }

    /**
     * Devuelve si el asistente requiere atención especial.
     * 
     * @return especial Indica si el asistente requiere atención especial.
     */
    public boolean getEspecial() {
        return especial;
    }

    /**
     * Modifica si el asistente requiere atención especial.
     * 
     * @param especial Indica si el asistente requiere atención especial.
     */
    public void setEspecial(boolean especial) {
        this.especial = especial;
    }
}
