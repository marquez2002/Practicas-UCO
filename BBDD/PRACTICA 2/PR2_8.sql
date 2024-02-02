select partidos.nombreCompleto from consultas_datos, partidos
where consultas_datos.partido=partidos.idpartido
having count(consultas_datos.partido)>10
group by partidos.nombreCompleto;