SELECT SUBSTR(nombrecompleto, 1, INSTR(nombrecompleto, ' ')) AS Nombre, localidades.nombre AS Localidad, provincias.nombre AS Provincia FROM votantes
JOIN localidades ON localidades.idlocalidad = votantes.localidad
JOIN provincias ON provincias.idprovincia = localidades.provincia
WHERE votantes.localidad = 1 OR votantes.localidad = 3 OR votantes.localidad = 9;