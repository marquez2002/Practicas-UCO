SET SERVEROUTPUT ON;

DECLARE
    nombre votantes.nombrecompleto%TYPE;
    correo votantes.email%TYPE;
BEGIN
    SELECT nombrecompleto, SUBSTR(email, 1, INSTR(email, '@')) INTO nombre, correo FROM votantes WHERE fechanacimiento = (SELECT MIN(fechanacimiento) FROM votantes);
    DBMS_OUTPUT.PUT_LINE(nombre||' - EMAIL: '||correo||'uco.es');
    SELECT nombrecompleto, SUBSTR(email, 1, INSTR(email, '@')) INTO nombre, correo FROM votantes WHERE fechanacimiento = (SELECT MAX(fechanacimiento) FROM votantes);
    DBMS_OUTPUT.PUT_LINE(nombre||' - EMAIL: '||correo||'uco.es');
END;
