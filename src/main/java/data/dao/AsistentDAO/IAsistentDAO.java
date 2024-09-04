package data.dao.AsistentDAO;

import business.asistent.AsistentDTO;

/**
 * Interfaz para acceder y gestionar asistentes en el sistema.
 */
public interface IAsistentDAO {

    /**
     * Verifica la existencia de un asistente en la base de datos.
     * 
     * @param email    La dirección de correo electrónico del asistente.
     * @param password La contraseña del asistente.
     * @return Devuelve verdadero si el asistente existe en la base de datos; de lo contrario, falso.
     */
    Boolean esAsistentExiste(String email, String password);

    /**
     * Registra un nuevo asistente en el sistema.
     *
     * @param name     El nombre del asistente.
     * @param surname  El apellido del asistente.
     * @param email    La dirección de correo electrónico del asistente.
     * @param password La contraseña del asistente.
     * @param role     El rol del asistente.
     * @param date     La fecha asociada al asistente.
     * @param special  Indica si el asistente tiene atención especial.
     * @return El número de registros afectados en la base de datos como resultado del registro.
     */
    int registrarAsistent(String name, String surname, String email, String password, int role, String date, Boolean special);

    /**
     * Modifica la información de un asistente existente en el sistema.
     *
     * @param name     El nombre del asistente.
     * @param surname  El apellido del asistente.
     * @param email    La dirección de correo electrónico del asistente.
     * @param password La nueva contraseña del asistente.
     * @param role     El nuevo rol del asistente.
     * @param date     La nueva fecha asociada al asistente.
     * @param special  Indica si el asistente tiene atención especial.
     * @return El número de registros afectados en la base de datos como resultado de la modificación.
     */
    int modificarAsistent(String name, String surname, String email, String password, int role, String date, Boolean special);

    /**
     * Recupera un objeto AsistentDTO basado en la dirección de correo electrónico proporcionada.
     *
     * @param email La dirección de correo electrónico del asistente.
     * @return Un objeto AsistentDTO correspondiente a la dirección de correo electrónico proporcionada, si existe; de lo contrario, null.
     */
    AsistentDTO getAsistentConEmail(String email);
    
    /**
     * Verifica si un asistente está registrado en el sistema utilizando su dirección de correo electrónico.
     *
     * @param email La dirección de correo electrónico del asistente.
     * @return true si el asistente está registrado en el sistema, de lo contrario false.
     */
    Boolean esAsistentRegistrado(String email);
    
    /**
     * Verifica si un asistente tiene un estado especial identificado por un ID específico.
     *
     * @param id El ID del estado especial del asistente.
     * @return true si el asistente tiene un estado especial identificado por el ID proporcionado, de lo contrario false.
     */
    Boolean esAsistentSpecial(int id);
}
