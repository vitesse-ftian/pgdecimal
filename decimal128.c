#include "decimal.h"

// 
// Forward declarations.
//
Datum decimal128_in(PG_FUNCTION_ARGS);
Datum decimal128_out(PG_FUNCTION_ARGS);
Datum decimal128_add(PG_FUNCTION_ARGS);
Datum decimal128_sub(PG_FUNCTION_ARGS);
Datum decimal128_mul(PG_FUNCTION_ARGS);
Datum decimal128_div(PG_FUNCTION_ARGS);
Datum decimal128_uplus(PG_FUNCTION_ARGS);
Datum decimal128_uminus(PG_FUNCTION_ARGS);
Datum decimal128_abs(PG_FUNCTION_ARGS);
Datum decimal128_lt(PG_FUNCTION_ARGS);
Datum decimal128_le(PG_FUNCTION_ARGS);
Datum decimal128_gt(PG_FUNCTION_ARGS);
Datum decimal128_ge(PG_FUNCTION_ARGS);
Datum decimal128_eq(PG_FUNCTION_ARGS);
Datum decimal128_ne(PG_FUNCTION_ARGS);
Datum decimal128_cmp(PG_FUNCTION_ARGS);
Datum decimal128_hash(PG_FUNCTION_ARGS);
Datum decimal128_smaller(PG_FUNCTION_ARGS);
Datum decimal128_larger(PG_FUNCTION_ARGS);
Datum decimal128_inc(PG_FUNCTION_ARGS);
Datum decimal128_round(PG_FUNCTION_ARGS);
Datum decimal128_float4(PG_FUNCTION_ARGS);
Datum float4_decimal128(PG_FUNCTION_ARGS);
Datum decimal128_float8(PG_FUNCTION_ARGS);
Datum float8_decimal128(PG_FUNCTION_ARGS);;
Datum int4_decimal128(PG_FUNCTION_ARGS);
Datum int8_decimal128(PG_FUNCTION_ARGS);
Datum decimal128_numeric(PG_FUNCTION_ARGS);
Datum numeric_decimal128(PG_FUNCTION_ARGS);

PG_FUNCTION_INFO_V1(decimal128_in);
Datum decimal128_in(PG_FUNCTION_ARGS)
{
    char *s = PG_GETARG_CSTRING(0);
    DECLARE_PRET_128_WITH_CTXT(pret, DEC_INIT_DECIMAL128);

    decQuadFromString(pret, s, &dc); 
    DEC_CHK_STATUS(dc, DEC_STATUS_ALL, "invalid decimal128 syntax:\"%s\"", s);
    PG_RETURN_P_DECIMAL128(pret);
}

PG_FUNCTION_INFO_V1(decimal128_out);
Datum decimal128_out(PG_FUNCTION_ARGS)
{
    PGDecimal128 *pd = PG_GETARG_P_DECIMAL128(0);
    char *s = (char *) palloc(DECQUAD_String);
    if (!s) {
        elog(ERROR, "OOM");
    }
    
    decQuadToString(pd, s);
    PG_RETURN_CSTRING(s);
}

PG_FUNCTION_INFO_V1(decimal128_add); 
Datum decimal128_add(PG_FUNCTION_ARGS)
{
    PGDecimal128* pa = PG_GETARG_P_DECIMAL128(0);
    PGDecimal128* pb = PG_GETARG_P_DECIMAL128(1);
    DECLARE_PRET_128_WITH_CTXT(pret, DEC_INIT_DECIMAL128);

    decQuadAdd(pret, pa, pb, &dc); 
    DEC_CHK_STATUS(dc, DEC_STATUS_OFUF, "decimal128 overflow"); 
    PG_RETURN_P_DECIMAL128(pret);
}

PG_FUNCTION_INFO_V1(decimal128_sub); 
Datum decimal128_sub(PG_FUNCTION_ARGS)
{
    PGDecimal128* pa = PG_GETARG_P_DECIMAL128(0);
    PGDecimal128* pb = PG_GETARG_P_DECIMAL128(1);
    DECLARE_PRET_128_WITH_CTXT(pret, DEC_INIT_DECIMAL128);

    decQuadSubtract(pret, pa, pb, &dc); 
    DEC_CHK_STATUS(dc, DEC_STATUS_OFUF, "decimal128 overflow"); 
    PG_RETURN_P_DECIMAL128(pret);
}

PG_FUNCTION_INFO_V1(decimal128_mul); 
Datum decimal128_mul(PG_FUNCTION_ARGS)
{
    PGDecimal128* pa = PG_GETARG_P_DECIMAL128(0);
    PGDecimal128* pb = PG_GETARG_P_DECIMAL128(1);
    DECLARE_PRET_128_WITH_CTXT(pret, DEC_INIT_DECIMAL128);

    decQuadMultiply(pret, pa, pb, &dc); 
    DEC_CHK_STATUS(dc, DEC_STATUS_OFUF, "decimal128 overflow"); 
    PG_RETURN_P_DECIMAL128(pret);
}

PG_FUNCTION_INFO_V1(decimal128_div); 
Datum decimal128_div(PG_FUNCTION_ARGS)
{
    PGDecimal128* pa = PG_GETARG_P_DECIMAL128(0);
    PGDecimal128* pb = PG_GETARG_P_DECIMAL128(1);
    DECLARE_PRET_128_WITH_CTXT(pret, DEC_INIT_DECIMAL128);

    decQuadDivide(pret, pa, pb, &dc); 
    DEC_CHK_STATUS(dc, DEC_STATUS_DIV, "decimal128 division error"); 
    PG_RETURN_P_DECIMAL128(pret);
}

PG_FUNCTION_INFO_V1(decimal128_uplus); 
Datum decimal128_uplus(PG_FUNCTION_ARGS)
{
    PGDecimal128* pa = PG_GETARG_P_DECIMAL128(0);
    DECLARE_PRET_128_WITH_CTXT(pret, DEC_INIT_DECIMAL128);

    decQuadPlus(pret, pa, &dc); 
    DEC_CHK_STATUS(dc, DEC_STATUS_OFUF, "decimal128 overflow"); 
    PG_RETURN_P_DECIMAL128(pret);
}

PG_FUNCTION_INFO_V1(decimal128_uminus); 
Datum decimal128_uminus(PG_FUNCTION_ARGS)
{
    PGDecimal128* pa = PG_GETARG_P_DECIMAL128(0);
    DECLARE_PRET_128_WITH_CTXT(pret, DEC_INIT_DECIMAL128);

    decQuadMinus(pret, pa, &dc); 
    DEC_CHK_STATUS(dc, DEC_STATUS_OFUF, "decimal128 overflow"); 
    PG_RETURN_P_DECIMAL128(pret);
}

PG_FUNCTION_INFO_V1(decimal128_abs);
Datum decimal128_abs(PG_FUNCTION_ARGS)
{
    PGDecimal128* pa = PG_GETARG_P_DECIMAL128(0);
    DECLARE_PRET_128_WITH_CTXT(pret, DEC_INIT_DECIMAL128);

    decQuadAbs(pret, pa, &dc); 
    DEC_CHK_STATUS(dc, DEC_STATUS_OFUF, "decimal128 overflow"); 
    PG_RETURN_P_DECIMAL128(pret);
}


static int decimal128_cmp_internal(const PGDecimal128* a, const PGDecimal128* b)
{
    PGDecimal128 result;
    DECLARE_DEC_CTXT(DEC_INIT_DECIMAL128);
    decQuadCompare(&result, a, b, &dc);

    if (decQuadIsPositive(&result)) {
        return 1;
    } else if (decQuadIsZero(&result)) {
        return 0;
    } else if (decQuadIsNegative(&result)) {
        return -1;
    } else {
        elog(ERROR, "invalid decimal128 in compare");
    }
}

PG_FUNCTION_INFO_V1(decimal128_lt); 
Datum decimal128_lt(PG_FUNCTION_ARGS)
{
    PGDecimal128* pa = PG_GETARG_P_DECIMAL128(0);
    PGDecimal128* pb = PG_GETARG_P_DECIMAL128(1);
    int ret = decimal128_cmp_internal(pa, pb);
    PG_RETURN_BOOL(ret < 0); 
}

PG_FUNCTION_INFO_V1(decimal128_le); 
Datum decimal128_le(PG_FUNCTION_ARGS)
{
    PGDecimal128* pa = PG_GETARG_P_DECIMAL128(0);
    PGDecimal128* pb = PG_GETARG_P_DECIMAL128(1);
    int ret = decimal128_cmp_internal(pa, pb);
    PG_RETURN_BOOL(ret <= 0); 
}

PG_FUNCTION_INFO_V1(decimal128_gt); 
Datum decimal128_gt(PG_FUNCTION_ARGS)
{
    PGDecimal128* pa = PG_GETARG_P_DECIMAL128(0);
    PGDecimal128* pb = PG_GETARG_P_DECIMAL128(1);
    int ret = decimal128_cmp_internal(pa, pb);
    PG_RETURN_BOOL(ret > 0); 
}

PG_FUNCTION_INFO_V1(decimal128_ge); 
Datum decimal128_ge(PG_FUNCTION_ARGS)
{
    PGDecimal128* pa = PG_GETARG_P_DECIMAL128(0);
    PGDecimal128* pb = PG_GETARG_P_DECIMAL128(1);
    int ret = decimal128_cmp_internal(pa, pb);
    PG_RETURN_BOOL(ret >= 0); 
}

PG_FUNCTION_INFO_V1(decimal128_eq); 
Datum decimal128_eq(PG_FUNCTION_ARGS)
{
    PGDecimal128* pa = PG_GETARG_P_DECIMAL128(0);
    PGDecimal128* pb = PG_GETARG_P_DECIMAL128(1);
    int ret = decimal128_cmp_internal(pa, pb);
    PG_RETURN_BOOL(ret == 0); 
}

PG_FUNCTION_INFO_V1(decimal128_ne); 
Datum decimal128_ne(PG_FUNCTION_ARGS)
{
    PGDecimal128* pa = PG_GETARG_P_DECIMAL128(0);
    PGDecimal128* pb = PG_GETARG_P_DECIMAL128(1);
    int ret = decimal128_cmp_internal(pa, pb);
    PG_RETURN_BOOL(ret != 0); 
}

PG_FUNCTION_INFO_V1(decimal128_cmp); 
Datum decimal128_cmp(PG_FUNCTION_ARGS)
{
    PGDecimal128* pa = PG_GETARG_P_DECIMAL128(0);
    PGDecimal128* pb = PG_GETARG_P_DECIMAL128(1);
    int ret = decimal128_cmp_internal(pa, pb);
    PG_RETURN_INT32(ret);
}

PG_FUNCTION_INFO_V1(decimal128_hash); 
Datum decimal128_hash(PG_FUNCTION_ARGS)
{
    PGDecimal128* pa = PG_GETARG_P_DECIMAL128(0);
    PGDecimal128 n;
    Datum ret;

    if (decQuadIsZero(pa)) {
        decQuadZero(&n); 
    } else {
        decQuadCanonical(&n, pa);
    }

    ret = hash_any((unsigned char *)&n, sizeof(n)); 
    return ret;
}

PG_FUNCTION_INFO_V1(decimal128_smaller); 
Datum decimal128_smaller(PG_FUNCTION_ARGS)
{
    PGDecimal128* pa = PG_GETARG_P_DECIMAL128(0);
    PGDecimal128* pb = PG_GETARG_P_DECIMAL128(1);
    DECLARE_PRET_128_WITH_CTXT(pret, DEC_INIT_DECIMAL128);

    decQuadMin(pret, pa, pb, &dc);
    PG_RETURN_P_DECIMAL128(pret);
}

PG_FUNCTION_INFO_V1(decimal128_larger); 
Datum decimal128_larger(PG_FUNCTION_ARGS)
{
    PGDecimal128* pa = PG_GETARG_P_DECIMAL128(0);
    PGDecimal128* pb = PG_GETARG_P_DECIMAL128(1);
    DECLARE_PRET_128_WITH_CTXT(pret, DEC_INIT_DECIMAL128);

    decQuadMax(pret, pa, pb, &dc);
    PG_RETURN_P_DECIMAL128(pret);
}

PG_FUNCTION_INFO_V1(decimal128_inc); 
Datum decimal128_inc(PG_FUNCTION_ARGS)
{
    PGDecimal128* pa = PG_GETARG_P_DECIMAL128(0);
    PGDecimal128 one;
    DECLARE_PRET_128_WITH_CTXT(pret, DEC_INIT_DECIMAL128);

    decQuadFromInt32(&one, 1);

    decQuadMax(pret, pa, &one, &dc);
    PG_RETURN_P_DECIMAL128(pret);
}

PG_FUNCTION_INFO_V1(decimal128_round); 
Datum decimal128_round(PG_FUNCTION_ARGS)
{
    static PGDecimal128* pquan;
    static PGDecimal128 quan[33];

    PGDecimal128* pa = PG_GETARG_P_DECIMAL128(0);
    int32_t scale = PG_GETARG_INT32(1);
    DECLARE_PRET_128_WITH_CTXT(pret, DEC_INIT_DECIMAL128);

    if (pquan == 0) {
        int i;
        PGDecimal128 ten;
        decQuadFromInt32(&ten, 10);
        decQuadFromInt32(&quan[0], 1);
        for (i = 1; i < 33; i++) {
            decQuadDivide(&quan[i], &quan[i-1], &ten, &dc);
        }
        pquan = &quan[0];
    }

    if (scale < 0 || scale > 32) {
        elog(ERROR, "decimal32 rounding to an invalid scale");
    }

    decQuadQuantize(pret, pa, &quan[scale], &dc);
    PG_RETURN_P_DECIMAL128(pret);
}

PG_FUNCTION_INFO_V1(decimal128_float4); 
Datum decimal128_float4(PG_FUNCTION_ARGS)
{
    PGDecimal128* pa = PG_GETARG_P_DECIMAL128(0);
    char s[DECQUAD_String];
    char *endp = 0;
    float f;

    decQuadToString(pa, s);

    errno = 0;
    f = strtof(s, &endp); 

    if (endp == s || errno != 0) {
        elog(ERROR, "cannot convert decimal128 to float4");
    }

    PG_RETURN_FLOAT4(f);
}

PG_FUNCTION_INFO_V1(float4_decimal128); 
Datum float4_decimal128(PG_FUNCTION_ARGS)
{
    float f = PG_GETARG_FLOAT4(0);
    char s[128];
    DECLARE_PRET_128_WITH_CTXT(pret, DEC_INIT_DECIMAL128);

    sprintf(s, "%.*g", FLT_DIG, f);
    decQuadFromString(pret, s, &dc); 
    DEC_CHK_STATUS(dc, DEC_STATUS_ALL, "invalid decimal128 syntax:\"%s\"", s);
    PG_RETURN_P_DECIMAL128(pret);
}

PG_FUNCTION_INFO_V1(decimal128_float8); 
Datum decimal128_float8(PG_FUNCTION_ARGS)
{
    PGDecimal128* pa = PG_GETARG_P_DECIMAL128(0);
    char s[DECQUAD_String];
    char *endp = 0;
    double d;

    decQuadToString(pa, s);

    errno = 0;
    d = strtod(s, &endp); 

    if (endp == s || errno != 0) {
        elog(ERROR, "cannot convert decimal128 to float8");
    }

    PG_RETURN_FLOAT8(d);
}

PG_FUNCTION_INFO_V1(float8_decimal128); 
Datum float8_decimal128(PG_FUNCTION_ARGS)
{
    double d = PG_GETARG_FLOAT8(0);
    char s[128];
    DECLARE_PRET_128_WITH_CTXT(pret, DEC_INIT_DECIMAL128);

    sprintf(s, "%.*g", DBL_DIG, d);
    decQuadFromString(pret, s, &dc); 
    DEC_CHK_STATUS(dc, DEC_STATUS_ALL, "invalid decimal128 syntax:\"%s\"", s);
    PG_RETURN_P_DECIMAL128(pret);
}

PG_FUNCTION_INFO_V1(int4_decimal128);
Datum int4_decimal128(PG_FUNCTION_ARGS)
{
    int32_t a = PG_GETARG_INT32(0);
    DECLARE_PRET_128(pret);

    decQuadFromInt32(pret, a);
    PG_RETURN_P_DECIMAL128(pret);
}

PG_FUNCTION_INFO_V1(int8_decimal128);
Datum int8_decimal128(PG_FUNCTION_ARGS)
{
    int64_t a = PG_GETARG_INT64(0);
    char s[128];
    DECLARE_PRET_128_WITH_CTXT(pret, DEC_INIT_DECIMAL128);

    sprintf(s, INT64_FORMAT, a); 
    decQuadFromString(pret, s, &dc); 
    DEC_CHK_STATUS(dc, DEC_STATUS_ALL, "invalid decimal128 syntax:\"%s\"", s);
    PG_RETURN_P_DECIMAL128(pret);
}

PG_FUNCTION_INFO_V1(decimal128_numeric);
Datum decimal128_numeric(PG_FUNCTION_ARGS)
{
    PGDecimal128* pa = PG_GETARG_P_DECIMAL128(0);
    Datum ret;
    char s[DECQUAD_String];

    decQuadToString(pa, s);
    ret = DirectFunctionCall3(numeric_in, 
                                 CStringGetDatum(s), Int32GetDatum(0), Int32GetDatum(-1));
    PG_RETURN_DATUM(ret);
}

PG_FUNCTION_INFO_V1(numeric_decimal128);
Datum numeric_decimal128(PG_FUNCTION_ARGS)
{
    char *buf;
    DECLARE_PRET_128_WITH_CTXT(pret, DEC_INIT_DECIMAL128);

    buf = DatumGetCString(DirectFunctionCall1(numeric_out, PG_GETARG_DATUM(0)));
    decQuadFromString(pret, buf, &dc); 
    DEC_CHK_STATUS(dc, DEC_STATUS_ALL, "invalid decimal128:\"%s\"", buf);
    pfree(buf);
    PG_RETURN_P_DECIMAL128(pret);
}

