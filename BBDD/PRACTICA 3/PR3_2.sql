SELECT votantes.nombrecompleto, localidades.nombre FROM votantes
JOIN localidades ON localidades.idlocalidad = votantes.localidad
WHERE votantes.localidad IN (1,2,3);