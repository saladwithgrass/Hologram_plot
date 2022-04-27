#include "segmentfunction.h"

SegmentFunction::SegmentFunction(const double& t0_p, const double& t1_p,
                                 const double& v0_p, const double& v1_p,
                                 const double& x0_p) {
    t0 = t0_p;
    t1 = t1_p;
    v0 = v0_p;
    v1 = v1_p;
    x0 = x0_p;
    a = (v1 - v0) / (t1 - t0);

}

double SegmentFunction::x(const double& t) const {
    return x0 + v0 * (t - t0) + a * (t - t0) * (t - t0) / 2;
}
