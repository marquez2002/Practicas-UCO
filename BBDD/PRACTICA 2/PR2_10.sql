select partidos.nombreCompleto, count(consultas_datos.partido) AS "Conteo"
from consultas_datos, partidos
where consultas_datos.partido=partidos.idpartido and consultas_datos.certidumbre>0.8 and consultas_datos.respuesta='Si'
group by partidos.nombreCompleto;