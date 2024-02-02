SET SERVEROUTPUT ON;

DECLARE
    apellido1 votantes.nombrecompleto%TYPE;
    apellido2 votantes.nombrecompleto%TYPE;
    apellido3 votantes.nombrecompleto%TYPE;
BEGIN
    SELECT SUBSTR(SUBSTR(nombrecompleto, INSTR(nombrecompleto, ' ')), INSTR(nombrecompleto, ' ')) INTO apellido1 FROM votantes WHERE fechanacimiento = (SELECT MIN(fechanacimiento) FROM votantes);
    SELECT SUBSTR(nombrecompleto, INSTR(nombrecompleto, ' ')) INTO apellido2 FROM votantes WHERE fechanacimiento = (SELECT MIN(fechanacimiento) FROM votantes WHERE fechanacimiento != (SELECT MIN(fechanacimiento) FROM votantes));
    DBMS_OUTPUT.PUT_LINE('Juan' || apellido2 || ' '|| apellido1);
END;
