package business.inscription;

import java.util.Date;

/**
 * Clase abstracta que define un creador de inscripciones para un campamento.
 * Las subclases deben implementar los métodos abstractos para crear inscripciones completas y parciales.
 * 
 * @author Antonio Jiménez Jiménez
 * @author Gonzalo Márquez de Torres
 * @author José María Muñoz López
 * @version 1.0
*/
public abstract class InscriptionDTOCreation {

    /**
     * Crea una inscripción completa para un participante en un campamento con los parámetros especificados.
     *
     * @param idAsistent El identificador del participante.
     * @param idCamp El identificador del campamento.
     * @param inscriptionDate La fecha en la que se realiza la inscripción.
     * @param price El precio de la inscripción.
     * @param completada Indica si la inscripción ha sido completada.
     * @return Una instancia de InscriptionDTO que representa la inscripción completa.
     */
    public abstract InscriptionDTO RegistrationCompleta(int idAsistent, int idCamp, Date inscriptionDate, float price, Boolean completada);

    /**
     * Crea una inscripción parcial para un participante en un campamento con los parámetros especificados.
     *
     * @param idAsistent El identificador del participante.
     * @param idCamp El identificador del campamento.
     * @param inscriptionDate La fecha en la que se realiza la inscripción.
     * @param price El precio de la inscripción.
     * @param completada Indica si la inscripción ha sido completada.
     * @return Una instancia de InscriptionDTO que representa la inscripción parcial.
     */
    public abstract InscriptionDTO RegistrationParcial(int idAsistent, int idCamp, Date inscriptionDate, float price, Boolean completada);
}
