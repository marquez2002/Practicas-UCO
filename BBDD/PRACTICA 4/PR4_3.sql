SET SERVEROUTPUT ON;

DECLARE
    correo votantes.email%TYPE;
    nombre votantes.nombrecompleto%TYPE;
BEGIN
    SELECT SUBSTR(nombrecompleto, 1, INSTR(nombrecompleto, ' ')) INTO nombre FROM votantes WHERE dni = 30983712;
    SELECT email INTO correo FROM votantes WHERE dni = 30983712;
    DBMS_OUTPUT.PUT_LINE(nombre || 'con correo: ' || correo);
END;
