#include "../../fcu_core.h"
#if 0
// The index for this table is the measured velocity (probably scaled by some value)
// The 4 values in the table are Kp, Ki, Kd, and Ts constants to compute the brake gap
// TODO: add real values, these are examples
#ifndef WIN32
const Lfloat32 f32A34_GainsTable[] = {
#else
Lfloat32 f32A34_GainsTable[] = {
#endif
0.378, 0.17, 0.206, 0.0183,
0.378, 0.17, 0.206, 0.0183,
0.378, 0.17, 0.206, 0.0183,
0.378, 0.17, 0.206, 0.0183
};

#endif //0

