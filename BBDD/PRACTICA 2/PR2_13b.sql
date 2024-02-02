SELECT nombrecompleto, AVG(consultas_datos.certidumbre) AS "Certidumbre" FROM partidos
JOIN consultas_datos ON partidos.idpartido = consultas_datos.partido
WHERE consultas_datos.respuesta LIKE 'No' 
GROUP BY nombrecompleto
HAVING AVG(consultas_datos.certidumbre)>0.6
ORDER BY AVG(consultas_datos.certidumbre) DESC;


