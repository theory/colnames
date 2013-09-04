\set ECHO 0
BEGIN;
\set QUIET 1
\i sql/colnames.sql

SELECT colnames( ROW(1, 3, 'foo') );
SELECT colnames( ROW(c.*)::pg_description ) FROM pg_description c LIMIT 1;
SELECT colnames( NULL::pg_description );

CREATE TYPE foo AS (id int, name text);
SELECT colnames( row(1, 'foo')::foo );

CREATE TYPE bar AS ("The Id" int, "My Name" text);
SELECT colnames( row(1, 'bar')::bar );

-- Empty types allowed on 9.1 and higher.
CREATE TYPE empty AS ();
SELECT colnames( row()::empty );

ROLLBACK;
