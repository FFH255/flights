SELECT * FROM pg_roles;

CREATE ROLE user_group;

CREATE USER "user" WITH PASSWORD 'user';

GRANT user_group TO "user";

GRANT SELECT ON schedule_view TO user_group;
GRANT SELECT, INSERT, DELETE ON ticket TO user_group;
GRANT ALL ON SEQUENCE ticket_id_seq TO user_group;
GRANT SELECT ON town TO user_group;
GRANT SELECT, UPDATE ON flight TO user_group;
GRANT SELECT ON airplane TO user_group;