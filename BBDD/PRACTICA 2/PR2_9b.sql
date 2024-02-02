SELECT nombrecompleto, localidades.nombre "Localidad" FROM votantes
JOIN localidades ON votantes.localidad = localidades.idlocalidad
WHERE localidades.numerohabitantes > 300000
ORDER BY nombrecompleto ASC;
