\set ECHO 0
BEGIN;
\set QUIET 1
\i sql/colnames.sql

SELECT colnames( ROW(1, 3, 'foo') );
SELECT colnames( ROW(c.*)::pg_collation ) FROM pg_collation c LIMIT 1;
SELECT colnames( NULL::pg_collation );

CREATE TYPE foo AS (id int, name text);
SELECT colnames( row(1, 'foo')::foo );

CREATE TYPE bar AS ("The Id" int, "My Name" text);
SELECT colnames( row(1, 'bar')::bar );

ROLLBACK;
