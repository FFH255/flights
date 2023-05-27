SELECT * FROM pg_roles;

-- user

CREATE ROLE user_group;

CREATE USER "user" WITH PASSWORD 'user';

GRANT user_group TO "user";

GRANT SELECT ON schedule_view TO user_group;
GRANT SELECT, INSERT, DELETE ON ticket TO user_group;
GRANT ALL ON SEQUENCE ticket_id_seq TO user_group;
GRANT SELECT ON town TO user_group;
GRANT SELECT, UPDATE ON flight TO user_group;
GRANT SELECT ON airplane TO user_group;



--admin

CREATE ROLE admin_group;
CREATE USER "admin" WITH PASSWORD 'admin';
GRANT admin_group TO "admin";

GRANT SELECT, UPDATE, INSERT, DELETE ON 
	town, 
	airplane, 
	flight, 
	ticket, 
	schedule_view, 
	flight_view 
TO admin_group;

GRANT ALL ON SEQUENCE
	town_id_seq,
	airplane_id_seq,
	flight_id_seq,
	ticket_id_seq
TO admin_group;