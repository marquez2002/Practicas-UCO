select partidos.idpartido AS "PARTIDO", count(consultas_datos.partido) AS "COUNT(PARTIDO)"
from consultas_datos, partidos
where consultas_datos.partido = partidos.idpartido
GROUP BY partidos.idpartido;