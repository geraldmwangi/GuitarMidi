#include <bandpass.h>
#include <math.h>
#include <stdlib.h>
START_NAMESPACE_DISTRHO
BandPass::BandPass():
    Plugin(5, 0, 0)
{
    int frames=getBufferSize();
    for(int i=0;i<NUM_FILTERS;i++)
    {
        m_filter[i].setSampleRate(getSampleRate());
        m_outbuffers[i]=new float[frames];
    }



}

BandPass::~BandPass()
{
    for(int i=0;i<NUM_FILTERS;i++)
        delete [] m_outbuffers[i];
}



void BandPass::initParameter(uint32_t index, Parameter &parameter)
{


    if(index==0)
    {
//        m_cutoff=1000.0;
        parameter.name="CutOff";
        parameter.ranges.min=1;
        parameter.ranges.max=4500.0;
        parameter.unit="Hz";
        parameter.ranges.def=m_filter[0].getCutOff();
    }
    else if(index==1)
    {
//        m_damp=1.0;
        parameter.name="Damping Factor";
        parameter.ranges.min=0;
        parameter.ranges.max=1.0;
        parameter.unit="";
        parameter.ranges.def=m_filter[0].getDamping();
    }
    else if(index==2)
    {
        parameter.name="Order";
        parameter.ranges.min=0;
        parameter.ranges.max=10.0;
        parameter.unit="";
        parameter.hints=kParameterIsInteger;
        parameter.ranges.def=m_filter[0].getOrder();
    }
    else if(index==3)
    {
        parameter.name="Gain";
        parameter.ranges.min=-20.0;
        parameter.ranges.max=10.0;
        parameter.unit="dB";

        parameter.ranges.def=m_filter[0].getGain();
    }
    else if(index==4)
    {
        parameter.name="pole rescale factor";
        parameter.ranges.min=0.1;
        parameter.ranges.max=10.0;
        parameter.ranges.def=m_filter[0].getScale();
    }



}

float BandPass::getParameterValue(uint32_t index) const
{
    if(index==0)
        return m_filter[0].getCutOff();
    else if(index==1)
        return m_filter[0].getDamping();
    else if(index==2)
        return m_filter[0].getOrder();
    else if(index==3)
        return m_filter[0].getGain();
    else
        return m_filter[0].getScale();

}

void BandPass::setParameterValue(uint32_t index, float value)
{
    if(index==0)
        for(int i=0;i<NUM_FILTERS;i++)
            m_filter[i].setCutOff((i+1)*value);
    else if(index==1)
        for(int i=0;i<NUM_FILTERS;i++)
            m_filter[i].setDamping(value);
    else if(index==2)
        for(int i=0;i<NUM_FILTERS;i++)
            m_filter[i].setOrder(value);
    else if(index==3)
        for(int i=0;i<NUM_FILTERS;i++)
            m_filter[i].setGain(value);
    else
        for(int i=0;i<NUM_FILTERS;i++)
            m_filter[i].setScale(value);
}

void BandPass::run(const float **inputs, float **outputs, uint32_t frames)
{

    resizeBuffers(frames);
//    m_filter[0].process(inputs[0],m_outbuffers[0],frames);
    for(int i=0;i<NUM_FILTERS;i++)
        m_filter[i].process(inputs[0],m_outbuffers[i],frames);
    for(int f=0;f<frames;f++)
    {
        outputs[0][f]=0.0;
        for(int i=0;i<NUM_FILTERS;i++)
            outputs[0][f]+=m_outbuffers[i][f]/((double)NUM_FILTERS);
    }



}

int BandPass::factorial(int n)
{
    return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

void BandPass::resizeBuffers(int newsize)
{
    if(newsize!=m_buffersize)
    {
        for(int i=0;i<NUM_FILTERS;i++)
        {
            delete [] m_outbuffers[i];
            m_outbuffers[i]=new float[newsize];
        }
        m_buffersize=newsize;
    }

}
Plugin* createPlugin()
{
    return new BandPass();
}
END_NAMESPACE_DISTRHO
