SELECT partidos.nombrecompleto, COUNT(consultas_datos.partido) FROM partidos, consultas_datos
WHERE partidos.idpartido = consultas_datos.partido 
GROUP BY partidos.nombrecompleto
ORDER BY COUNT(consultas_datos.partido) DESC;

/*
3�- [Ejercicios Eliminatorio] �Cu�l fue el partido que los ciudadanos fueron consultados un mayor
n�mero de veces? S�lo puede usar una vez: SELECT, FROM, WHERE y JOIN. Resultado: �Partido
Socialista Obrero Espa�ol?18�
*/


/*
2�- Muestra el nombre de los votantes cuya longitud del primer nombre sea menor que el ID de la
localidad a la que pertenecen y junto a ella muestra la diferencia de edad (en a�os) entre la persona
m�s joven y m�s mayor de su localidad. Cada columna se llamar� �Nombre� y �Diferencia�
respectivamente. [Nota: en caso de no usar EXTRACT simplemente se restan las fechas y se divide
entre 365 y es igual de v�lido].

*/

/*
EJERCICIO 1
SELECT nombrecompleto AS Nombre, COUNT(consultas_datos.partido) AS Consultas FROM partidos
LEFT JOIN consultas_datos ON consultas_datos.partido = partidos.idpartido
WHERE consultas_datos.respuesta = 'No' AND consultas_datos.certidumbre > 0.1 AND consultas_datos.certidumbre > 0.6 
GROUP BY nombrecompleto;

EJERCICIO 3
SELECT partidos.nombrecompleto, COUNT(consultas_datos.partido) FROM partidos, consultas_datos
WHERE partidos.idpartido = consultas_datos.partido 
GROUP BY partidos.nombrecompleto
ORDER BY COUNT(consultas_datos.partido) DESC;

EJERCICIO 4
ALTER TABLE votantes
ADD CONSTRAINT constraint_email CHECK(email LIKE '%@%.%');
*/