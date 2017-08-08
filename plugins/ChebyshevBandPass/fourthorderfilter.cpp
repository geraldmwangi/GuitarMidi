#include "fourthorderfilter.h"

FourthOrderFilter::FourthOrderFilter()
{
    m_buff=0;
    m_buffsize=0;
    m_delayIn[0]=0.0;
    m_delayIn[1]=0.0;
    m_delayIn[2]=0.0;
    m_delayIn[3]=0.0;

    m_delayOut[0]=0.0;
    m_delayOut[1]=0.0;
    m_delayOut[2]=0.0;
    m_delayOut[3]=0.0;

    m_paramsIn[0]=1.0;
    m_paramsIn[1]=0.0;
    m_paramsIn[2]=0.0;

    m_paramsOut[0]=0.0;
    m_paramsOut[1]=0.0;
    m_paramsOut[2]=0.0;
    m_paramsOut[3]=0.0;
}

FourthOrderFilter::~FourthOrderFilter()
{
    setOutputBufferSize(0);
}

void FourthOrderFilter::setOutputBufferSize(int newsize)
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

void FourthOrderFilter::setParameters(float n0, float n2, float n4, float d1, float d2, float d3, float d4)
{
    m_paramsIn[0]=n0;
    m_paramsIn[1]=n2;
    m_paramsIn[2]=n4;

    m_paramsOut[0]=d1;
    m_paramsOut[1]=d2;
    m_paramsOut[2]=d3;
    m_paramsOut[3]=d4;

    m_delayIn[0]=0.0;
    m_delayIn[1]=0.0;
    m_delayIn[2]=0.0;
    m_delayIn[3]=0.0;

    m_delayOut[0]=0.0;
    m_delayOut[1]=0.0;
    m_delayOut[2]=0.0;
    m_delayOut[3]=0.0;
}

void FourthOrderFilter::process(const float *input, int frames)
{
    if(frames!=m_buffsize)
        setOutputBufferSize(frames);

    for(int i=0;i<4;i++)
    {
        m_buff[i]=input[i]*m_paramsIn[0];
        int i4=i-4;
        if(i4>=0)
            m_buff[i]+=m_paramsIn[2]*input[i4];
        else
            m_buff[i]+=m_paramsIn[2]*m_delayIn[3-i];

        int i2=i-2;
        if(i2>=0)
            m_buff[i]+=m_paramsIn[1]*input[i2];
        else
            m_buff[i]+=m_paramsIn[1]*m_delayIn[1-i];

        for(int j=1;j<=4;j++)
        {
            int ij=i-j;
            if(ij>=0)
                m_buff[i]-=m_paramsOut[j-1]*m_buff[ij];
            else
                m_buff[i]-=m_paramsOut[j-1]*m_delayOut[j-1-i];
        }


    }

    for(int i=4;i<frames;i++)
    {
        m_buff[i]=input[i]*m_paramsIn[0];
         m_buff[i]+=m_paramsIn[2]*input[i-4];



        m_buff[i]+=m_paramsIn[1]*input[i-2];


        for(int j=1;j<=4;j++)
        {

            m_buff[i]-=m_paramsOut[j-1]*m_buff[i-j];

        }


    }

    for(int i=0;i<4;i++)
    {
        m_delayIn[i]=input[frames-1-i];
        m_delayOut[i]=m_buff[frames-1-i];
    }

}

float *FourthOrderFilter::getOutput()
{

    return m_buff;
}
