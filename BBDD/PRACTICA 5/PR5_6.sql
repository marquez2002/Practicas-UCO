SET SERVEROUTPUT ON;

DECLARE
    CURSOR votantes IS SELECT dni, COUNT(votante) nveces FROM votantes 
        LEFT JOIN consultas ON votantes.dni = consultas.votante
        GROUP BY dni 
        HAVING COUNT(votante) > (SELECT AVG(COUNT(votante)) FROM consultas GROUP BY votante)
    ORDER BY COUNT(votante) DESC;
BEGIN
    FOR fila IN votantes LOOP
        DBMS_OUTPUT.PUT_LINE(fila.dni ||'  ha participado veces ' || fila.nveces);
    END LOOP;
END;