#ifndef CHEBYSHEVBANDPASS_H
#define CHEBYSHEVBANDPASS_H
#include <DistrhoPlugin.hpp>
#include <fourthorderfilter.h>
#define MAXORDER 10
START_NAMESPACE_DISTRHO
class ChebyshevBandPass:
        public Plugin
{
public:
    ChebyshevBandPass();
    ~ChebyshevBandPass();

protected:
   /* --------------------------------------------------------------------------------------------------------
    * Information */

   /**
      Get the plugin label.
      A plugin label follows the same rules as Parameter::symbol, with the exception that it can start with numbers.
    */
    const char* getLabel() const override
    {
    return "ChebyshevBandPass";
    }

   /**
      Get an extensive comment/description about the plugin.
    */
    const char* getDescription() const override
    {
    return "Filter which output a chebyshev bandpass  signal.";
    }

   /**
      Get the plugin author/maker.
    */
    const char* getMaker() const override
    {
    return "JimsonDrift";
    }

   /**
      Get the plugin homepage.
    */
    const char* getHomePage() const override
    {
    return "https://github.com/geraldmwangi/GuitarMidi";
    }

   /**
      Get the plugin license name (a single line of text).
      For commercial plugins this should return some short copyright information.
    */
    const char* getLicense() const override
    {
    return "GPL";
    }

   /**
      Get the plugin version, in hexadecimal.
    */
    uint32_t getVersion() const override
    {
    return d_version(1, 0, 0);
    }

   /**
      Get the plugin unique Id.
      This value is used by LADSPA, DSSI and VST plugin formats.
    */
    int64_t getUniqueId() const override
    {
    return d_cconst('j', 'i', 'd', 'r');
    }

    void initParameter(uint32_t index, Parameter& parameter) override;
    float getParameterValue(uint32_t index) const override;
    void setParameterValue(uint32_t index, float value) override;
    void run(const float** inputs, float** outputs, uint32_t frames) override;
private:
    void setFilterParameters();
    FourthOrderFilter m_filters[MAXORDER];
    unsigned int m_order; //the real order is 2*m_order
    float m_centerfreq;
    float m_bandwidth;
    float m_passbandatten;

};
END_NAMESPACE_DISTRHO
#endif // CHEBYSHEVBANDPASS_H
