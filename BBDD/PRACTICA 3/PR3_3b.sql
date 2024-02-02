SELECT nombre FROM localidades
WHERE numerohabitantes > (
    SELECT numerohabitantes FROM localidades
    JOIN votantes ON localidades.idlocalidad = votantes.localidad
    WHERE votantes.dni LIKE (
    SELECT votantes.dni FROM votantes
    WHERE votantes.fechanacimiento = (
        SELECT MIN(fechanacimiento) FROM votantes
        WHERE fechanacimiento > (SELECT MIN(fechanacimiento) FROM votantes)
        )
    )
);