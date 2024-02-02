SELECT nombrecompleto FROM votantes
LEFT JOIN consultas ON votantes.dni = consultas.votante
GROUP BY nombrecompleto
HAVING COUNT(votante) > (
    SELECT AVG(COUNT(votante)) FROM consultas
    GROUP BY votante
);
