/* Linear interpolation routines */
/* 2019 Nick Moriarty */

#include "LinearInterpolator.h"

#include <iostream>
using namespace std;

/* Spec tests */
const char* context;
int passes, failures;
#define when(desc) context=desc
#define test(desc, subj, comp) if(!(subj comp)) { ++failures; cout << "Failed: When " << context << " " desc " - " #subj " " #comp ", was " << subj; } else ++passes
#define report() cout << "Tests finished; " << passes << " passes, " << failures << " failures" << endl; return 0

int main() {
  /* Test is for a 150k-loaded 100k NTC thermistor being read via an analogue
     port, input values 0-1023 fullscale, output values in deg C * 100 */
  int loaded_thermistor[] = {-691, -392, -119, 136, 376, 607, 830, 1049, 1265, 1480, 1697, 1916, 2139, 2369, 2607, 2857, 3121, 3404};

  LinearInterpolator li(180, 5, 17, loaded_thermistor);

  int r, y;

  when("Attempting to interpolate beyong the minimum input");
  y = 0xcafe;
  r = li.interpolate(179, y);
  test("the operation should fail as too low", r, == LININT_TOO_LOW);
  test("the y value should be unchanged", y, == 0xcafe);

  when("Attempting to interpolate with the minimum input");
  y = 0;
  r = li.interpolate(180, y);
  test("the operation should succeed", r, == LININT_OK);
  test("the y value should be correct", y, == -691);

  when("Attempting to interpolate at a segment point");
  y = 0;
  r = li.interpolate(180+32, y);
  test("the operation should succeed", r, == LININT_OK);
  test("the y value should be correct", y, == -392);

  when("Attempting to interpolate on a segment");
  y = 0;
  r = li.interpolate(542, y);
  test("the operation should succeed", r, == LININT_OK);
  test("the y value should be correct", y, == 1985);

  when("Attempting to interpolate at the maximum input");
  y = 0;
  r = li.interpolate(180 + 32*17, y);
  test("the operation should succeed", r, == LININT_OK);
  test("the y value should be correct", y, == 3404);

  when("Attempting to interpolate beyond the maximum input");
  y = 0xcafe;
  r = li.interpolate(180 + 32*17 + 1, y);
  test("the operation should fail as too high", r, == LININT_TOO_HIGH);
  test("the y value should be unchanged", y, == 0xcafe);

  report();
}
