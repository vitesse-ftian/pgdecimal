#ifndef _PG_DECIMAL_H_
#define _PG_DECIMAL_H_

#include "postgres.h"

#include "utils/builtins.h"
#include "utils/formatting.h"

#include "decSingle.h"
#include "decDouble.h"
#include "decQuad.h"

#include <float.h>

typedef decDouble PGDecimal64;
typedef decQuad PGDecimal128;

PGDecimal64 DatumGetDecimal64(Datum d);
Datum Decimal64GetDatum(PGDecimal64 d);

#define PG_GETARG_DECIMAL64(n) DatumGetDecimal64(PG_GETARG_DATUM(n))
#define PG_GETARG_P_DECIMAL128(n) ((PGDecimal128 *) DatumGetPointer(PG_GETARG_DATUM(n)))

#define PG_RETURN_DECIMAL64(d) return Decimal64GetDatum(d)
#define PG_RETURN_P_DECIMAL128(d) return PointerGetDatum(d)

#define DECLARE_PRET_128(P)                                             \
    PGDecimal128 *P = (PGDecimal128 *) palloc(sizeof(PGDecimal128));    \
    if (!P) {                                                           \
        elog(ERROR, "OOM");                                             \
    } else (void) 0                                                      

#define DECLARE_DEC_CTXT(X)         \
    decContext dc;                  \
    decContextDefault(&dc, X)     

#define DECLARE_PRET_128_WITH_CTXT(P, X)                    \
    decContext dc;                                          \
    PGDecimal128 *P;                                        \
    decContextDefault(&dc, X);                              \
    P = (PGDecimal128 *) palloc(sizeof(PGDecimal128));      \
    if (!X) {                                               \
        elog(ERROR, "OOM");                                 \
    } else (void) 0                                                      


#define DEC_CHK_STATUS(dc, chk_status, ...)                             \
    if (1) {                                                            \
        uint32_t dc_status = decContextGetStatus(&dc);                  \
        if ((dc_status & chk_status) != 0) {                            \
            elog(ERROR, __VA_ARGS__);                                   \
        }                                                               \
    } else (void) 0 

#define DEC_STATUS_OFUF (DEC_Overflow | DEC_Underflow)
#define DEC_STATUS_DIV  (DEC_Division_by_zero | DEC_Division_impossible | DEC_Division_undefined | DEC_STATUS_OFUF)
#define DEC_STATUS_ALL  (0xFFFF)

extern Datum hash_any(register const unsigned char* p, register int len);

#endif  /* _PG_DECIMAL_H_ */
