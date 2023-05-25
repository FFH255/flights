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

CREATE OR REPLACE FUNCTION get_tickets()
RETURNS TABLE (
	id INT,
	flight_date DATE,
	"from" VARCHAR,
	"to" VARCHAR,
	price INT,
	booking_date DATE
)
LANGUAGE SQL AS $$
SELECT --корреляция
  t.id AS id,
  f.date AS flight_date,
  (SELECT name FROM town WHERE id = f.from_town_id) AS "from",
  (SELECT name FROM town WHERE id = f.to_town_id) AS "to",
  f.ticket_price AS price,
  t.booking_date
FROM
  ticket t, flight f
WHERE
  t.flight_id = f.id
ORDER BY (f.date);
$$;