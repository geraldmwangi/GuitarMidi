#include "chebyshevbandpass.h"
#include <math.h>
START_NAMESPACE_DISTRHO
ChebyshevBandPass::ChebyshevBandPass():
    Plugin(4, 0, 0)
{
//    for(int r=0;r<MAXORDER;r++)
//        m_filters[MAXORDER].setOutputBufferSize(getBufferSize());
    m_centerfreq=1000;
    m_bandwidth=1000;
    m_passbandatten=1;
    m_order=1;
    setFilterParameters();

}

ChebyshevBandPass::~ChebyshevBandPass()
{

}

void ChebyshevBandPass::initParameter(uint32_t index, Parameter &parameter)
{

    if(index==0)
    {
//        m_cutoff=1000.0;
        parameter.name="Center";
        parameter.ranges.min=1;
        parameter.ranges.max=4500.0;
        parameter.unit="Hz";
        parameter.ranges.def=m_centerfreq;
    }
    else if(index==1)
    {
        parameter.name="Bandwidth";
        parameter.ranges.min=1;
        parameter.ranges.max=2000.0;
        parameter.unit="Hz";
        parameter.ranges.def=m_bandwidth;
    }
    else if(index==2)
    {
        parameter.name="Passband Attenuation";
        parameter.ranges.max=10.0;
        parameter.ranges.min=0.1;
        parameter.unit="dB";
        parameter.ranges.def=m_passbandatten;
    }
    else if(index==3)
    {
        parameter.name="Order";
        parameter.ranges.min=1;
        parameter.ranges.max=MAXORDER;
        parameter.unit="";
        parameter.hints=kParameterIsInteger;
        parameter.ranges.def=m_order;
    }

}

float ChebyshevBandPass::getParameterValue(uint32_t index) const
{
    if(index==0)
    {
//        m_cutoff=1000.0;
//        parameter.name="Center";
//        parameter.ranges.min=1;
//        parameter.ranges.max=4500.0;
//        parameter.unit="Hz";
//        parameter.ranges.def=m_centerfreq;
        return m_centerfreq;
    }
    else if(index==1)
    {
//        parameter.name="Bandwidth";
//        parameter.ranges.min=1;
//        parameter.ranges.max=100.0;
//        parameter.unit="Hz";
//        parameter.ranges.def=m_bandwidth;
        return m_bandwidth;
    }
    else if(index==2)
    {
//        parameter.name="Passband Attenuation";
//        parameter.ranges.min=0;
//        parameter.ranges.max=10.0;
//        parameter.unit="dB";
//        parameter.ranges.def=m_passbandatten;
        return m_passbandatten;
    }
    else if(index==3)
    {
//        parameter.name="Order";
//        parameter.ranges.min=1;
//        parameter.ranges.max=5;
//        parameter.unit="";
//        parameter.hints=kParameterIsInteger;
//        parameter.ranges.def=m_order;
        return m_order;
    }
}

void ChebyshevBandPass::setParameterValue(uint32_t index, float value)
{

    if(index==0)
    {
//        m_cutoff=1000.0;
//        parameter.name="Center";
//        parameter.ranges.min=1;
//        parameter.ranges.max=4500.0;
//        parameter.unit="Hz";
//        parameter.ranges.def=m_centerfreq;
        m_centerfreq=value;
    }
    else if(index==1)
    {
//        parameter.name="Bandwidth";
//        parameter.ranges.min=1;
//        parameter.ranges.max=100.0;
//        parameter.unit="Hz";
//        parameter.ranges.def=m_bandwidth;
        m_bandwidth=value;
    }
    else if(index==2)
    {
//        parameter.name="Passband Attenuation";
//        parameter.ranges.min=0;
//        parameter.ranges.max=10.0;
//        parameter.unit="dB";
//        parameter.ranges.def=m_passbandatten;
        m_passbandatten=value;
    }
    else if(index==3)
    {
//        parameter.name="Order";
//        parameter.ranges.min=1;
//        parameter.ranges.max=5;
//        parameter.unit="";
//        parameter.hints=kParameterIsInteger;
//        parameter.ranges.def=m_order;
        m_order=value;
    }
    setFilterParameters();
}

void ChebyshevBandPass::run(const float **inputs, float **outputs, uint32_t frames)
{
    m_filters[0].process(inputs[0],frames);
    for(int r=1;r<(m_order);r++)
    {
        m_filters[r].process(m_filters[r-1].getOutput(),frames);
    }
    memcpy(outputs[0],m_filters[m_order-1].getOutput(),frames*sizeof(float));

}

void ChebyshevBandPass::setFilterParameters()
{
    float eps=pow(10.0,0.1*m_passbandatten)-1.0;
    float n=2*m_order;
    float eta=sinh(1.0/(n)*asinh(1.0/eps));
    float om1=tan(M_PI*(m_centerfreq-0.5*m_bandwidth)/getSampleRate());
    float om2=tan(M_PI*(m_centerfreq+0.5*m_bandwidth)/getSampleRate());
    float omegaC=tan(M_PI*m_centerfreq/getSampleRate());
    float omegaBand=om2-om1;//tan(M_PI*(m_bandwidth)/getSampleRate());
    float alpha=omegaC/omegaBand;
    for(int r=1;r<=m_order;r++)
    {
        float Kr=sqrt(eta*eta+pow(sin(r/n*M_PI),2.0));
        float Kr2=sqrt(eta*eta+pow(sin((n-r+1)/n*M_PI),2.0));
        float theta=(2.0*r-1.0)/(2.0*n)*M_PI;
        float ar=2.0*eta*sin(theta);
        float br=pow(cos(theta),2.0)+eta*eta;




        float aDivOm=alpha/omegaC;
        float aMulOm=alpha*omegaC;

        float d0=aDivOm*aDivOm + aDivOm*ar + aMulOm*ar+ 2.0*alpha*alpha+br+ aMulOm*aMulOm;

        float d1=-4*aDivOm*aDivOm-2*aDivOm*ar+2*aMulOm*ar+4*aMulOm*aMulOm;

        float d2=6*aDivOm*aDivOm-4*alpha*alpha-2*br+6*aMulOm*aMulOm;
        float d3=-4*aDivOm*aDivOm+2*aDivOm*ar-2*aMulOm*ar+4*aMulOm*aMulOm;
        float d4=aDivOm*aDivOm - aDivOm*ar - aMulOm*ar+ 2.0*alpha*alpha+br+ aMulOm*aMulOm;

        m_filters[r-1].setParameters(Kr*Kr2/d0,-2*Kr*Kr2/d0,Kr*Kr2/d0,d1/d0,d2/d0,d3/d0,d4/d0);

//        m_filters[r-1].setParameters(K/d0,-2*K/d0,K/d0,d1/d0,d2/d0,d3/d0,d4/d0);

//        m_filters[r-1].setParameters(0.5,0,-0.5,0,0,0,0.5);


    }

}


Plugin* createPlugin()
{
    return new ChebyshevBandPass();
}
END_NAMESPACE_DISTRHO
