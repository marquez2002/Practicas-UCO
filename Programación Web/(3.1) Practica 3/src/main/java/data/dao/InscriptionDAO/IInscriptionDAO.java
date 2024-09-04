package data.dao.InscriptionDAO;

import java.util.ArrayList;

import business.inscription.InscriptionDTO;

public interface IInscriptionDAO {

	/**
	 * Registra una nueva inscripción en la base de datos.
	 *
	 * @param inscription El objeto InscriptionDTO a registrar.
	 * @return Un entero que representa el resultado del registro.
	 */
	int registrarInscription(InscriptionDTO inscription);

	/**
	 * Imprime y devuelve todas las inscripciones almacenadas en la base de datos.
	 *
	 * @return Un ArrayList de objetos InscriptionDTO que representan todas las inscripciones almacenadas.
	 */
	ArrayList<InscriptionDTO> imprimirInscriptions();
	
	/**
	 * Cuenta el número de inscripciones en un campamento específico.
	 *
	 * @param camp El ID del campamento del que se desea contar las inscripciones.
	 * @return El número de inscripciones en el campamento dado.
	 */
	int contarInscriptionsCamp(int camp);
	
	/**
	 * Obtiene una lista de objetos InscriptionDTO que representan las inscripciones de un participante por su ID.
	 *
	 * @param id_participant El ID del participante del que se desean obtener las inscripciones.
	 * @return Una lista de InscriptionDTO que representan las inscripciones del participante.
	 */
	ArrayList<InscriptionDTO> getAsistentInscriptionsById(int idAsistent);
	
	/**
	 * Elimina una inscripción según el ID del participante y el ID del campamento.
	 *
	 * @param participantId El ID del participante.
	 * @param campId        El ID del campamento.
	 * @return true si la eliminación de la inscripción fue exitosa, de lo contrario false.
	 */
	boolean eliminarInscriptionByAsistentAndIdCamp(int idAsistent, int campId);
	
	/**
	 * Calcula el precio total de una inscripción completa en función del número de actividades y el tipo de inscripción.
	 *
	 * @param numActivities   El número de actividades seleccionadas.
	 * @param inscriptionType El tipo de inscripción (completa o parcial).
	 * @return El precio total de la inscripción completa.
	 */
	int calcularPrecioCompleto(int numActivities, String inscriptionType);
	
	/**
	 * Calcula el precio de una inscripción parcial en función del número de actividades y el tipo de inscripción.
	 *
	 * @param numActivities   El número de actividades seleccionadas.
	 * @param inscriptionType El tipo de inscripción (completa o parcial).
	 * @return El precio de la inscripción parcial.
	 */
	int calcularPrecioParcial(int numActivities, String inscriptionType);
	
	/**
	 * Obtiene una lista de IDs de los asistentes en un campamento específico.
	 *
	 * @param camp_id El ID del campamento del que se desean obtener los asistentes.
	 * @return Una lista de IDs de los asistentes en el campamento.
	 */
	ArrayList<Integer> getAsistentsEnCamp(int idCamp);

}
