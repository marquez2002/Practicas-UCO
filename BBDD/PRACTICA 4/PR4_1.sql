set serveroutput on
DECLARE
    fecha_actual DATE;
BEGIN
    fecha_actual := SYSDATE;
    DBMS_OUTPUT.PUT_LINE('Hola Mundo, hoy es dia ' || to_char(fecha_actual));
END;