package business.inscription;

import java.util.Date;

/**
 * Clase que representa una inscripción parcial en un campamento.
 * Extiende la clase InscriptionDTO y proporciona una implementación predeterminada
 * del constructor y el método toString.
 * 
 * @author Antonio Jiménez Jiménez
 * @author Gonzalo Márquez de Torres
 * @author José María Muñoz López
 * @version 1.0
 */
public class ParcialInscriptionDTO extends InscriptionDTO {

    /**
     * Constructor predeterminado que inicializa los atributos de la inscripción parcial con valores predeterminados.
     */
    public ParcialInscriptionDTO() {
        this.setIdAsistent(0);
        this.setIdCamp(0);
        this.setInscriptionDate(new Date());
        this.setPrice(0);
        this.setCancelada(false);
        this.setCompletada(false);
    }

    @Override
    public String toString() {
        return "ParcialInscription [completada=" + getCompletada() + 
               ", idParticipante=" + getIdAsistent() + 
               ", idCampamento=" + getIdCamp() + 
               ", fechaInscripcion=" + getInscriptionDate() + 
               ", precio=" + getPrice() + 
               ", cancelable=" + getCancelada() + "]";
    }
}
