SELECT votantes.nombrecompleto, provincias.comunidad FROM votantes, provincias, localidades
where localidades.numerohabitantes>'300000' and localidades.idlocalidad=votantes.localidad and localidades.provincia=provincias.idprovincia;