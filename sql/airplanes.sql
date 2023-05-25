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