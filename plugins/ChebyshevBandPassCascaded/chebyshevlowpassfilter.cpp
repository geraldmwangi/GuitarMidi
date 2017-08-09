#include "chebyshevlowpassfilter.h"
#include <string.h>
ChebyshevLowHighPassFilter::ChebyshevLowHighPassFilter(bool highpass)
{
    m_highpass=highpass;

}

void ChebyshevLowHighPassFilter::setFilterParameters(int order, float cuttoff, float sr, float passbandattenuation)
{
    m_order=order;
    m_cuttoff=cuttoff;
    m_passbandatten=passbandattenuation;
    m_sr=sr;
    for(int i=0;i<order;i++)
        m_stages[i].setFilterParameters(i+1,order,cuttoff,sr,passbandattenuation,m_highpass);

}

void ChebyshevLowHighPassFilter::setBufferSize(int newsize)
{
    for(int i=0;i<MAXORDER;i++)
        m_stages[i].setOutputBufferSize(newsize);
}

void ChebyshevLowHighPassFilter::process(const float *input, float *output, int frames)
{
    m_stages[0].process(input,frames);
    for(int r=1;r<(m_order);r++)
    {
        m_stages[r].process(m_stages[r-1].getOutput(),frames);
    }
    memcpy(output,m_stages[m_order-1].getOutput(),frames*sizeof(float));
}
