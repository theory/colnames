CREATE FUNCTION colnames(record) RETURNS name[] LANGUAGE C STABLE
AS '$libdir/colnames','record_colnames';
