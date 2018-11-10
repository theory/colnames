colnames 1.7.0
==============

This extension contains a single SQL function, `colnames()`, that takes a
record value as its argument and returns an array of the names of the columns
in that record. This can be useful for example in trigger functions, where one
might need to get the column names in order to generate a query string.

[![PGXN version](https://badge.fury.io/pg/colnames.svg)](https://badge.fury.io/pg/colnames)
[![Build Status](https://travis-ci.org/theory/colnames.png)](https://travis-ci.org/theory/colnames)

To build colnames, just do this:

    make
    make install
    make installcheck

If you encounter an error such as:

    "Makefile", line 8: Need an operator

You need to use GNU make, which may well be installed on your system as
`gmake`:

    gmake
    gmake installcheck
    gmake install

If you encounter an error such as:

    make: pg_config: Command not found

Be sure that you have `pg_config` installed and in your path. If you used a
package management system such as RPM to install PostgreSQL, be sure that the
`-devel` package is also installed. If necessary tell the build process where
to find it:

    make PG_CONFIG=/path/to/pg_config
    make install PG_CONFIG=/path/to/pg_config
    make installcheck PG_CONFIG=/path/to/pg_config

If you encounter an error such as:

    ERROR:  must be owner of database regression

You need to run the test suite using a super user, such as the default
"postgres" super user:

    make installcheck PGUSER=postgres

Once colnames is installed, you can add it to a database. If you're running
PostgreSQL 9.1.0 or greater, it's a simple as connecting to a database as a
super user and running:

    CREATE EXTENSION colnames;

If you've upgraded your cluster to PostgreSQL 9.1 and already had colnames
installed, you can upgrade it to a properly packaged extension with:

    CREATE EXTENSION colnames FROM unpackaged;

For versions of PostgreSQL less than 9.1.0, you'll need to run the
installation script:

    psql -d mydb -f /path/to/pgsql/share/contrib/colnames.sql

If you want to install colnames into a specific schema, use the `PGOPTIONS`
environment variable to specify the schema, like so:

    PGOPTIONS=--search_path=extensions psql -d mydb -f colnames.sql

Dependencies
------------
The `colnames` data type has no dependencies other than PostgreSQL 8.2.0
or higher.

Copyright and License
---------------------

Copyright (c) 2011-2018 Andrew Gierth and David E. Wheeler.

This module is free software; you can redistribute it and/or modify it under
the [PostgreSQL License](http://www.opensource.org/licenses/postgresql).

Permission to use, copy, modify, and distribute this software and its
documentation for any purpose, without fee, and without a written agreement is
hereby granted, provided that the above copyright notice and this paragraph
and the following two paragraphs appear in all copies.

In no event shall Andrew Gierth or David E. Wheeler be liable to any party for
direct, indirect, special, incidental, or consequential damages, including
lost profits, arising out of the use of this software and its documentation,
even if Andrew Gierth or David E. Wheeler has been advised of the possibility
of such damage.

Andrew Gierth and David E. Wheeler specifically disclaim any warranties,
including, but not limited to, the implied warranties of merchantability and
fitness for a particular purpose. The software provided hereunder is on an "as
is" basis, and Andrew Gierth and David E. Wheeler have no obligations to
provide maintenance, support, updates, enhancements, or modifications.
