#include "bandpassfilter.h"
#include <stdio.h>
#include <string.h>
bandpassfilter::bandpassfilter()
{
    memset(m_delayIn,0,MAXORDER*sizeof(float));
    memset(m_delayOut,0,2*MAXORDER*sizeof(float));
    m_order=1;
    m_cutoff=1000.0;
    m_damp=1.0;
    m_gainDB=-3.0;
    computeCoefficients();

}

void bandpassfilter::computeCoefficients()
{
    int nfac=factorial(m_order);
    float F=2.0*sin(M_PI*m_cutoff/m_sr);
    float Q=2.0*m_damp;

    float a=-2.0+F*F+F*Q;
    float b=1.0-F*Q;
    for(int m=0;m<=2*m_order;m++)
    {
        float coeff=0;
        for(int k=0;k<=m_order;k++)
        {
            int kfac=factorial(k);
            int nOverK=nfac/(kfac*factorial(m_order-k));

            for(int l=0;l<=k;l++)
            {
                if((2*k-l)==m)
                {
                    int kOverL=kfac/(factorial(l)*factorial(k-l));
                    coeff+=nOverK*kOverL*pow(a,l)*pow(b,k-l);
                }
            }
        }
        m_delayOutCoeff[m]=coeff;
        m_delayOut[m]=0.0;
    }

    for(int k=0;k<=m_order;k++)
    {
        int kfac=factorial(k);
        int nOverK=nfac/(kfac*factorial(m_order-k));
        float coeff=nOverK*pow(-1.0,k)*pow(F,m_order);
        m_delayInCoeff[k]=coeff;
        m_delayIn[k]=0.0;
    }

    //Normalize the filter
    double radianfreq=2.0*M_PI*m_cutoff/m_sr;
    double rn=0;
    double in=0;
    double rd=1.0;
    double id=0;

    for(int k=0;k<=m_order;k++)
    {
        rn+=m_delayInCoeff[k]*cos(k*radianfreq);
        in+=m_delayInCoeff[k]*sin(k*radianfreq);
    }

    for(int k=1;k<=2*m_order;k++)
    {
        rd+=m_delayOutCoeff[k]*cos(k*radianfreq);
        id+=m_delayOutCoeff[k]*sin(k*radianfreq);
    }

    double norm=1.0/(rd*rd+id*id)*sqrt(pow(rn*rd+in*id,2.0)+pow(id*rn-in*rd,2.0));

    double gain=pow(10.0,m_gainDB/20.0);
    for(int k=0;k<=m_order;k++)
        m_delayInCoeff[k]*=gain/norm;


}

void bandpassfilter::process(const float *inputs, float *outputs, uint32_t frames)
{
    for(int i=0;i<frames;i++)
    {
        outputs[i]=0;
        int k;
        for(k=0;k<=i&&k<=m_order;k++)
            outputs[i]+=m_delayInCoeff[k]*inputs[i-k];
        for(;k<=m_order;k++)
            outputs[i]+=m_delayInCoeff[k]*m_delayIn[k-i-1];

        int m;
        for(m=1;m<=i&&m<=m_order*2;m++)
            outputs[i]-=m_delayOutCoeff[m]*outputs[i-m];
        for(;m<=m_order*2;m++)
            outputs[i]-=m_delayOutCoeff[m]*m_delayOut[m-i-1];
    }

    for(int i=0;i<=m_order;i++)
        m_delayIn[i]=inputs[frames-1-i];
    for(int i=0;i<=m_order*2;i++)
        m_delayOut[i]=outputs[frames-1-i];

}

int bandpassfilter::factorial(int n)
{
    return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}
