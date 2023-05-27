CREATE OR REPLACE VIEW flight_view(id, date, "from", "to", airplane, price, reserved_tickets, all_tickets, status, last_updated) AS ( -- CASE
	SELECT f.id, 
		f.date, 
		tf.name, 
		tt.name,
		a.model,
		f.ticket_price,
		f.reserved_tickets,
		a.seats,
		CASE WHEN CURRENT_DATE = f.date THEN 'занят'
			 WHEN CURRENT_DATE < f.date THEN 'ожидает'
		 	 WHEN CURRENT_DATE > f.date THEN 'завершен' END,
		f.last_updated
	FROM flight f
	INNER JOIN town tf
	ON f.from_town_id = tf.id
	INNER JOIN town tt
	ON f.to_town_id = tt.id
	INNER JOIN airplane a
	ON f.airplane_id = a.id
	ORDER BY (f.date) ASC);
	
-- instead of insert on flight_view

CREATE OR REPLACE FUNCTION flight_view_instead_of_insert() 
RETURNS TRIGGER 
LANGUAGE plpgsql AS $$
DECLARE 
	ft_id int;
	tt_id int;
	a_id int;
BEGIN
	SELECT id 
		INTO ft_id
		FROM town
		WHERE name = NEW."from";
	SELECT id 
		INTO tt_id
		FROM town
		WHERE name = NEW."to";
	SELECT MIN(id)
		INTO a_id
		FROM (SELECT id
	  	FROM airplane 
	  	WHERE model = NEW.airplane) AS a;
		CALL insert_flight(NEW.date, ft_id, tt_id, a_id, NEW.price);
	RETURN NULL;
END;
$$;

CREATE OR REPLACE TRIGGER flight_view_insert_trigger
INSTEAD OF INSERT
ON flight_view
FOR EACH ROW 
EXECUTE PROCEDURE flight_view_instead_of_insert();

-- instead of update trigger on flight_view

CREATE OR REPLACE FUNCTION flight_view_instead_of_update()
RETURNS TRIGGER
LANGUAGE plpgsql AS $$
DECLARE
	a_id int;
	tf_id int;
	tt_id int;
BEGIN
	IF NEW.airplane != OLD.airplane THEN
		SELECT MIN(id)
			INTO a_id
			FROM (SELECT id
	  		FROM airplane 
	  		WHERE model = NEW.airplane) AS a;
	END IF;
	IF NEW."from" != OLD."from" THEN
		SELECT id
			INTO tf_id
			FROM town
			WHERE name = NEW."from";
	END IF;
	IF NEW."to" != OLD."to" THEN
		SELECT id 
			INTO tt_id
			FROM town
			WHERE name = NEW."to";
	END IF;
	UPDATE flight SET 
		date = COALESCE(NEW.date, flight.date),
		airplane_id = COALESCE(a_id, flight.airplane_id),
		from_town_id = COALESCE(tf_id, flight.from_town_id),
		to_town_id = COALESCE(tt_id, flight.to_town_id),
		ticket_price = COALESCE(NEW.price, flight.ticket_price)
	WHERE id = NEW.id;
	RETURN NULL;
END;
$$;

CREATE OR REPLACE TRIGGER flight_view_update_trigger
INSTEAD OF UPDATE
ON flight_view
FOR EACH ROW 
EXECUTE PROCEDURE flight_view_instead_of_update();

-- instead of delete trigger on flight_view

CREATE OR REPLACE FUNCTION flight_view_instead_of_delete()
RETURNS TRIGGER
LANGUAGE plpgsql AS $$
BEGIN
	DELETE FROM flight
		WHERE id = OLD.id;
	RETURN NULL;
END;
$$;

CREATE OR REPLACE TRIGGER flight_view_delete_trigger
INSTEAD OF DELETE
ON flight_view
FOR EACH ROW
EXECUTE PROCEDURE flight_view_instead_of_delete();

--select

CREATE OR REPLACE FUNCTION select_flight_view()
RETURNS SETOF flight_view
LANGUAGE SQL AS $$
	SELECT * 
	FROM flight_view
	WHERE id != 0
	ORDER BY (date);
$$;

CREATE OR REPLACE FUNCTION select_flight_view_by_id(f_id int)
RETURNS SETOF flight_view
LANGUAGE SQL AS $$
	SELECT * 
	FROM flight_view
	WHERE id = f_id;
$$;

-- update 

CREATE OR REPLACE PROCEDURE update_flight_view(f_id int, d date, ft varchar, tt varchar, a varchar, t_price int)
LANGUAGE plpgsql AS $$
BEGIN
	UPDATE flight_view
	SET date = d, "from" = ft, "to" = tt, airplane = a, price = t_price
	WHERE id = f_id;
END;
$$;

--inseft

CREATE OR REPLACE PROCEDURE insert_flight_view(d date, ft varchar, tt varchar, a varchar, p int)
LANGUAGE plpgsql AS $$
BEGIN
INSERT INTO flight_view(date, "from", "to", airplane, price)
	VALUES(d, ft, tt, a, p);
END;
$$;

--delete

CREATE OR REPLACE PROCEDURE delete_flight_view(f_id int)
LANGUAGE plpgsql AS $$
BEGIN
DELETE FROM flight_view
WHERE id = f_id;
END;
$$;