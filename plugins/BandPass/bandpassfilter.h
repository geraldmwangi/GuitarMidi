#ifndef BANDPASSFILTER_H
#define BANDPASSFILTER_H
#include <math.h>
#include <assert.h>
#include <cstdint>
#define MAXORDER 10
class bandpassfilter
{
public:
    bandpassfilter();

    void setOrder(unsigned int order)
    {
        assert(order<MAXORDER);
        m_order=order;
        computeCoefficients();
    }

    void setCutOff(float cutoff)
    {
        m_cutoff=cutoff;
        computeCoefficients();
    }

    void setDamping(float damp)
    {
        m_damp=damp;
        computeCoefficients();
    }

    void setGain(double gaindb)
    {
        m_gainDB=gaindb;
        computeCoefficients();
    }

    void setScale(double scale)
    {
        m_scale=scale;
        computeCoefficients();
    }

    double getScale() const
    {
        return m_scale;
    }

    double getGain() const
    {
        return m_gainDB;
    }

    void setSampleRate(float sr)
    {
        m_sr=sr;
        computeCoefficients();
    }

    unsigned int getOrder() const
    {
        return m_order;
    }

    float getCutOff() const
    {
        return m_cutoff;
    }

    float getDamping() const
    {
        return m_damp;
    }

    void computeCoefficients();

    void process(const float* inputs, float* outputs, uint32_t frames);

private:

    float m_delayIn[MAXORDER];
    float m_delayOut[MAXORDER*2];
    float m_delayInCoeff[MAXORDER];
    float m_delayOutCoeff[MAXORDER*2];
    unsigned int m_order;
    float m_cutoff;
    float m_damp;
    float m_sr;

    double m_gainDB;
    double m_scale;
    int factorial(int n);
};

#endif // BANDPASSFILTER_H
