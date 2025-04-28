CREATE OR REPLACE FUNCTION colnames(record) RETURNS name[] LANGUAGE C STABLE
AS 'colnames','record_colnames';
