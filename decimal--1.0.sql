/* contrib/decimal/decimal--1.0.sql */ 

-- complain if script is sourced in psql, rather than via CREATE EXTENSION
-- \echo Use "CREATE EXTENSION decimal" to load this file. \quit

--
-- PostgreSQL code for Decimal64/128. 
--

--
-- Shell type to keep things a bit quieter.
--

CREATE TYPE decimal128;

--
--  Input and output functions.
--
CREATE FUNCTION decimal128_in(cstring)
RETURNS decimal128
AS 'MODULE_PATHNAME'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION decimal128_out(decimal128)
RETURNS cstring
AS 'MODULE_PATHNAME'
LANGUAGE C IMMUTABLE STRICT;

CREATE TYPE decimal128 (
    INPUT          = decimal128_in,
    OUTPUT         = decimal128_out,
    LIKE = pg_catalog.interval
);

--
-- decimal128 functions.   
--

--  group 1: arithmatics, 
CREATE FUNCTION decimal128_div(decimal128, decimal128)
RETURNS decimal128
AS 'MODULE_PATHNAME'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION decimal128_mul(decimal128, decimal128)
RETURNS decimal128
AS 'MODULE_PATHNAME'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION decimal128_add(decimal128, decimal128)
RETURNS decimal128
AS 'MODULE_PATHNAME'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION decimal128_sub(decimal128, decimal128)
RETURNS decimal128
AS 'MODULE_PATHNAME'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION decimal128_uminus(decimal128) 
RETURNS decimal128
AS 'MODULE_PATHNAME'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION decimal128_uplus(decimal128) 
RETURNS decimal128
AS 'MODULE_PATHNAME'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION decimal128_abs(decimal128) 
RETURNS decimal128
AS 'MODULE_PATHNAME'
LANGUAGE C IMMUTABLE STRICT;

--  group 2: compares.
CREATE FUNCTION decimal128_eq(decimal128, decimal128)
RETURNS boolean 
AS 'MODULE_PATHNAME'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION decimal128_ne(decimal128, decimal128)
RETURNS boolean
AS 'MODULE_PATHNAME'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION decimal128_lt(decimal128, decimal128)
RETURNS boolean
AS 'MODULE_PATHNAME'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION decimal128_le(decimal128, decimal128)
RETURNS boolean
AS 'MODULE_PATHNAME'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION decimal128_gt(decimal128, decimal128)
RETURNS boolean
AS 'MODULE_PATHNAME'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION decimal128_ge(decimal128, decimal128)
RETURNS boolean
AS 'MODULE_PATHNAME'
LANGUAGE C IMMUTABLE STRICT;

-- group 3: hash and cmp
CREATE FUNCTION decimal128_hash(decimal128) 
RETURNS integer 
AS 'MODULE_PATHNAME'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION decimal128_cmp(decimal128, decimal128)
RETURNS integer 
AS 'MODULE_PATHNAME'
LANGUAGE C IMMUTABLE STRICT;

-- group 4: misc
CREATE FUNCTION decimal128_inc(decimal128) 
RETURNS decimal128
AS 'MODULE_PATHNAME'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION decimal128_smaller(decimal128, decimal128) 
RETURNS decimal128
AS 'MODULE_PATHNAME'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION decimal128_larger(decimal128, decimal128) 
RETURNS decimal128
AS 'MODULE_PATHNAME'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION round(decimal128, int)
RETURNS decimal128
AS 'MODULE_PATHNAME','decimal128_round'
LANGUAGE C IMMUTABLE STRICT;

-- NYI:
--  mod, sqrt, pow, log, ln, fac, sign, trunc, ceil, floor
--  exp, div_trunc,

-- decimal aggregates
--  NYI: higher momentum stats functions, stddev, var, etc.  
CREATE AGGREGATE sum(decimal128)
(
	sfunc = decimal128_add,
	stype = decimal128
);

CREATE AGGREGATE min(decimal128)
(
	sfunc = decimal128_smaller,
	stype = decimal128
);

CREATE AGGREGATE max(decimal128)
(
	sfunc = decimal128_larger,
	stype = decimal128
);

-- 
-- operators
-- 
CREATE OPERATOR / (
  PROCEDURE = decimal128_div,
  LEFTARG = decimal128, RIGHTARG = decimal128
);

CREATE OPERATOR * (
  PROCEDURE = decimal128_mul,
  LEFTARG = decimal128, RIGHTARG = decimal128
);

CREATE OPERATOR + (
  PROCEDURE = decimal128_add,
  LEFTARG = decimal128, RIGHTARG = decimal128
);

CREATE OPERATOR - (
  PROCEDURE = decimal128_sub,
  LEFTARG = decimal128, RIGHTARG = decimal128
);

CREATE OPERATOR + (
  PROCEDURE = decimal128_uplus, 
  RIGHTARG = decimal128
);

CREATE OPERATOR - (
  PROCEDURE = decimal128_uminus, 
  RIGHTARG = decimal128
);

CREATE OPERATOR < (
  PROCEDURE = decimal128_lt,
  LEFTARG = decimal128, RIGHTARG = decimal128,
  COMMUTATOR = >,
  NEGATOR = >=
);

CREATE OPERATOR <= (
  PROCEDURE = decimal128_le,
  LEFTARG = decimal128, RIGHTARG = decimal128,
  COMMUTATOR = >=,
  NEGATOR = >
);

CREATE OPERATOR > (
  PROCEDURE = decimal128_gt,
  LEFTARG = decimal128, RIGHTARG = decimal128,
  COMMUTATOR = <,
  NEGATOR = <=
);

CREATE OPERATOR >= (
  PROCEDURE = decimal128_ge,
  LEFTARG = decimal128, RIGHTARG = decimal128,
  COMMUTATOR = <=,
  NEGATOR = <
);

CREATE OPERATOR = (
  PROCEDURE = decimal128_eq,
  LEFTARG = decimal128, RIGHTARG = decimal128,
  COMMUTATOR = =,
  NEGATOR = <>,
  MERGES, HASHES
);

CREATE OPERATOR <> (
  PROCEDURE = decimal128_ne,
  LEFTARG = decimal128, RIGHTARG = decimal128,
  COMMUTATOR = <>,
  NEGATOR = =
);

CREATE OPERATOR FAMILY decimal128_ops USING btree;
CREATE OPERATOR FAMILY decimal128_ops USING hash;

CREATE OPERATOR CLASS decimal128_op_cls DEFAULT 
FOR TYPE decimal128 USING btree FAMILY decimal128_ops AS
    OPERATOR 1 <,
    OPERATOR 2 <=,
    OPERATOR 3 =,
    OPERATOR 4 >=,
    OPERATOR 5 >,
    FUNCTION 1 decimal128_cmp(decimal128, decimal128);

CREATE OPERATOR CLASS decimal128_op_cls DEFAULT
FOR TYPE decimal128 USING hash FAMILY decimal128_ops AS
    OPERATOR 1 =,
    FUNCTION 1 decimal128_hash(decimal128);


--
-- Shell type to keep things a bit quieter.
--

CREATE TYPE decimal64;

--
--  Input and output functions.
--
CREATE FUNCTION decimal64_in(cstring)
RETURNS decimal64
AS 'MODULE_PATHNAME'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION decimal64_out(decimal64)
RETURNS cstring
AS 'MODULE_PATHNAME'
LANGUAGE C IMMUTABLE STRICT;

CREATE TYPE decimal64 (
    INPUT          = decimal64_in,
    OUTPUT         = decimal64_out,
    LIKE = pg_catalog.int8
);

--
-- decimal64 functions.   
--

--  group 1: arithmatics, 
CREATE FUNCTION decimal64_div(decimal64, decimal64)
RETURNS decimal64
AS 'MODULE_PATHNAME'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION decimal64_mul(decimal64, decimal64)
RETURNS decimal64
AS 'MODULE_PATHNAME'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION decimal64_add(decimal64, decimal64)
RETURNS decimal64
AS 'MODULE_PATHNAME'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION decimal64_sub(decimal64, decimal64)
RETURNS decimal64
AS 'MODULE_PATHNAME'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION decimal64_uminus(decimal64) 
RETURNS decimal64
AS 'MODULE_PATHNAME'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION decimal64_uplus(decimal64) 
RETURNS decimal64
AS 'MODULE_PATHNAME'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION decimal64_abs(decimal64) 
RETURNS decimal64
AS 'MODULE_PATHNAME'
LANGUAGE C IMMUTABLE STRICT;

--  group 2: compares.
CREATE FUNCTION decimal64_eq(decimal64, decimal64)
RETURNS boolean 
AS 'MODULE_PATHNAME'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION decimal64_ne(decimal64, decimal64)
RETURNS boolean
AS 'MODULE_PATHNAME'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION decimal64_lt(decimal64, decimal64)
RETURNS boolean
AS 'MODULE_PATHNAME'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION decimal64_le(decimal64, decimal64)
RETURNS boolean
AS 'MODULE_PATHNAME'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION decimal64_gt(decimal64, decimal64)
RETURNS boolean
AS 'MODULE_PATHNAME'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION decimal64_ge(decimal64, decimal64)
RETURNS boolean
AS 'MODULE_PATHNAME'
LANGUAGE C IMMUTABLE STRICT;

-- group 3: hash and cmp
CREATE FUNCTION decimal64_hash(decimal64) 
RETURNS integer 
AS 'MODULE_PATHNAME'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION decimal64_cmp(decimal64, decimal64)
RETURNS integer 
AS 'MODULE_PATHNAME'
LANGUAGE C IMMUTABLE STRICT;

-- group 4: misc
CREATE FUNCTION decimal64_inc(decimal64) 
RETURNS decimal64
AS 'MODULE_PATHNAME'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION decimal64_smaller(decimal64, decimal64) 
RETURNS decimal64
AS 'MODULE_PATHNAME'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION decimal64_larger(decimal64, decimal64) 
RETURNS decimal64
AS 'MODULE_PATHNAME'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION round(decimal64, int)
RETURNS decimal64
AS 'MODULE_PATHNAME','decimal64_round'
LANGUAGE C IMMUTABLE STRICT;

-- NYI:
--  mod, sqrt, pow, log, ln, fac, sign, trunc, ceil, floor
--  exp, div_trunc,

-- decimal aggregates
--  NYI: higher momentum stats functions, stddev, var, etc.  
CREATE AGGREGATE sum(decimal64)
(
	sfunc = decimal64_add,
	stype = decimal64
);

CREATE AGGREGATE min(decimal64)
(
	sfunc = decimal64_smaller,
	stype = decimal64
);

CREATE AGGREGATE max(decimal64)
(
	sfunc = decimal64_larger,
	stype = decimal64
);

-- 
-- operators
-- 
CREATE OPERATOR / (
  PROCEDURE = decimal64_div,
  LEFTARG = decimal64, RIGHTARG = decimal64
);

CREATE OPERATOR * (
  PROCEDURE = decimal64_mul,
  LEFTARG = decimal64, RIGHTARG = decimal64
);

CREATE OPERATOR + (
  PROCEDURE = decimal64_add,
  LEFTARG = decimal64, RIGHTARG = decimal64
);

CREATE OPERATOR - (
  PROCEDURE = decimal64_sub,
  LEFTARG = decimal64, RIGHTARG = decimal64
);

CREATE OPERATOR + (
  PROCEDURE = decimal64_uplus, 
  RIGHTARG = decimal64
);

CREATE OPERATOR - (
  PROCEDURE = decimal64_uminus, 
  RIGHTARG = decimal64
);

CREATE OPERATOR < (
  PROCEDURE = decimal64_lt,
  LEFTARG = decimal64, RIGHTARG = decimal64,
  COMMUTATOR = >,
  NEGATOR = >=
);

CREATE OPERATOR <= (
  PROCEDURE = decimal64_le,
  LEFTARG = decimal64, RIGHTARG = decimal64,
  COMMUTATOR = >=,
  NEGATOR = >
);

CREATE OPERATOR > (
  PROCEDURE = decimal64_gt,
  LEFTARG = decimal64, RIGHTARG = decimal64,
  COMMUTATOR = <,
  NEGATOR = <=
);

CREATE OPERATOR >= (
  PROCEDURE = decimal64_ge,
  LEFTARG = decimal64, RIGHTARG = decimal64,
  COMMUTATOR = <=,
  NEGATOR = <
);

CREATE OPERATOR = (
  PROCEDURE = decimal64_eq,
  LEFTARG = decimal64, RIGHTARG = decimal64,
  COMMUTATOR = =,
  NEGATOR = <>,
  MERGES, HASHES
);

CREATE OPERATOR <> (
  PROCEDURE = decimal64_ne,
  LEFTARG = decimal64, RIGHTARG = decimal64,
  COMMUTATOR = <>,
  NEGATOR = =
);

CREATE OPERATOR FAMILY decimal64_ops USING btree;
CREATE OPERATOR FAMILY decimal64_ops USING hash;

CREATE OPERATOR CLASS decimal64_op_cls DEFAULT 
FOR TYPE decimal64 USING btree FAMILY decimal64_ops AS
    OPERATOR 1 <,
    OPERATOR 2 <=,
    OPERATOR 3 =,
    OPERATOR 4 >=,
    OPERATOR 5 >,
    FUNCTION 1 decimal64_cmp(decimal64, decimal64);

CREATE OPERATOR CLASS decimal64_op_cls DEFAULT
FOR TYPE decimal64 USING hash FAMILY decimal64_ops AS
    OPERATOR 1 =,
    FUNCTION 1 decimal64_hash(decimal64);

/*
 * Casts functions
 */
CREATE FUNCTION decimal128_decimal64(decimal128)
RETURNS decimal64
AS 'MODULE_PATHNAME'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION decimal64_decimal128(decimal64)
RETURNS decimal128
AS 'MODULE_PATHNAME'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION float4_decimal64(float4)
RETURNS decimal64
AS 'MODULE_PATHNAME'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION float4_decimal128(float4)
RETURNS decimal128
AS 'MODULE_PATHNAME'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION decimal64_float4(decimal64) 
RETURNS float4
AS 'MODULE_PATHNAME'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION decimal128_float4(decimal128) 
RETURNS float4
AS 'MODULE_PATHNAME'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION float8_decimal64(float8)
RETURNS decimal64
AS 'MODULE_PATHNAME'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION float8_decimal128(float8)
RETURNS decimal128
AS 'MODULE_PATHNAME'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION decimal64_float8(decimal64) 
RETURNS float8
AS 'MODULE_PATHNAME'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION decimal128_float8(decimal128) 
RETURNS float8
AS 'MODULE_PATHNAME'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION numeric_decimal64(numeric) 
RETURNS decimal64
AS 'MODULE_PATHNAME'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION numeric_decimal128(numeric) 
RETURNS decimal128
AS 'MODULE_PATHNAME'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION decimal64_numeric(decimal64)
RETURNS numeric
AS 'MODULE_PATHNAME'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION decimal128_numeric(decimal128)
RETURNS numeric
AS 'MODULE_PATHNAME'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION int4_decimal64(int4)
RETURNS decimal64
AS 'MODULE_PATHNAME'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION int4_decimal128(int4)
RETURNS decimal128
AS 'MODULE_PATHNAME'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION int8_decimal64(int8)
RETURNS decimal64
AS 'MODULE_PATHNAME'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION int8_decimal128(int8)
RETURNS decimal128
AS 'MODULE_PATHNAME'
LANGUAGE C IMMUTABLE STRICT;

CREATE CAST(decimal128 AS decimal64)
WITH FUNCTION decimal128_decimal64(decimal128);

CREATE CAST(decimal64 AS decimal128)
WITH FUNCTION decimal64_decimal128(decimal64)
AS IMPLICIT;

CREATE CAST(float4 AS decimal64)
WITH FUNCTION float4_decimal64(float4)
AS IMPLICIT;

CREATE CAST(float4 AS decimal128)
WITH FUNCTION float4_decimal128(float4)
AS IMPLICIT;

CREATE CAST(decimal64 AS float4)
WITH FUNCTION decimal64_float4(decimal64);

CREATE CAST(decimal128 AS float4)
WITH FUNCTION decimal128_float4(decimal128);

CREATE CAST(float8 AS decimal64)
WITH FUNCTION float8_decimal64(float8);

CREATE CAST(float8 AS decimal128)
WITH FUNCTION float8_decimal128(float8)
AS IMPLICIT;

CREATE CAST(decimal64 AS float8)
WITH FUNCTION decimal64_float8(decimal64);

CREATE CAST(decimal128 AS float8)
WITH FUNCTION decimal128_float8(decimal128);

CREATE CAST(numeric AS decimal64)
WITH FUNCTION numeric_decimal64(numeric);

CREATE CAST(numeric AS decimal128)
WITH FUNCTION numeric_decimal128(numeric);

CREATE CAST(decimal64 AS numeric)
WITH FUNCTION decimal64_numeric(decimal64)
AS IMPLICIT;

CREATE CAST(decimal128 AS numeric)
WITH FUNCTION decimal128_numeric(decimal128)
AS IMPLICIT;

CREATE CAST(int4 AS decimal64)
WITH FUNCTION int4_decimal64(int4)
AS IMPLICIT;

CREATE CAST(int4 AS decimal128)
WITH FUNCTION int4_decimal128(int4)
AS IMPLICIT;

CREATE CAST(int8 AS decimal64)
WITH FUNCTION int8_decimal64(int8);

CREATE CAST(int8 AS decimal128)
WITH FUNCTION int8_decimal128(int8)
AS IMPLICIT;

