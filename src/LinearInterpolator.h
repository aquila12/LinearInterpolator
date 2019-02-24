/* Linear interpolation using piecewise line segments */
/* 2019 Nick Moriarty */

#define LININT_OK 0
#define LININT_TOO_LOW -1
#define LININT_TOO_HIGH 1

class LinearInterpolator {
public:
  LinearInterpolator(int x0, int segment_bits, int n_segments, int y[]);
  int interpolate(int x, int& y);
private:
  int _x0, _seg_bits, _seg_mask, _n_segs;
  int *_y;
};
