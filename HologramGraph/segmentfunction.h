#ifndef SEGMENTFUNCTION_H
#define SEGMENTFUNCTION_H


class SegmentFunction {
private:
    double t0, t1, v0, v1, a, x0;
public:
    SegmentFunction(const double& t0_p = 0, const double& t1_p = 0,
                    const double& v0_p = 0, const double& v1_p = 0,
                    const double& x0_p = 0);
    double x(const double& t) const;
    double getT0() const { return t0; }
    double getT1() const { return t1; }
    double getX0() const { return x0; }
};

#endif // SEGMENTFUNCTION_H
