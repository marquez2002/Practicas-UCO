SELECT nombrecompleto, AVG(consultas_datos.certidumbre) AS "Certidumbre" FROM votantes
JOIN consultas ON votantes.dni = consultas.votante
JOIN consultas_datos ON consultas.idconsulta = consultas_datos.consulta
WHERE consultas_datos.respuesta LIKE 'Si' 
GROUP BY nombrecompleto
HAVING AVG(consultas_datos.certidumbre)>0.5 AND AVG(consultas_datos.certidumbre)<0.8
ORDER BY nombrecompleto;

