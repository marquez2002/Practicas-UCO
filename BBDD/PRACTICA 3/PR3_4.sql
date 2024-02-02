SELECT dni FROM votantes
WHERE fechanacimiento = (SELECT MIN(fechanacimiento) FROM votantes);
