package display.userbean;

/**
 * Clase que representa un bean de usuario serializable.
 * Esta clase almacena información básica de un usuario.
 * 
 * @author Antonio Jiménez Jiménez
 * @author Gonzalo Márquez de Torres
 * @author José María Muñoz López
 * @version 1.0
 */

public class userBean implements java.io.Serializable {
	
	private static final long serialVersionUID = 1L;

	private String name = "";
	private String email = "";
	private int role =0;
	private int id = 0;
	
	/**
     * Obtiene el nombre del usuario.
     *
     * @return El nombre del usuario.
     */
	public String getName() {
		return name;
	}
	
	/**
     * Establece el nombre del usuario.
     *
     * @param name El nombre del usuario a establecer.
     */
	public void setName(String name) {
		this.name = name;
	}
	
	/**
     * Obtiene el correo electrónico del usuario.
     *
     * @return El correo electrónico del usuario.
     */
	public String getEmail() {
		return email;
	}
	
	/**
     * Establece el correo electrónico del usuario.
     *
     * @param email El correo electrónico del usuario a establecer.
     */
	public void setEmail(String email) {
		this.email = email;
	}

	/**
     * Obtiene el rol del usuario.
     *
     * @return El rol del usuario.
     */
	public int getRole() {
		return role;
	}
	
	/**
     * Establece el rol del usuario.
     *
     * @param role El rol del usuario a establecer.
     */
	public void setRole(int role) {
		this.role = role;
	}
	
	 /**
     * Obtiene el ID del usuario.
     *
     * @return El ID del usuario.
     */
	public int getId() {
		return id;
	}
	
	/**
     * Establece el ID del usuario.
     *
     * @param id El ID del usuario a establecer.
     */
	public void setId(int id) {
		this.id = id;
	}
}