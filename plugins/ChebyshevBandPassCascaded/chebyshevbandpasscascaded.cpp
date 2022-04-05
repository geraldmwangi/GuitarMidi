#include "chebyshevbandpasscascaded.h"
#include <math.h>
START_NAMESPACE_DISTRHO
ChebyshevBandPassCascaded::ChebyshevBandPassCascaded():
    Plugin(4, 0, 0),m_highpass(true),m_lowpass(false),m_lowpass2(false)
{
//    for(int r=0;r<MAXORDER;r++)
//        m_filters[MAXORDER].setOutputBufferSize(getBufferSize());
    m_centerfreq=110;
    m_bandwidth=80;
    m_passbandatten=1;
    m_order=2;
    setFilterParameters();

}

ChebyshevBandPassCascaded::~ChebyshevBandPassCascaded()
{

}

void ChebyshevBandPassCascaded::initParameter(uint32_t index, Parameter &parameter)
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
        parameter.ranges.min=0.01;
        parameter.ranges.max=100.0;
        parameter.unit="Hz";
        parameter.ranges.def=m_bandwidth;
    }
    else if(index==2)
    {
        parameter.name="Passband Attenuation";
        parameter.ranges.max=20.0;
        parameter.ranges.min=0.001;
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

float ChebyshevBandPassCascaded::getParameterValue(uint32_t index) const
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

void ChebyshevBandPassCascaded::setParameterValue(uint32_t index, float value)
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

void ChebyshevBandPassCascaded::run(const float **inputs, float **outputs, uint32_t frames)
{

    m_lowpass.process(inputs[0],outputs[0],frames);
    m_highpass.process(outputs[0],outputs[0],frames);
//    m_lowpass2.process(outputs[0],outputs[0],frames);

}

void ChebyshevBandPassCascaded::setFilterParameters()
{
    float highf=m_centerfreq+0.5*m_bandwidth;
    float lowf=m_centerfreq-0.5*m_bandwidth;

    m_highpass.setFilterParameters(m_order,lowf,getSampleRate(),m_passbandatten);
    m_lowpass.setFilterParameters(m_order,highf,getSampleRate(),m_passbandatten);
    m_lowpass2.setFilterParameters(m_order,highf,getSampleRate(),m_passbandatten);

}


Plugin* createPlugin()
{
    return new ChebyshevBandPassCascaded();
}
END_NAMESPACE_DISTRHO
