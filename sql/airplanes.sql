CREATE OR REPLACE FUNCTION select_available_airplane_models(d date)
RETURNS TABLE (model VARCHAR)
LANGUAGE SQL AS $$
SELECT model -- Вложенный запрос в where, вложенный запрос в from, all
FROM (SELECT model 
	  FROM airplane 
	  WHERE id != ALL(SELECT airplane_id 
					  FROM flight
					  WHERE date = d)
	 AND id != 0) AS a
GROUP BY(model)
$$; 