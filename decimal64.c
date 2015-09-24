#include "decimal.h"

//
// Forward declaritions.
//
Datum decimal64_in(PG_FUNCTION_ARGS);
Datum decimal64_out(PG_FUNCTION_ARGS);
Datum decimal64_add(PG_FUNCTION_ARGS);
Datum decimal64_sub(PG_FUNCTION_ARGS);
Datum decimal64_mul(PG_FUNCTION_ARGS);
Datum decimal64_div(PG_FUNCTION_ARGS);
Datum decimal64_uplus(PG_FUNCTION_ARGS);
Datum decimal64_uminus(PG_FUNCTION_ARGS);
Datum decimal64_abs(PG_FUNCTION_ARGS);
Datum decimal64_lt(PG_FUNCTION_ARGS);
Datum decimal64_le(PG_FUNCTION_ARGS);
Datum decimal64_gt(PG_FUNCTION_ARGS);
Datum decimal64_ge(PG_FUNCTION_ARGS);
Datum decimal64_eq(PG_FUNCTION_ARGS);
Datum decimal64_ne(PG_FUNCTION_ARGS);
Datum decimal64_cmp(PG_FUNCTION_ARGS);
Datum decimal64_hash(PG_FUNCTION_ARGS);
Datum decimal64_smaller(PG_FUNCTION_ARGS);
Datum decimal64_larger(PG_FUNCTION_ARGS);
Datum decimal64_inc(PG_FUNCTION_ARGS);
Datum decimal64_round(PG_FUNCTION_ARGS);
Datum decimal64_decimal128(PG_FUNCTION_ARGS);
Datum decimal128_decimal64(PG_FUNCTION_ARGS);
Datum decimal64_float4(PG_FUNCTION_ARGS);
Datum float4_decimal64(PG_FUNCTION_ARGS);
Datum decimal64_float8(PG_FUNCTION_ARGS);
Datum float8_decimal64(PG_FUNCTION_ARGS);
Datum int4_decimal64(PG_FUNCTION_ARGS);
Datum int8_decimal64(PG_FUNCTION_ARGS);
Datum decimal64_numeric(PG_FUNCTION_ARGS);
Datum numeric_decimal64(PG_FUNCTION_ARGS);

PG_FUNCTION_INFO_V1(decimal64_in);
Datum decimal64_in(PG_FUNCTION_ARGS)
{
    char *s = PG_GETARG_CSTRING(0);
    PGDecimal64 ret;
    DECLARE_DEC_CTXT(DEC_INIT_DECIMAL64);

    decDoubleFromString(&ret, s, &dc);
    DEC_CHK_STATUS(dc, DEC_STATUS_ALL, "invalid decimal64 syntax:%s", s);

    PG_RETURN_DECIMAL64(ret);
}

PG_FUNCTION_INFO_V1(decimal64_out);
Datum decimal64_out(PG_FUNCTION_ARGS)
{
    PGDecimal64 d = PG_GETARG_DECIMAL64(0);
    char *s = (char *) palloc(DECDOUBLE_String);
    if (!s) {
        elog(ERROR, "OOM");
    }
    
    decDoubleToString(&d, s);
    PG_RETURN_CSTRING(s);
}

PG_FUNCTION_INFO_V1(decimal64_add); 
Datum decimal64_add(PG_FUNCTION_ARGS)
{
    PGDecimal64 a = PG_GETARG_DECIMAL64(0);
    PGDecimal64 b = PG_GETARG_DECIMAL64(1);
    PGDecimal64 ret;

    DECLARE_DEC_CTXT(DEC_INIT_DECIMAL64);
    decDoubleAdd(&ret, &a, &b, &dc); 
    DEC_CHK_STATUS(dc, DEC_STATUS_OFUF, "decimal64 overflow"); 

    PG_RETURN_DECIMAL64(ret);
}

PG_FUNCTION_INFO_V1(decimal64_sub); 
Datum decimal64_sub(PG_FUNCTION_ARGS)
{
    PGDecimal64 a = PG_GETARG_DECIMAL64(0);
    PGDecimal64 b = PG_GETARG_DECIMAL64(1);
    PGDecimal64 ret;

    DECLARE_DEC_CTXT(DEC_INIT_DECIMAL64);
    decDoubleSubtract(&ret, &a, &b, &dc); 
    DEC_CHK_STATUS(dc, DEC_STATUS_OFUF, "decimal64 overflow"); 

    PG_RETURN_DECIMAL64(ret);
}

PG_FUNCTION_INFO_V1(decimal64_mul); 
Datum decimal64_mul(PG_FUNCTION_ARGS)
{
    PGDecimal64 a = PG_GETARG_DECIMAL64(0);
    PGDecimal64 b = PG_GETARG_DECIMAL64(1);
    PGDecimal64 ret;

    DECLARE_DEC_CTXT(DEC_INIT_DECIMAL64);
    decDoubleMultiply(&ret, &a, &b, &dc); 
    DEC_CHK_STATUS(dc, DEC_STATUS_OFUF, "decimal64 overflow"); 

    PG_RETURN_DECIMAL64(ret);
}

PG_FUNCTION_INFO_V1(decimal64_div); 
Datum decimal64_div(PG_FUNCTION_ARGS)
{
    PGDecimal64 a = PG_GETARG_DECIMAL64(0);
    PGDecimal64 b = PG_GETARG_DECIMAL64(1);
    PGDecimal64 ret;

    DECLARE_DEC_CTXT(DEC_INIT_DECIMAL64);
    decDoubleDivide(&ret, &a, &b, &dc); 
    DEC_CHK_STATUS(dc, DEC_STATUS_DIV, "decimal64 division error"); 

    PG_RETURN_DECIMAL64(ret);
}

PG_FUNCTION_INFO_V1(decimal64_uplus); 
Datum decimal64_uplus(PG_FUNCTION_ARGS)
{
    PGDecimal64 a = PG_GETARG_DECIMAL64(0);
    PGDecimal64 ret;

    DECLARE_DEC_CTXT(DEC_INIT_DECIMAL64);
    decDoublePlus(&ret, &a, &dc); 
    DEC_CHK_STATUS(dc, DEC_STATUS_OFUF, "decimal64 overflow"); 

    PG_RETURN_DECIMAL64(ret);
}

PG_FUNCTION_INFO_V1(decimal64_uminus); 
Datum decimal64_uminus(PG_FUNCTION_ARGS)
{
    PGDecimal64 a = PG_GETARG_DECIMAL64(0);
    PGDecimal64 ret;

    DECLARE_DEC_CTXT(DEC_INIT_DECIMAL64);
    decDoubleMinus(&ret, &a, &dc); 
    DEC_CHK_STATUS(dc, DEC_STATUS_OFUF, "decimal64 overflow"); 

    PG_RETURN_DECIMAL64(ret);
}

PG_FUNCTION_INFO_V1(decimal64_abs); 
Datum decimal64_abs(PG_FUNCTION_ARGS)
{
    PGDecimal64 a = PG_GETARG_DECIMAL64(0);
    PGDecimal64 ret;

    DECLARE_DEC_CTXT(DEC_INIT_DECIMAL64);
    decDoubleAbs(&ret, &a, &dc); 
    DEC_CHK_STATUS(dc, DEC_STATUS_OFUF, "decimal64 overflow"); 

    PG_RETURN_DECIMAL64(ret);
}


static int decimal64_cmp_internal(const PGDecimal64* a, const PGDecimal64* b)
{
    PGDecimal64 result;
    DECLARE_DEC_CTXT(DEC_INIT_DECIMAL64);
    decDoubleCompare(&result, a, b, &dc);

    if (decDoubleIsPositive(&result)) {
        return 1;
    } else if (decDoubleIsZero(&result)) {
        return 0;
    } else if (decDoubleIsNegative(&result)) {
        return -1;
    } else {
        elog(ERROR, "invalid decimal64 in compare");
    }
}

PG_FUNCTION_INFO_V1(decimal64_lt); 
Datum decimal64_lt(PG_FUNCTION_ARGS)
{
    PGDecimal64 a = PG_GETARG_DECIMAL64(0);
    PGDecimal64 b = PG_GETARG_DECIMAL64(1);
    int ret = decimal64_cmp_internal(&a, &b);
    PG_RETURN_BOOL(ret < 0); 
}

PG_FUNCTION_INFO_V1(decimal64_le); 
Datum decimal64_le(PG_FUNCTION_ARGS)
{
    PGDecimal64 a = PG_GETARG_DECIMAL64(0);
    PGDecimal64 b = PG_GETARG_DECIMAL64(1);
    int ret = decimal64_cmp_internal(&a, &b);
    PG_RETURN_BOOL(ret <= 0); 
}

PG_FUNCTION_INFO_V1(decimal64_gt); 
Datum decimal64_gt(PG_FUNCTION_ARGS)
{
    PGDecimal64 a = PG_GETARG_DECIMAL64(0);
    PGDecimal64 b = PG_GETARG_DECIMAL64(1);
    int ret = decimal64_cmp_internal(&a, &b);
    PG_RETURN_BOOL(ret > 0); 
}

PG_FUNCTION_INFO_V1(decimal64_ge); 
Datum decimal64_ge(PG_FUNCTION_ARGS)
{
    PGDecimal64 a = PG_GETARG_DECIMAL64(0);
    PGDecimal64 b = PG_GETARG_DECIMAL64(1);
    int ret = decimal64_cmp_internal(&a, &b);
    PG_RETURN_BOOL(ret >= 0); 
}

PG_FUNCTION_INFO_V1(decimal64_eq); 
Datum decimal64_eq(PG_FUNCTION_ARGS)
{
    PGDecimal64 a = PG_GETARG_DECIMAL64(0);
    PGDecimal64 b = PG_GETARG_DECIMAL64(1);
    int ret = decimal64_cmp_internal(&a, &b);
    PG_RETURN_BOOL(ret == 0); 
}

PG_FUNCTION_INFO_V1(decimal64_ne); 
Datum decimal64_ne(PG_FUNCTION_ARGS)
{
    PGDecimal64 a = PG_GETARG_DECIMAL64(0);
    PGDecimal64 b = PG_GETARG_DECIMAL64(1);
    int ret = decimal64_cmp_internal(&a, &b);
    PG_RETURN_BOOL(ret != 0); 
}

PG_FUNCTION_INFO_V1(decimal64_cmp); 
Datum decimal64_cmp(PG_FUNCTION_ARGS)
{
    PGDecimal64 a = PG_GETARG_DECIMAL64(0);
    PGDecimal64 b = PG_GETARG_DECIMAL64(1);
    int ret = decimal64_cmp_internal(&a, &b);
    PG_RETURN_INT32(ret);
}

PG_FUNCTION_INFO_V1(decimal64_hash); 
Datum decimal64_hash(PG_FUNCTION_ARGS)
{
    PGDecimal64 a = PG_GETARG_DECIMAL64(0);
    PGDecimal64 n;
    Datum ret;

    if (decDoubleIsZero(&a)) {
        decDoubleZero(&n);
    } else {
        decDoubleCanonical(&n, &a);
    }

    ret = hash_any((unsigned char *)&n, sizeof(n));
    return ret;
}

PG_FUNCTION_INFO_V1(decimal64_smaller); 
Datum decimal64_smaller(PG_FUNCTION_ARGS)
{
    PGDecimal64 a = PG_GETARG_DECIMAL64(0);
    PGDecimal64 b = PG_GETARG_DECIMAL64(1);
    PGDecimal64 ret;
    DECLARE_DEC_CTXT(DEC_INIT_DECIMAL64);

    decDoubleMin(&ret, &a, &b, &dc);
    PG_RETURN_DECIMAL64(ret);
}

PG_FUNCTION_INFO_V1(decimal64_larger); 
Datum decimal64_larger(PG_FUNCTION_ARGS)
{
    PGDecimal64 a = PG_GETARG_DECIMAL64(0);
    PGDecimal64 b = PG_GETARG_DECIMAL64(1);
    PGDecimal64 ret;
    DECLARE_DEC_CTXT(DEC_INIT_DECIMAL64);

    decDoubleMax(&ret, &a, &b, &dc);
    PG_RETURN_DECIMAL64(ret);
}

PG_FUNCTION_INFO_V1(decimal64_inc); 
Datum decimal64_inc(PG_FUNCTION_ARGS)
{
    PGDecimal64 a = PG_GETARG_DECIMAL64(0);
    PGDecimal64 one;
    PGDecimal64 ret;
    DECLARE_DEC_CTXT(DEC_INIT_DECIMAL64);

    decDoubleFromInt32(&one, 1);
    decDoubleAdd(&ret, &a, &one, &dc);
    PG_RETURN_DECIMAL64(ret);
}

PG_FUNCTION_INFO_V1(decimal64_round); 
Datum decimal64_round(PG_FUNCTION_ARGS)
{
    PGDecimal64 a = PG_GETARG_DECIMAL64(0);
    int32_t scale = PG_GETARG_INT32(1);
    PGDecimal64 ret;

    static PGDecimal64* pquan;
    static PGDecimal64 quan[16];

    DECLARE_DEC_CTXT(DEC_INIT_DECIMAL64);

    if (pquan == 0) {
        int i;
        PGDecimal64 ten;
        decDoubleFromInt32(&ten, 10);
        decDoubleFromInt32(&quan[0], 1);
        for (i = 1; i < 16; i++) {
            decDoubleDivide(&quan[i], &quan[i-1], &ten, &dc);
        }
        pquan = &quan[0];
    }

    if (scale < 0 || scale > 15) {
        elog(ERROR, "decimal32 rounding to an invalid scale");
    }

    decDoubleQuantize(&ret, &a, &quan[scale], &dc);
    PG_RETURN_DECIMAL64(ret);
}

PG_FUNCTION_INFO_V1(decimal64_decimal128);
Datum decimal64_decimal128(PG_FUNCTION_ARGS)
{
    PGDecimal64 a = PG_GETARG_DECIMAL64(0);
    DECLARE_PRET_128(pret);

    decDoubleToWider(&a, pret);
    PG_RETURN_P_DECIMAL128(pret);
}

PG_FUNCTION_INFO_V1(decimal128_decimal64);
Datum decimal128_decimal64(PG_FUNCTION_ARGS)
{
    PGDecimal128* pa = PG_GETARG_P_DECIMAL128(0);
    PGDecimal64 ret;
    DECLARE_DEC_CTXT(DEC_INIT_DECIMAL64);

    decDoubleFromWider(&ret, pa, &dc); 
    DEC_CHK_STATUS(dc, DEC_STATUS_OFUF, "decimal128 to decimal64 over/under flow");
    PG_RETURN_DECIMAL64(ret);
}

PG_FUNCTION_INFO_V1(decimal64_float4); 
Datum decimal64_float4(PG_FUNCTION_ARGS)
{
    PGDecimal64 a = PG_GETARG_DECIMAL64(0);
    char s[DECDOUBLE_String];
    char *endp = 0;
    float f;

    decDoubleToString(&a, s);

    errno = 0;
    f = strtof(s, &endp); 

    if (endp == s || errno != 0) {
        elog(ERROR, "cannot convert decimal64 to float4");
    }

    PG_RETURN_FLOAT4(f);
}

PG_FUNCTION_INFO_V1(float4_decimal64); 
Datum float4_decimal64(PG_FUNCTION_ARGS)
{
    float f = PG_GETARG_FLOAT4(0);
    PGDecimal64 ret; 
    char s[128];

    DECLARE_DEC_CTXT(DEC_INIT_DECIMAL64);

    sprintf(s, "%.*g", FLT_DIG, f);
    decDoubleFromString(&ret, s, &dc); 
    DEC_CHK_STATUS(dc, DEC_STATUS_ALL, "invalid decimal64 syntax:\"%s\"", s);

    PG_RETURN_DECIMAL64(ret);
}

PG_FUNCTION_INFO_V1(decimal64_float8); 
Datum decimal64_float8(PG_FUNCTION_ARGS)
{
    PGDecimal64 a = PG_GETARG_DECIMAL64(0);
    char s[DECDOUBLE_String];
    char *endp = 0;
    double d;

    decDoubleToString(&a, s);

    errno = 0;
    d = strtod(s, &endp); 

    if (endp == s || errno != 0) {
        elog(ERROR, "cannot convert decimal64 to float8");
    }

    PG_RETURN_FLOAT8(d);
}

PG_FUNCTION_INFO_V1(float8_decimal64); 
Datum float8_decimal64(PG_FUNCTION_ARGS)
{
    double d = PG_GETARG_FLOAT8(0);
    PGDecimal64 ret; 
    char s[128];
    DECLARE_DEC_CTXT(DEC_INIT_DECIMAL64);

    sprintf(s, "%.*g", DBL_DIG, d);
    decDoubleFromString(&ret, s, &dc); 
    DEC_CHK_STATUS(dc, DEC_STATUS_ALL, "invalid decimal64 syntax:\"%s\"", s);

    PG_RETURN_DECIMAL64(ret);
}

PG_FUNCTION_INFO_V1(int4_decimal64);
Datum int4_decimal64(PG_FUNCTION_ARGS)
{
    int32_t a = PG_GETARG_INT32(0);
    PGDecimal64 ret;

    decDoubleFromInt32(&ret, a);
    PG_RETURN_DECIMAL64(ret);
}

PG_FUNCTION_INFO_V1(int8_decimal64);
Datum int8_decimal64(PG_FUNCTION_ARGS)
{
    int64_t a = PG_GETARG_INT64(0);
    PGDecimal64 ret;
    char s[128];

    DECLARE_DEC_CTXT(DEC_INIT_DECIMAL64);
    sprintf(s, INT64_FORMAT, a); 
    decDoubleFromString(&ret, s, &dc); 
    DEC_CHK_STATUS(dc, DEC_STATUS_ALL, "invalid decimal64 syntax:\"%s\"", s);
    PG_RETURN_DECIMAL64(ret);
}

PG_FUNCTION_INFO_V1(decimal64_numeric);
Datum decimal64_numeric(PG_FUNCTION_ARGS)
{
    PGDecimal64 a = PG_GETARG_DECIMAL64(0);
    Datum ret;
    char s[DECDOUBLE_String];

    decDoubleToString(&a, s);
    ret = DirectFunctionCall3(numeric_in, 
                                 CStringGetDatum(s), Int32GetDatum(0), Int32GetDatum(-1));
    PG_RETURN_DATUM(ret);
}

PG_FUNCTION_INFO_V1(numeric_decimal64);
Datum numeric_decimal64(PG_FUNCTION_ARGS)
{
    char *buf;
    PGDecimal64 ret; 
    DECLARE_DEC_CTXT(DEC_INIT_DECIMAL64);

    buf = DatumGetCString(DirectFunctionCall1(numeric_out, PG_GETARG_DATUM(0)));
    decDoubleFromString(&ret, buf, &dc); 
    DEC_CHK_STATUS(dc, DEC_STATUS_ALL, "invalid decimal64:\"%s\"", buf);
    pfree(buf);
    PG_RETURN_DECIMAL64(ret);
}

