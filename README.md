colnames 1.7.0
==============

[![PGXN version](https://badge.fury.io/pg/colnames.svg)](https://badge.fury.io/pg/colnames)
[![Build Status](https://github.com/theory/colnames/workflows/CI/badge.svg)](https://github.com/theory/colnames/actions)

This extension contains a single SQL function, `colnames()`, that takes a
record value as its argument and returns an array of the names of the columns
in that record:

``` psql
try=# SELECT colnames( ROW(1, 'foo', 458.0) );
  colnames
------------
 {f1,f2,f3}
```

This can be useful for example in trigger functions, where one might need the
column names to generate a query string.

### Pure SQL Alternative

Can't use a C extension? Fear not! PostgreSQL 9.3 and later include JSON
functions get the column names directly:

```psql
try=# SELECT ARRAY( SELECT json_object_keys( row_to_json( ROW( 1, 3, 'foo' ) ) ) );
   array
------------
 {f1,f2,f3}
```

Installation
------------

To build colnames, just do this:

``` sh
make
make install
make installcheck
```

If you encounter an error such as:

```
"Makefile", line 8: Need an operator
```

You need to use GNU make, which may well be installed on your system as
`gmake`:

``` sh
gmake
gmake installcheck
gmake install
```

If you encounter an error such as:

```
make: pg_config: Command not found
```

Be sure that you have `pg_config` installed and in your path. If you used a
package management system such as RPM to install PostgreSQL, be sure that the
`-devel` package is also installed. If necessary tell the build process where
to find it:

``` sh
make PG_CONFIG=/path/to/pg_config
make install PG_CONFIG=/path/to/pg_config
make installcheck PG_CONFIG=/path/to/pg_config
```

If you encounter an error such as:

```
ERROR:  must be owner of database regression
```

You need to run the test suite using a super user, such as the default
"postgres" super user:

``` sh
make installcheck PGUSER=postgres
```

To install the extension in a custom prefix on PostgreSQL 18 or later, pass
the `prefix` argument to `install` (but no other `make` targets):

    make install prefix=/usr/local/extras

Then ensure that the prefix is included in the following [`postgresql.conf`
parameters]:

```ini
extension_control_path = '/usr/local/extras/postgresql/share:$system'
dynamic_library_path   = '/usr/local/extras/postgresql/lib:$libdir'
```

Once colnames is installed, you can add it to a database. If you're running
PostgreSQL 9.1.0 or greater, it's a simple as connecting to a database as a
super user and running:

``` sql
CREATE EXTENSION colnames;
```

If you've upgraded your cluster to PostgreSQL 9.1 and already had colnames
installed, you can upgrade it to a properly packaged extension with:

``` sql
CREATE EXTENSION colnames FROM unpackaged;
```

For versions of PostgreSQL less than 9.1.0, you'll need to run the
installation script:

``` sh
psql -d my_db -f /path/to/pgsql/share/contrib/colnames.sql
```

If you want to install colnames into a specific schema, use the `PGOPTIONS`
environment variable to specify the schema, like so:

``` sh
PGOPTIONS=--search_path=extensions psql -d my_db -f colnames.sql
```

Dependencies
------------

The `colnames` data type has no dependencies other than PostgreSQL 8.2.0
or higher.

Copyright and License
---------------------

Copyright (c) 2011-2025 Andrew Gierth and David E. Wheeler.

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

  [`postgresql.conf` parameters]: https://www.postgresql.org/docs/devel/runtime-config-client.html#RUNTIME-CONFIG-CLIENT-OTHER
