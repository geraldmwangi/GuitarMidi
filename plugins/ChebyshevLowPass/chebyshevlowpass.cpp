#include "chebyshevlowpass.h"
#include <math.h>
START_NAMESPACE_DISTRHO
ChebyshevLowPass::ChebyshevLowPass():
    Plugin(3, 0, 0),m_filter(false)
{
//    for(int r=0;r<MAXORDER;r++)
//        m_filters[MAXORDER].setOutputBufferSize(getBufferSize());
    m_filter.setBufferSize(getBufferSize());
    m_filter.setFilterParameters(1,500,getSampleRate(),3);

}

ChebyshevLowPass::~ChebyshevLowPass()
{

}

void ChebyshevLowPass::initParameter(uint32_t index, Parameter &parameter)
{

    if(index==0)
    {
//        m_cutoff=1000.0;
        parameter.name="Cuttoff";
        parameter.ranges.min=1;
        parameter.ranges.max=4500.0;
        parameter.unit="Hz";
        parameter.ranges.def=m_filter.getCuttoff();
    }
    else if(index==1)
    {
        parameter.name="Passband Attenuation";
        parameter.ranges.max=10.0;
        parameter.ranges.min=0.1;
        parameter.unit="dB";
        parameter.ranges.def=m_filter.getPassbandAtten();
    }
    else if(index==2)
    {
        parameter.name="Order";
        parameter.ranges.min=1;
        parameter.ranges.max=MAXORDER;
        parameter.unit="";
        parameter.hints=kParameterIsInteger;
        parameter.ranges.def=m_filter.getOrder();
    }

}

float ChebyshevLowPass::getParameterValue(uint32_t index) const
{
    if(index==0)
    {
//        m_cutoff=1000.0;
//        parameter.name="Center";
//        parameter.ranges.min=1;
//        parameter.ranges.max=4500.0;
//        parameter.unit="Hz";
//        parameter.ranges.def=m_centerfreq;
        return m_filter.getCuttoff();
    }
    else if(index==1)
    {
//        parameter.name="Passband Attenuation";
//        parameter.ranges.min=0;
//        parameter.ranges.max=10.0;
//        parameter.unit="dB";
//        parameter.ranges.def=m_passbandatten;
        return m_filter.getPassbandAtten();
    }
    else if(index==2)
    {
//        parameter.name="Order";
//        parameter.ranges.min=1;
//        parameter.ranges.max=5;
//        parameter.unit="";
//        parameter.hints=kParameterIsInteger;
//        parameter.ranges.def=m_order;
        return m_filter.getOrder();
    }
}

void ChebyshevLowPass::setParameterValue(uint32_t index, float value)
{

    if(index==0)
    {
//        m_cutoff=1000.0;
//        parameter.name="Center";
//        parameter.ranges.min=1;
//        parameter.ranges.max=4500.0;
//        parameter.unit="Hz";
//        parameter.ranges.def=m_centerfreq;
        m_filter.setCuttoff(value,getSampleRate());
    }
    else if(index==1)
    {
//        parameter.name="Passband Attenuation";
//        parameter.ranges.min=0;
//        parameter.ranges.max=10.0;
//        parameter.unit="dB";
//        parameter.ranges.def=m_passbandatten;
        m_filter.setPassbandAtten(value,getSampleRate());
    }
    else if(index==2)
    {
//        parameter.name="Order";
//        parameter.ranges.min=1;
//        parameter.ranges.max=5;
//        parameter.unit="";
//        parameter.hints=kParameterIsInteger;
//        parameter.ranges.def=m_order;
        m_filter.setOrder(value,getSampleRate());
    }

}

void ChebyshevLowPass::run(const float **inputs, float **outputs, uint32_t frames)
{
    m_filter.process(inputs[0],outputs[0],frames);

}




Plugin* createPlugin()
{
    return new ChebyshevLowPass();
}
END_NAMESPACE_DISTRHO
