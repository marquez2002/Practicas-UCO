select partidos.idpartido, count(consultas_datos.partido) AS "conteo"
from consultas_datos, partidos
where consultas_datos.partido = partidos.idpartido
GROUP BY partidos.idpartido;