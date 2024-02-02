SELECT dni, COUNT(votante) FROM votantes
JOIN consultas ON votantes.dni = consultas.votante
HAVING COUNT(votante) > (SELECT AVG(COUNT(votante)) FROM consultas
                        GROUP BY votante
                        )
GROUP BY dni
ORDER BY (COUNT(votante)) DESC;
