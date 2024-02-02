SELECT nombrecompleto FROM votantes
WHERE SUBSTR(votantes.dni, -1,1) LIKE (votantes.localidad+1);