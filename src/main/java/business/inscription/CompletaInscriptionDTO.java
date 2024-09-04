package business.inscription;

import java.util.Date;

/**
 * Clase que representa una inscripción completa en un campamento.
 * Extiende la clase InscriptionDTO y proporciona una implementación predeterminada del constructor y del método toString.
 * Esta clase gestiona los detalles de una inscripción que ha sido completada.
 * 
 * @autor Antonio Jiménez Jiménez
 * @autor Gonzalo Márquez de Torres
 * @autor José María Muñoz López
 * @version 1.0
 */
public class CompletaInscriptionDTO extends InscriptionDTO {

    /**
     * Constructor predeterminado que inicializa los atributos de la inscripción completa con valores por defecto.
     * La inscripción creada con este constructor tendrá todos los valores inicializados con datos estándar.
     */
    public CompletaInscriptionDTO() {
        this.setIdAsistent(0); 
        this.setIdCamp(0); 
        this.setInscriptionDate(new Date()); 
        this.setPrice(0); 
        this.setCancelada(false);
        this.setCompletada(false);
    }

    /**
     * Devuelve una representación en cadena de la inscripción completa, incluyendo todos los atributos relevantes.
     * 
     * @return Una cadena que representa la inscripción completa, detallando si está completa, el ID del asistente,
     *         el ID del campamento, la fecha de inscripción, el precio y si es cancelable.
     */
    @Override
    public String toString() {
        return "CompletaInscriptionDTO [completada=" + getCompletada() + ", id participante="
                + getIdAsistent() + ", id campamento=" + getIdCamp() + ", fecha inscripcion="
                + getInscriptionDate() + ", precio=" + getPrice() + ", cancelada=" + getCancelada()
                + "]";
    }
}
