CREATE TABLE town (
	id SERIAL PRIMARY KEY,
	name VARCHAR(255) NOT NULL,
	country VARCHAR(128) NOT NULL,
	UNIQUE(name, country)
);

CREATE TABLE airplane (
	id SERIAL PRIMARY KEY,
	model VARCHAR(32) NOT NULL,
	seats SMALLINT NOT NULL
);

CREATE TABLE flight (
	id SERIAL PRIMARY KEY,
	date DATE NOT NULL,
	from_town_id INT NOT NULL DEFAULT 0,
	to_town_id INT NOT NULL DEFAULT 0,
	airplane_id INT NOT NULL DEFAULT 0,
	ticket_price INT NOT NULL
		CHECK (ticket_price >= 0),
	reserved_tickets SMALLINT NOT NULL 
		CHECK (reserved_tickets >= 0),
	CONSTRAINT fk_from_town_id 
		FOREIGN KEY (from_town_id)
		REFERENCES town(id)
		ON DELETE SET DEFAULT,
	CONSTRAINT fk_to_town_id
		FOREIGN KEY (to_town_id)
		REFERENCES town(id)
		ON DELETE SET DEFAULT,
	CONSTRAINT fk_airplane_id
		FOREIGN KEY (airplane_id)
		REFERENCES airplane(id)
		ON DELETE SET DEFAULT
);

CREATE TABLE ticket (
	id SERIAL PRIMARY KEY,
	flight_id INT NOT NULL DEFAULT 0,
	booking_date DATE NOT NULL,
	CONSTRAINT fk_flight_id
		FOREIGN KEY (flight_id)
		REFERENCES flight(id)
		ON DELETE SET DEFAULT
);

DROP TABLE ticket CASCADE;
DROP TABLE flight CASCADE;
DROP TABLE town CASCADE;
DROP TABLE airplane CASCADE;

--TOWN

CREATE OR REPLACE FUNCTION select_towns()
RETURNS SETOF town
LANGUAGE SQL AS $$
	SELECT * 
	FROM town
	WHERE id != 0
	ORDER BY (name);
$$;

CREATE OR REPLACE FUNCTION select_town_by_id(t_id int)
RETURNS SETOF town
LANGUAGE SQL AS $$
	SELECT * 
	FROM town
	WHERE id = t_id;
$$;

CREATE PROCEDURE insert_town(n varchar(255), c varchar(128))
LANGUAGE plpgsql AS $$
BEGIN
	INSERT INTO town(name, country)
		VALUES (n, c);
END;
$$;

CREATE OR REPLACE PROCEDURE update_town(town_id int, town_name varchar, country_name varchar)
LANGUAGE plpgsql AS $$
BEGIN
	UPDATE town
		SET name = COALESCE(town_name, town.name),
			country = COALESCE(country_name, town.country)
		WHERE id = town_id;
END;
$$;

CREATE PROCEDURE delete_town(t_id int)
LANGUAGE plpgsql AS $$
BEGIN
	DELETE FROM town
		WHERE id = t_id;
END;
$$;

--AIRPLANE

CREATE OR REPLACE FUNCTION select_airplanes()
RETURNS SETOF airplane
LANGUAGE SQL AS $$
	SELECT * 
	FROM airplane
	WHERE id != 0
	ORDER BY (model);
$$;

CREATE OR REPLACE FUNCTION select_airplane_by_id(a_id int)
RETURNS SETOF airplane
LANGUAGE SQL AS $$
	SELECT * 
	FROM airplane
	WHERE id = a_id;
$$;

CREATE PROCEDURE insert_airplane(m varchar(32), s SMALLINT)
LANGUAGE plpgsql AS $$
BEGIN
	INSERT INTO airplane(model, seats)
		VALUES (m, s);
END;
$$;

CREATE OR REPLACE PROCEDURE update_airplane(airplane_id int, airplane_model varchar, airplane_seats smallint)
LANGUAGE plpgsql AS $$
BEGIN
	UPDATE airplane
		SET model = COALESCE(airplane_model, airplane.model),
			seats = COALESCE(airplane_seats, airplane.seats)
		WHERE id = airplane_id;
END;
$$;

CREATE PROCEDURE delete_airplane(a_id int)
LANGUAGE plpgsql AS $$
BEGIN
	DELETE FROM airplane
		WHERE id = a_id;
END;
$$;

--FLIGHT

CREATE OR REPLACE FUNCTION select_flights()
RETURNS SETOF flight
LANGUAGE SQL AS $$
	SELECT * 
	FROM flight
	WHERE id != 0
	ORDER BY (date);
$$;

CREATE OR REPLACE FUNCTION select_flight_by_id(f_id int)
RETURNS SETOF flight
LANGUAGE SQL AS $$
	SELECT * 
	FROM flight
	WHERE id = f_id;
$$;

CREATE PROCEDURE insert_flight(d date, ft_id int, tt_id int, a_id int, t_price int)
LANGUAGE plpgsql AS $$
BEGIN
	INSERT INTO flight(date, from_town_id, to_town_id, airplane_id, ticket_price, reserved_tickets)
		VALUES (d, ft_id, tt_id, a_id, t_price, 0);
END;
$$;

CREATE OR REPLACE PROCEDURE update_flight(
	f_id int, 
	new_date date, 
	new_from_town_id int, 
	new_to_town_id int,
	new_airplane_id int, 
	new_ticket_price money,
	new_reserved_tickets smallint
)
LANGUAGE plpgsql AS $$
BEGIN
	UPDATE flight f
		SET date = COALESCE(new_date, f.date),
			from_town_id = COALESCE(new_from_town_id, f.from_town_id),
			to_town_id = COALESCE(new_to_town_id, f.to_town_id),
			airplane_id = COALESCE(new_airplane_id, f.airplane_id),
			ticket_price = COALESCE(new_ticket_price, f.ticket_price),
			reserved_tickets = COALESCE(new_reserved_tickets, f.reserver_tickets)
		WHERE id = f_id;
END;
$$;

CREATE PROCEDURE delete_flight(f_id int)
LANGUAGE plpgsql AS $$
BEGIN
	DELETE FROM flight
		WHERE id = f_id;
END;
$$;

--TICKET

CREATE OR REPLACE FUNCTION select_tickets()
RETURNS SETOF ticket
LANGUAGE SQL AS $$
	SELECT * 
	FROM ticket
	WHERE id != 0
	ORDER BY (booking_date);
$$;

CREATE OR REPLACE FUNCTION select_ticket_by_id(t_id int)
RETURNS SETOF ticket
LANGUAGE SQL AS $$
	SELECT * 
	FROM ticket
	WHERE id = t_id;
$$;

CREATE PROCEDURE insert_ticket(f_id int)
LANGUAGE plpgsql AS $$
BEGIN
	INSERT INTO ticket(flight_id, booking_date)
		VALUES (f_id, CURRENT_DATE);
END;
$$;

CREATE OR REPLACE PROCEDURE update_ticket(new_flight_id int, new_booking_date date)
LANGUAGE plpgsql AS $$
BEGIN
	UPDATE ticket t
		SET flight_id = COALESCE(new_flight_id, t.flight_id),
			booking_date = COALESCE(new_booking_date, t.booking_date)
		WHERE id = airplane_id;
END;
$$;

CREATE PROCEDURE delete_ticket(t_id int)
LANGUAGE plpgsql AS $$
BEGIN
	DELETE FROM ticket
		WHERE id = t_id;
END;
$$;