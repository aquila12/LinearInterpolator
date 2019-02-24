This library does linear interpolation of integers.  It's intended for use with
analogRead() and similar, where an input comes in in an arbitrary unit which
needs converting.

Setting up a suitable table of value is slightly involved because of the way the
interpolator is set up.  You'll need the following information to construct your
conversion table:
- The minimum input value you'll accept (x0)
- A set of points spaced evenly from x0 at a power-of-two step size, with the
  corresponding output values.

For example, to map the square-root law, `y=10*sqrt(x)`, we can produce the
table of values:
| x   | y   |
| ---:| ---:|
|   3	|  17 |
|  19	|  44 |
|  35	|  59 |
|  51	|  71 |
|  67	|  82 |
|  83	|  91 |

For this function, x0 is 3 (as it is the lowest value).  The x coordinates are
separated by 16, which (by requirement) is a power of 2.  `log2(16)` is 4, so
`segment_bits=4`.

Since we have 6 points defined, there are a total of 5 line segments in this
table, so `n_segments=5`.

To create an interpolator based on this table, supply the parameters and the `y`
values:
```
int square_root_law[] = { 17, 44, 59, 71, 82, 91 };
LinearInterpolator li(0, 4, 5, square_root_law);
```

To actually interpolate a value, call `li.interpolate`.  Note the return code
is the status and *not* the output value!
```
int x = analogRead(A0);
int y;
int result = li.interpolate(x, y);
/* Output is in y, if the operation succeeded, otherwise is left unchanged */
```

The result code is one of LININT_OK, LININT_TOO_LOW (if the input was less than
`x0`), or LININT_TOO_HIGH (if the input was outside the table range).

Note that once you've set up the parameters for x (`x0` and `segment_bits`), you
can easily substitute the Y values if required (e.g. to convert to a different
unit), and extend the table as necessary.
