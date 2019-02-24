/* Linear interpolation using piecewise line segments */
/* 2019 Nick Moriarty */

#include "LinearInterpolator.h"

LinearInterpolator::LinearInterpolator(int x0, int segment_bits, int n_segments, int y[]) {
  _x0 = x0;
  _seg_bits = segment_bits;
  _seg_mask = (1 << segment_bits) - 1;
  _n_segs = n_segments;
  _y = y;
}

int LinearInterpolator::interpolate(int x, int& y) {
  int seg, d_x, D_y, d_y;

  x -= _x0;                      /* Correct for input zero-offset */
  if(x < 0) return LININT_TOO_LOW;

  seg = x >> _seg_bits;   /* Get the segment / bucket number */
  d_x = x & _seg_mask;    /* Get the segment input coordinate */

  /* Permit use of bucket N for d_x = 0 only */
  if(seg == _n_segs && d_x == 0);
  else if(seg >= _n_segs) return LININT_TOO_HIGH;

  if(d_x == 0) {
    d_y = 0;
  } else {
    D_y = _y[seg+1] - _y[seg];
    d_y = ((D_y * d_x) >> _seg_bits);
  }

  y = _y[seg] + d_y;
  return LININT_OK;
}
