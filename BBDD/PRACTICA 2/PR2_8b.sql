SELECT nombrecompleto, COUNT(consultas.votante) "CONSULTAS" FROM votantes
JOIN consultas ON votantes.dni = consultas.votante
GROUP BY nombrecompleto
HAVING COUNT(consultas.votante)>3
ORDER BY count(evento) ASC;
