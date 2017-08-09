#include "secondorderfilter.h"

SecondOrderFilter::SecondOrderFilter()
{
    m_buff=0;
    m_buffsize=0;
    m_delayIn[0]=0.0;
    m_delayIn[1]=0.0;


    m_delayOut[0]=0.0;
    m_delayOut[1]=0.0;


    m_paramsIn[0]=1.0;
    m_paramsIn[1]=0.0;
    m_paramsIn[2]=0.0;

    m_paramsOut[0]=0.0;
    m_paramsOut[1]=0.0;

}

SecondOrderFilter::~SecondOrderFilter()
{
    setOutputBufferSize(0);
}

void SecondOrderFilter::setOutputBufferSize(int newsize)
{

    if(newsize!=m_buffsize)
    {
        if(m_buff)
        {
            delete [] m_buff;
            m_buff=0;
        }
        if(newsize)
        {
            m_buff=new float[newsize];

            memset(m_buff,0,sizeof(float)*newsize);
        }
        m_buffsize=newsize;
    }

}

void SecondOrderFilter::setFilterCoefficients(float n0, float n1, float n2, float d1, float d2)
{
    m_paramsIn[0]=n0;
    m_paramsIn[1]=n1;
    m_paramsIn[2]=n2;

    m_paramsOut[0]=d1;
    m_paramsOut[1]=d2;


    m_delayIn[0]=0.0;
    m_delayIn[1]=0.0;


    m_delayOut[0]=0.0;
    m_delayOut[1]=0.0;

}

void SecondOrderFilter::process(const float *input, int frames)
{
    if(frames!=m_buffsize)
        setOutputBufferSize(frames);

    for(int i=0;i<2;i++)
    {
        m_buff[i]=input[i]*m_paramsIn[0];
        for(int j=1;j<=2;j++)
        {
            int ij=i-j;
            if(ij>=0)
                m_buff[i]+=m_paramsIn[j]*input[ij];
            else
                m_buff[i]+=m_paramsIn[j]*m_delayIn[j-1-i];
        }

        for(int j=1;j<=2;j++)
        {
            int ij=i-j;
            if(ij>=0)
                m_buff[i]-=m_paramsOut[j-1]*m_buff[ij];
            else
                m_buff[i]-=m_paramsOut[j-1]*m_delayOut[j-1-i];
        }


    }

    for(int i=2;i<frames;i++)
    {
        m_buff[i]=input[i]*m_paramsIn[0];

        for(int j=1;j<=2;j++)
        {

            m_buff[i]+=m_paramsIn[j]*input[i-j];

        }

        for(int j=1;j<=2;j++)
        {

            m_buff[i]-=m_paramsOut[j-1]*m_buff[i-j];

        }


    }

    for(int i=0;i<2;i++)
    {
        m_delayIn[i]=input[frames-1-i];
        m_delayOut[i]=m_buff[frames-1-i];
    }

}

float *SecondOrderFilter::getOutput()
{

    return m_buff;
}
