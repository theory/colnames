colnames 1.7.0
==============

Synopsis
--------

``` psql
try=# CREATE EXTENSION colnames;
CREATE EXTENSION

try=# SELECT colnames( ROW(1, 'foo', 458.0) );
  colnames
------------
 {f1,f2,f3}

try=# SELECT colnames( ROW(c.*)::pg_collation ) FROM pg_collation c LIMIT 1;
                                colnames
-----------------------------------------------------------------------
 {collname,collnamespace,collowner,collencoding,collcollate,collctype}
```

Description
-----------

This extension contains a single SQL function, `colnames()`, that takes a
record value as its argument and returns an array of the names of the columns
in that record. This can be useful for example in trigger functions, where one
might need to get the column names in order to generate a query string.

Usage
-----

Simply pass a record value to the function and it will return an array of
the column names for that record:

``` psql
try=# SELECT colnames( ROW(1, 'foo', 458.0) );
  colnames
------------
 {f1,f2,f3}
```

Note that this function is not strict; it's legal to pass in a null record of
a named composite type:

``` psql
try=# SELECT colnames( NULL::pg_collation );
                                colnames
-----------------------------------------------------------------------
 {collname,collnamespace,collowner,collencoding,collcollate,collctype}
```

**Warning:** The indexes of the resulting array do **not** necessarily
correspond to the values one might find when fetching column names from
`pg_attribute.attnum`, since columns are not returned. The resulting array
**does** correspond to the order of fields that would be returned by, say,
`SELECT (rec).*`.

Support
-------

This library is stored in a public
[GitHub repository](https://github.com/theory/colnames). Feel free to fork and
contribute! Please file bug reports via
[GitHub Issues](https://github.com/theory/colnames/issues/).

Authors
-------

*   [Andrew Gierth](https://blog.rhodiumtoad.org.uk)
*   [David E. Wheeler](https://www.justatheory.com/)

Copyright and License
---------------------

Copyright (c) 2011-2024 Andrew Gierth and David E. Wheeler.

This module is free software; you can redistribute it and/or modify it under
the [PostgreSQL License](http://www.opensource.org/licenses/postgresql).

Permission to use, copy, modify, and distribute this software and its
documentation for any purpose, without fee, and without a written agreement is
hereby granted, provided that the above copyright notice and this paragraph
and the following two paragraphs appear in all copies.

IN NO EVENT SHALL ANDREW GIERTH AND DAVID E. WHEELER BE LIABLE TO ANY PARTY
FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, INCLUDING
LOST PROFITS, ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION,
EVEN IF ANDREW GIERTH AND DAVID E. WHEELER HAS BEEN ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.

ANDREW GIERTH AND DAVID E. WHEELER SPECIFICALLY DISCLAIMS ANY WARRANTIES,
INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
FITNESS FOR A PARTICULAR PURPOSE. THE SOFTWARE PROVIDED HEREUNDER IS ON AN “AS
IS” BASIS, AND ANDREW GIERTH AND DAVID E. WHEELER HAS NO OBLIGATIONS TO
PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
