package data.dao.common;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

import javax.naming.Context;
import javax.naming.InitialContext;
import javax.naming.NamingException;

/**
 * Clase que representa los métodos para la conexión con la base de datos.
 * Esta clase encapsula la lógica para establecer y cerrar conexiones con la base de datos.
 * 
 * @autor Antonio Jiménez Jiménez
 * @autor Gonzalo Márquez de Torres
 * @autor José María Muñoz López
 * @version 1.0
 */
public class ConexionBD {
    protected Connection connection = null;

    /**
     * Establece una conexión a la base de datos utilizando parámetros de configuración.
     * 
     * @return Un objeto Connection que representa la conexión a la base de datos, 
     *         o null si la conexión no se pudo establecer.
     */
    public Connection getConnection() {
        try {           
            Context ctx = new InitialContext();
            Context env = (Context) ctx.lookup("java:comp/env");
            final String url = (String) env.lookup("url");
            final String user = (String) env.lookup("user");
            final String password = (String) env.lookup("password");
            
            // Carga el controlador JDBC para MySQL
            Class.forName("com.mysql.jdbc.Driver");

            // Establece la conexión a la base de datos
            this.connection = (Connection) DriverManager.getConnection(url, user, password);
            System.err.println("Database connection successfully opened!");
            
        } catch (NamingException e) {
            e.printStackTrace();
            
        } catch (SQLException e) {
            System.err.println("Connection to MySQL has failed!");
            e.printStackTrace();
            
        } catch (ClassNotFoundException e) {
            System.err.println("JDBC Driver not found.");
            e.printStackTrace();
        }                
        return this.connection;
    }

    /**
     * Cierra la conexión a la base de datos si está abierta.
     * Se utiliza para liberar recursos y evitar fugas de memoria.
     */
    public void closeConnection() {
        try {
            // Verifica si la conexión no es nula y está abierta antes de cerrarla
            if (this.connection != null && !this.connection.isClosed()) {
                this.connection.close(); // Cierra la conexión a la base de datos
                System.out.println("Database connection successfully closed!");
            }
        } catch (SQLException e) {
            System.err.println("Error while trying to close the connection.");
            e.printStackTrace();
        }
    }
}
