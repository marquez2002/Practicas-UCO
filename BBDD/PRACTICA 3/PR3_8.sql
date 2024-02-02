SELECT dni FROM votantes
JOIN consultas ON votantes.dni = consultas.votante
WHERE dni NOT LIKE (
    SELECT dni FROM votantes
    WHERE fechanacimiento = (
        SELECT MIN(fechanacimiento) FROM votantes
        WHERE fechanacimiento > (SELECT MIN(fechanacimiento) FROM votantes)
    )
)
GROUP BY dni
ORDER BY COUNT(votante) DESC;

