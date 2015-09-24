/*
 * contrib/decimal/decimal.c
 */
#include "decimal.h"
#ifdef PG_MODULE_MAGIC
PG_MODULE_MAGIC;
#endif

#ifndef USE_FLOAT8_BYVAL
#error pgdecimal uses 64 bit datum.
#endif

Datum
Decimal64GetDatum(PGDecimal64 X)
{
    union
    {
        PGDecimal64	value;
        int64		retval;
    }			myunion;

    myunion.value = X;
    return SET_8_BYTES(myunion.retval);
}

PGDecimal64
DatumGetDecimal64(Datum X)
{
    union
    {
        int64		value;
        PGDecimal64	retval;
    }			myunion;

    myunion.value = GET_8_BYTES(X);
    return myunion.retval;
}

