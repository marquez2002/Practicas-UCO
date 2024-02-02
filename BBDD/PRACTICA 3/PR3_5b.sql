SELECT nombrecompleto, localidad, DECODE(SIGN(18-trunc((SYSDATE-fechanacimiento)/365)), 1 , 'Menor de EDAD', 'Mayor de EDAD') AS "Mayoria de Edad" FROM votantes
WHERE localidad LIKE '2' OR localidad LIKE '4' OR localidad LIKE '8';