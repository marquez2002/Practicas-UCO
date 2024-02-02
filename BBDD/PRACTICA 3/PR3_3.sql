SELECT partidos.siglas FROM partidos
WHERE idpartido = ANY (
    SELECT partido FROM eventos_resultados
    GROUP BY partido
    HAVING COUNT (*) = (
        SELECT MAX(participaciones) FROM (
            SELECT partido, COUNT (*) participaciones FROM eventos_resultados
            GROUP BY PARTIDO
            )
        )
    );
