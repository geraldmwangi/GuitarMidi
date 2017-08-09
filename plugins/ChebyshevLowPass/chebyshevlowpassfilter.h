#ifndef CHEBYSHEVLOWPASSFILTER_H
#define CHEBYSHEVLOWPASSFILTER_H
#include <chebyshevlowpassstage.h>
#define MAXORDER 20
class ChebyshevLowHighPassFilter
{
public:
    ChebyshevLowHighPassFilter(bool highpass);
    void setFilterParameters(int order, float cuttoff, float sr, float passbandattenuation);
    void setBufferSize(int newsize);
    void process(const float* input,float* output,int frames);
    int getOrder() const
    {
        return m_order;
    }

    float getCuttoff() const
    {
        return m_cuttoff;
    }

    float getPassbandAtten() const
    {
        return m_passbandatten;
    }

    void setCuttoff(float value,float sr)
    {
        m_cuttoff=value;
        setFilterParameters(m_order,m_cuttoff,sr,m_passbandatten);
    }

    void setOrder(float value,float sr)
    {
        m_order=value;
        setFilterParameters(m_order,m_cuttoff,sr,m_passbandatten);
    }

    void setPassbandAtten(float value,float sr)
    {
        m_passbandatten=value;
        setFilterParameters(m_order,m_cuttoff,sr,m_passbandatten);
    }

private:
    ChebyshevLowHighPassStage m_stages[MAXORDER];
    int m_order;
    float m_cuttoff;
    float m_passbandatten;
    float m_sr;
    bool m_highpass;
};

#endif // CHEBYSHEVLOWPASSFILTER_H
