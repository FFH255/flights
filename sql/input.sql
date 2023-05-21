INSERT INTO town(id, name, country) VALUES (1, 'Рязань', 'Россия'),
	(2, 'Москва', 'Россия'), (3, 'Питер', 'Россия'), (4, 'Валенсия', 'Испания'),
	(5, 'Барселона', 'Испания'), (6, 'Дубай', 'АОЭ'), (7, 'Любляна', 'Словения');

INSERT INTO airplane(id, model, seats) VALUES (1, 'Туполев Ту-134', 80),
	(2, 'Туполев Ту-134', 80), (3, 'Туполев Ту-134', 80), (4, 'Туполев Ту-154 ', 180),
	(5, 'Туполев Ту-154 ', 180), (6, 'Сухой Суперджет-100', 100);

INSERT INTO flight(id, date, from_town_id, to_town_id, airplane_id, ticket_price, reserved_tickets)
	VALUES (1, CURRENT_DATE, 1, 2, 1, 5000, 0),
	 (2, CURRENT_DATE, 3, 4, 5, 500, 0),
	 (3, CURRENT_DATE, 3, 4, 5, 500, 0);
	 
CALL reserve_ticket(1);
CALL reserve_ticket(2);
CALL reserve_ticket(3);

SELECT * FROM flight_view;