package business.inscription;

import java.util.Date;

/**
 * Clase abstracta que representa una inscripción dentro del sistema.
 * Esta clase proporciona los atributos y métodos básicos para manejar la información de las inscripciones
 * de los asistentes a los campamentos.
 * 
 * @author Antonio Jiménez Jiménez
 * @author Gonzalo Márquez de Torres
 * @author José María Muñoz López
 * @version 1.0
 */
public abstract class InscriptionDTO {
    
    /**
     * ID del asistente que realiza la inscripción.
     */
    private int idAsistent;
    
    /**
     * ID del campamento al que se realiza la inscripción.
     */
    private int idCamp;
    
    /**
     * Fecha en la que se realiza la inscripción.
     */
    private Date inscriptionDate;
    
    /**
     * Precio de la inscripción.
     */
    private float price;
    
    /**
     * Indica si la inscripción ha sido completada.
     */
    private Boolean completada_;
    
    /**
     * Indica si la inscripción ha sido cancelada.
     */
    private Boolean cancelada_;
    
    /**
     * Devuelve el identificador del asistente que realiza la inscripción.
     * 
     * @return idAsistent El identificador del asistente que realiza la inscripción.
     */
    public int getIdAsistent() {
        return idAsistent;
    }
    
    /**
     * Modifica el ID del asistente que realiza la inscripción.
     * 
     * @param idAsistent El ID del asistente.
     */
    public void setIdAsistent(int idAsistent) {
        this.idAsistent = idAsistent;
    }

    /**
     * Devuelve el identificador del campamento.
     * 
     * @return idCamp El identificador del campamento.
     */
    public int getIdCamp() {
        return idCamp;
    }
    
    /**
     * Modifica el identificador del campamento.
     * 
     * @param idCamp El identificador del campamento.
     */
    public void setIdCamp(int idCamp) {
        this.idCamp = idCamp;
    }
    
    /**
     * Devuelve la fecha de la inscripción al campamento.
     * 
     * @return inscriptionDate La fecha de la inscripción al campamento.
     */
    public Date getInscriptionDate() {
        return inscriptionDate;
    }
    
    /**
     * Modifica la fecha de inscripción del campamento.
     * 
     * @param inscriptionDate La fecha de inscripción del campamento.
     */
    public void setInscriptionDate(Date inscriptionDate) {
        this.inscriptionDate = inscriptionDate;
    }
    
    /**
     * Devuelve el precio de la inscripción.
     * 
     * @return price El precio de la inscripción.
     */
    public Float getPrice() {
        return price;
    }
    
    /**
     * Modifica el precio de inscripción del campamento.
     * 
     * @param price El precio de inscripción del campamento.
     */
    public void setPrice(float price) {
        this.price = price;
    }
    
    /**
     * Devuelve si la inscripción está completada.
     * 
     * @return completada_ true si la inscripción está completada, false en caso contrario.
     */
    public Boolean getCompletada() {
        return completada_;
    }
    
    /**
     * Modifica el estado de la inscripción, indicando si está completada.
     * 
     * @param completada true si la inscripción está completada, false en caso contrario.
     */
    public void setCompletada(Boolean completada) {
        this.completada_ = completada;
    }
    
    /**
     * Devuelve si la inscripción está cancelada.
     * 
     * @return cancelada_ true si la inscripción está cancelada, false en caso contrario.
     */
    public Boolean getCancelada() {
        return cancelada_;
    }
    
    /**
     * Modifica el estado de la inscripción, indicando si está cancelada.
     * 
     * @param cancelada true si la inscripción está cancelada, false en caso contrario.
     */
    public void setCancelada(Boolean cancelada) {
        this.cancelada_ = cancelada;
    }
}
