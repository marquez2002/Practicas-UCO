SET SERVEROUTPUT ON;

DECLARE
    CURSOR votantes is SELECT nombrecompleto, nombre FROM votantes, localidades WHERE localidades.idlocalidad LIKE decode(votantes.localidad, 1, 9, 2, 9, 3, 9, votantes.localidad);
    contador NUMBER(8) := 0;
BEGIN
    FOR fila IN votantes LOOP
        DBMS_OUTPUT.PUT_LINE(fila.nombrecompleto || ' es de ' || fila.nombre);
        IF fila.nombre LIKE 'Madrid' THEN
            contador := contador+1;
        END IF;
        contador := contador+1;
    END LOOP;
        DBMS_OUTPUT.PUT_LINE('Hay un total de '||contador||' votantes');
END;