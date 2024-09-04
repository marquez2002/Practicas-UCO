package business.inscription;

import java.util.Date;

/**
 * Clase que implementa el creador de inscripciones tardías para un campamento.
 * Extiende la clase InscriptionDTOCreation y proporciona implementaciones de los métodos RegistrationCompleta y RegistrationParcial para crear inscripciones.
 * 
 * @author Antonio Jiménez Jiménez
 * @author Gonzalo Márquez de Torres
 * @author José María Muñoz López
 * @version 1.0
 */
public class TardiaInscriptionDTO extends InscriptionDTOCreation {

    /**
     * Crea una inscripción completa para un participante en un campamento con precio tardío.
     *
     * @param idAsistent El identificador del participante.
     * @param idCamp El identificador del campamento.
     * @param inscriptionDate La fecha en la que se realiza la inscripción.
     * @param price El precio de la inscripción tardía.
     * @param completada Indica si la inscripción está completada.
     * @return Una instancia de InscriptionDTO que representa la inscripción completa.
     */
    @Override
    public InscriptionDTO RegistrationCompleta(int idAsistent, int idCamp, Date inscriptionDate, float price, Boolean completada) {
        InscriptionDTO inscription = new CompletaInscriptionDTO();
        inscription.setIdAsistent(idAsistent);
        inscription.setIdCamp(idCamp);
        inscription.setPrice(price);
        inscription.setInscriptionDate(inscriptionDate);
        inscription.setCancelada(false);
        inscription.setCompletada(completada);
        return inscription;
    }

    /**
     * Crea una inscripción parcial para un participante en un campamento con precio tardío.
     *
     * @param idAsistent El identificador del participante.
     * @param idCamp El identificador del campamento.
     * @param inscriptionDate La fecha en la que se realiza la inscripción.
     * @param price El precio de la inscripción tardía.
     * @param completada Indica si la inscripción está completada.
     * @return Una instancia de InscriptionDTO que representa la inscripción parcial.
     */
    @Override
    public InscriptionDTO RegistrationParcial(int idAsistent, int idCamp, Date inscriptionDate, float price, Boolean completada) {
        InscriptionDTO inscription = new ParcialInscriptionDTO();
        inscription.setIdAsistent(idAsistent);
        inscription.setIdCamp(idCamp);
        inscription.setPrice(price);
        inscription.setInscriptionDate(inscriptionDate);
        inscription.setCancelada(false);
        inscription.setCompletada(completada);
        return inscription;
    }
}
