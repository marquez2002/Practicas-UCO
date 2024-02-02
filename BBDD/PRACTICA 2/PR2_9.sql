select partidos.nombreCompleto, count(consultas_datos.partido) AS "conteo"
from consultas_datos, partidos
where consultas_datos.partido = partidos.idpartido
having count(consultas_datos.partido)>10
GROUP BY partidos.nombreCompleto;