SELECT nombre FROM localidades
LEFT JOIN votantes ON votantes.localidad = localidades.idlocalidad
WHERE numerohabitantes > (
    SELECT numerohabitantes FROM votantes
    WHERE MIN(fechanacimiento) != (
        SELECT MIN(fechanacimiento) FROM votantes)
    );