/*
 * LowPass filter
 * Copyright (C) 2017 Gerald Mwangi <gerald.mwangi@gmx.de>
 *
 * Permission to use, copy, modify, and/or distribute this software for any purpose with
 * or without fee is hereby granted, provided that the above copyright notice and this
 * permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD
 * TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN
 * NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER
 * IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
#ifndef LOWPASS_H
#define LOWPASS_H
#include <DistrhoPlugin.hpp>
#include <bandpassfilter.h>
#define NUM_FILTERS 2
START_NAMESPACE_DISTRHO
class BandPass:
        public Plugin
{
public:
    BandPass();
    ~BandPass();


protected:
   /* --------------------------------------------------------------------------------------------------------
    * Information */

   /**
      Get the plugin label.
      A plugin label follows the same rules as Parameter::symbol, with the exception that it can start with numbers.
    */
    const char* getLabel() const override
    {
    return "BandPass";
    }

   /**
      Get an extensive comment/description about the plugin.
    */
    const char* getDescription() const override
    {
    return "Filter which output a  bandpass  signal."
           "The order of the filter is 2*order. The damping factor allows for resonant sounds when set near zero. TREAT WITH CAUTION,"
           "YOU CAN DAMAGE YOU EARS!";
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
    bandpassfilter m_filter[NUM_FILTERS];
    int m_buffersize;
    float *m_outbuffers[NUM_FILTERS];
    int factorial(int n);
    void resizeBuffers(int newsize);
};

END_NAMESPACE_DISTRHO
#endif // LOWPASS_H
