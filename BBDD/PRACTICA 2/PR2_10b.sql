SELECT nombrecompleto, MAX(consultas_datos.certidumbre) AS "Certidumbre" FROM partidos
JOIN consultas_datos ON partidos.idpartido = consultas_datos.partido
GROUP BY nombrecompleto
ORDER BY MAX(consultas_datos.certidumbre) DESC;
