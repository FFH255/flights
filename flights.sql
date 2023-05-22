-- Бронирование билета

CREATE OR REPLACE PROCEDURE reserve_ticket(f_id int)
LANGUAGE plpgsql AS $$
DECLARE 
	have_free_seats bool;
BEGIN
	SELECT f.reserved_tickets < (SELECT seats 
								 FROM airplane 
								 WHERE id = f.airplane_id
								) -- Корреляция1
		INTO have_free_seats 
		FROM flight f
		WHERE id = f_id;
	IF have_free_seats THEN 
		UPDATE flight 
			SET reserved_tickets = reserved_tickets + 1 
			WHERE id = f_id;
		CALL insert_ticket(f_id);
		COMMIT;
	ELSE 
		ROLLBACK;
	END IF;
END;
$$;

SELECT 
FROM (SELECT f.reserved_tickets
	  FROM flight f
	  WHERE id = 2) AS f

-- Возврат билета

CREATE OR REPLACE PROCEDURE refund_ticket(t_id int)
LANGUAGE plpgsql AS $$
BEGIN
	IF (EXISTS (SELECT 1 FROM ticket WHERE id = t_id)) THEN
		UPDATE flight 
			SET reserved_tickets = reserved_tickets - 1
			WHERE id  = (SELECT flight_id FROM ticket 
							WHERE id = t_id);
		CALL delete_ticket(t_id);
		COMMIT;
	ELSE 
		ROLLBACK;
	END IF;
END;
$$;
	
--[reminder] booking tickets that are ongoing with ANY keyword	

CREATE OR REPLACE FUNCTION select_airplane_by_model_and_date(m varchar, d date)
RETURNS airplane
LANGUAGE SQL AS $$
SELECT * -- Два вложенных запроса в where, all, min
FROM airplane
WHERE id = (SELECT MIN(id)
			FROM airplane
			WHERE id != ALL (SELECT airplane_id
							 FROM flight
							 WHERE date = d)
			AND model = m);
$$; 

CREATE OR REPLACE FUNCTION select_available_airplane_models(d date)
RETURNS TABLE (model VARCHAR)
LANGUAGE SQL AS $$
SELECT model -- Вложенный запрос в where, вложенный запрос в from, all
FROM (SELECT model 
	  FROM airplane 
	  WHERE id != ALL(SELECT airplane_id 
					  FROM flight
					  WHERE date = d)) AS a
GROUP BY(model)
$$;

--[reminder] add ordering to selectors




