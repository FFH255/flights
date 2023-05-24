CREATE OR REPLACE VIEW schedule_view
AS (SELECT f.id, f.date, ft.name as "from", tt.name AS "to" -- Корреляция, having, group by, агрегатная функция
	FROM flight f
	INNER JOIN airplane a
	ON f.airplane_id = a.id
	INNER JOIN town tt
	ON f.to_town_id = tt.id
	INNER JOIN town ft
	ON f.from_town_id = ft.id
	WHERE (COALESCE((SELECT COUNT(*) AS reserved_tickets
					FROM ticket t
					GROUP BY (t.flight_id) 
					HAVING t.flight_id = f.id), 0)) < a.seats
	AND f.date >= CURRENT_DATE);
	
CREATE OR REPLACE FUNCTION get_filtered_schedule_view(d date, from_town varchar, to_town varchar)
RETURNS SETOF schedule_view
LANGUAGE SQL AS $$
	SELECT * 
		FROM schedule_view
		WHERE date = d
		AND "from" = from_town
		AND "to" = to_town;
$$;

CREATE OR REPLACE FUNCTION get_schedule_view()
RETURNS SETOF schedule_view
LANGUAGE SQL AS $$
	SELECT * 
	FROM schedule_view;
$$;