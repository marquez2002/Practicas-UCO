SELECT dni, COUNT(votante) FROM votantes
JOIN consultas ON votantes.dni = consultas.votante
GROUP BY dni
ORDER BY COUNT(votante) DESC;

