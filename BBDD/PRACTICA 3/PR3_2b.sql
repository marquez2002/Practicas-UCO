SELECT CONCAT(CONCAT(a.nombre, ' va antes que '), b.nombre) AS Orden FROM localidades a, localidades b
WHERE a.idlocalidad = b.idlocalidad-1;