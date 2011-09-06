/* $Id$ */

#include "postgres.h"

#include "access/heapam.h"
#include "access/htup.h"
#include "catalog/pg_type.h"
#include "funcapi.h"
#include "utils/lsyscache.h"
#include "utils/typcache.h"
#include "utils/array.h"


PG_MODULE_MAGIC;


PG_FUNCTION_INFO_V1(record_colnames);
Datum record_colnames(PG_FUNCTION_ARGS);
Datum
record_colnames(PG_FUNCTION_ARGS)
{
	HeapTupleHeader rec;
	Datum *d;
	ArrayType *a;
	int i,j;
	Oid	tupType;
	int32 tupTypmod;
	TupleDesc tupdesc;
	int	ncolumns;

	if (PG_ARGISNULL(0))
	{
		Oid	argtype = get_fn_expr_argtype(fcinfo->flinfo, 0);

		/*
		 * have no tuple to look at, so the only source of type info is the
		 * argtype. The lookup_rowtype_tupdesc call below will error out if we
		 * don't have a known composite type oid here.
		 */
		tupType = argtype;
		tupTypmod = -1;

		rec = NULL;
	}
	else
	{
		rec = PG_GETARG_HEAPTUPLEHEADER(0);

		/* Extract type info from the tuple itself */
		tupType = HeapTupleHeaderGetTypeId(rec);
		tupTypmod = HeapTupleHeaderGetTypMod(rec);
	}

	tupdesc = lookup_rowtype_tupdesc(tupType, tupTypmod);
	ncolumns = tupdesc->natts;

	/* 0 columns is possible but rare */

	if (ncolumns == 0)
	{
		a = construct_empty_array(NAMEOID);
        ReleaseTupleDesc(tupdesc);
		PG_RETURN_POINTER(a);
	}

	d = (Datum *) palloc(sizeof(Datum) * ncolumns);

	for (i = 0, j = 0; i < ncolumns; ++i)
	{
		/* Ignore dropped columns in datatype */
		if (tupdesc->attrs[i]->attisdropped)
			continue;

		d[j++] = NameGetDatum(&(tupdesc->attrs[i]->attname));
	}

	a = construct_array(d, j,
						NAMEOID, NAMEDATALEN, false, 'c');

	ReleaseTupleDesc(tupdesc);

	PG_RETURN_POINTER(a);
}
