SELECT votantes.nombrecompleto, AVG(consultas_datos.certidumbre) FROM votantes
LEFT JOIN consultas ON consultas.votante = votantes.dni
LEFT JOIN consultas_datos ON consultas_datos.consulta = consultas.idconsulta
WHERE consultas_datos.respuesta LIKE 'Si' 
GROUP BY nombrecompleto
HAVING AVG(consultas_datos.certidumbre) < 0.8 AND AVG(consultas_datos.certidumbre) > 0.5
ORDER BY nombrecompleto;

