SELECT votantes.nombrecompleto, localidades.nombre FROM votantes, localidades
where localidades.numerohabitantes>'300000' and votantes.localidad=localidades.idlocalidad;