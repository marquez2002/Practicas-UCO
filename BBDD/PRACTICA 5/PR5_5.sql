SET SERVEROUTPUT ON;

DECLARE
    CURSOR dnis IS SELECT dni FROM votantes ORDER BY dni DESC;
    dniAnterior votantes.dni%TYPE;
BEGIN
    FOR dniActual IN dnis LOOP
        IF dniAnterior IS NULL THEN
            dniAnterior := dniActual.dni;
        ELSE 
            DBMS_OUTPUT.PUT_LINE(dniAnterior ||' antes ' || dniActual.dni);
            dniAnterior := dniActual.dni;
        END IF;
    END LOOP;
        DBMS_OUTPUT.PUT_LINE('El menor es: '|| dniAnterior);
END;