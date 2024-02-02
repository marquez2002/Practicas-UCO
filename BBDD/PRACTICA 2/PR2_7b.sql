SELECT votante FROM consultas
GROUP BY votante
HAVING COUNT(votante) > 3;