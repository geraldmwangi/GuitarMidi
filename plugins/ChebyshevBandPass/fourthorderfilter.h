#ifndef FOURTHORDERFILTER_H
#define FOURTHORDERFILTER_H
#include <stdio.h>
#include <string.h>
//FourthOrderFilter is a filter of the form (n0 + n2*z^-2 + n4*z^-4)/(1+d1*z^-1 +d2*z^-2 + d3*z^-3 + d4*z^-4).
//Thus the numerator only has even powers of z. This is sufficient for Chebyshev bandpass filters (type I).
class FourthOrderFilter
{
public:
    FourthOrderFilter();
    ~FourthOrderFilter();
    void setOutputBufferSize(int newsize);
    void setParameters(float n0,float n2, float n4,float d1,float d2,float d3,float d4);
    void process(const float* input, int frames);
    float *getOutput();
private:
    float m_delayIn[4];
    float m_paramsIn[3];
    float m_delayOut[4];
    float m_paramsOut[4];

    float* m_buff;
    unsigned int m_buffsize;
};

#endif // FOURTHORDERFILTER_H
