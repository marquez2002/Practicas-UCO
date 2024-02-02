SET SERVEROUTPUT ON;

DECLARE
    nombre votantes.nombrecompleto%TYPE;
    dni votantes.dni%TYPE;
BEGIN
    SELECT nombrecompleto, dni INTO nombre, dni FROM votantes WHERE fechanacimiento = (SELECT MIN(fechanacimiento) FROM votantes);
    DBMS_OUTPUT.PUT_LINE('El señor ' ||nombre||' con dni '||dni||' es el votante mas longuevo');
END;
