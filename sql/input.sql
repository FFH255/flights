INSERT INTO town(id, name, country) VALUES (0, '', ''), (1, 'Рязань', 'Россия'),
	(2, 'Москва', 'Россия'), (3, 'Питер', 'Россия'), (4, 'Валенсия', 'Испания'),
	(5, 'Барселона', 'Испания'), (6, 'Дубай', 'АОЭ'), (7, 'Любляна', 'Словения');
	
INSERT INTO airplane(id, model, seats) VALUES (0, '', 0), (1, 'Туполев Ту-134', 80),
	(2, 'Туполев Ту-134', 80), (3, 'Туполев Ту-134', 80), (4, 'Туполев Ту-154 ', 180),
	(5, 'Туполев Ту-154 ', 180), (6, 'Сухой Суперджет-100', 100);

INSERT INTO flight(id, date, from_town_id, to_town_id, airplane_id, ticket_price, reserved_tickets)
	VALUES (0, CURRENT_DATE, 0, 0, 0, 0, 0),
	 (1, CURRENT_DATE, 1, 2, 1, 5000, 0),
	 (2, CURRENT_DATE, 3, 4, 5, 500, 0),
	 (3, CURRENT_DATE, 3, 4, 5, 500, 0);
	 
CALL reserve_ticket(1);
CALL reserve_ticket(2);
CALL reserve_ticket(3);

SELECT * FROM town;
SELECT * FROM airplane;

SELECT * FROM flight_view;

CALL update_flight_view(1, '2023-05-21', 'Москва', 'Рязань', 'Туполев Ту-134', 500);

SELECT * FROM get_schedule_view();

SELECT * FROM get_filtered_schedule_view('2023-05-24', 'Москва', 'Валенсия');

SELECT * FROM flight order by id;

SELECT * FROM town;

SELECT * FROM schedule_view;

DELETE FROM ticket;

DELETE FROM flight;

SELECT * FROM ticket;
  
select * from get_tickets();

CALL reserve_ticket((random() * 100)::int);

INSERT INTO flight (date, from_town_id, to_town_id, airplane_id, ticket_price, reserved_tickets)
SELECT
    current_date + (random() * interval '365 days') AS date,
    (random() * (SELECT max(id) FROM town))::int AS from_town_id,
    (random() * (SELECT max(id) FROM town))::int AS to_town_id,
    (random() * (SELECT max(id) FROM airplane))::int AS airplane_id,
    (random() * 1000)::int AS ticket_price,
    (random() * 100)::int AS reserved_tickets
FROM generate_series(1, 1000);

DO $$
DECLARE 
	i INT := 1;
	f_id INT;
	d DATE;
BEGIN
	WHILE i <= 1000 LOOP
		f_id := (random() * 1000)::int;
		d := current_date + (random() * interval '365 days');
		INSERT INTO ticket (flight_id, booking_date)
        VALUES (f_id, d);
		i := i + 1;
	END LOOP;
END $$;

DO $$
DECLARE
	i INT := 1;
	n VARCHAR;
	c VARCHAR;
BEGIN
	WHILE i <= 1000 LOOP
		n := (random() * 1000)::varchar;
		c := (random() * 1000)::varchar;
		INSERT INTO town(name, country)
			VALUES(n, c);
		i := i +1;
	END LOOP;
END $$;

EXPLAIN SELECT COUNT(*) AS reserved_tickets
					FROM ticket t
					GROUP BY (t.flight_id) 
					HAVING t.flight_id = 100 -- INDEX ONLY SCAN USING idx_ticket_flight_id on ticket
					

EXPLAIN INSERT INTO town(name, country) VALUES('3', '2');

select * from town where country = '2' AND name = '2'

EXPLAIN SELECT * 
FROM flight
WHERE id = 123; --INDEX SCAN USING idx_flight_id on flight

EXPLAIN SELECT f.id,  -- INDEX SCAN USING idx_town_id on town
		f.date, 
		tf.name, 
		tt.name,
		a.model,
		f.ticket_price,
		f.reserved_tickets,
		a.seats,
		CASE WHEN CURRENT_DATE = f.date THEN 'занят'
			 WHEN CURRENT_DATE < f.date THEN 'ожидает'
		 	 WHEN CURRENT_DATE > f.date THEN 'завершен' END
	FROM flight f
	INNER JOIN town tf
	ON f.from_town_id = tf.id
	INNER JOIN town tt
	ON f.to_town_id = tt.id
	INNER JOIN airplane a
	ON f.airplane_id = a.id
	ORDER BY (f.date) ASC
	
	
	
	

