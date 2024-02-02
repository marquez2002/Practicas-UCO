SET SERVEROUTPUT ON;

DECLARE
    CURSOR votante is SELECT nombrecompleto FROM votantes WHERE SUBSTR(dni, -length(localidad+1), length(localidad+1)) LIKE localidad+1;
    contador NUMBER(8) := 0;
BEGIN
    FOR fila IN votante LOOP
        DBMS_OUTPUT.PUT_LINE(fila.nombrecompleto);
        contador := contador+1;
    END LOOP;
        DBMS_OUTPUT.PUT_LINE('Hay un total de '||contador||' votantes');
END;