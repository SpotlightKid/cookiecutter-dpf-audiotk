/*
 * {{ cookiecutter.project_name }} audio efffect based on DISTRHO Plugin Framework (DPF)
 * Copyright (C) {{ cookiecutter.year }} {{ cookiecutter.full_name }} <{{ cookiecutter.email }}>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include "Plugin{{ cookiecutter.plugin_name }}.hpp"

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------

Plugin{{ cookiecutter.plugin_name }}::Plugin{{ cookiecutter.plugin_name }}()
    : Plugin(paramCount, 1, 0),  // paramCount params, 1 program(s), 0 states
      inFilterL(nullptr, 1, 0, false),
      inFilterR(nullptr, 1, 0, false),
      delayFilter(96000),
      outFilterL(nullptr, 1, 0, false),
      outFilterR(nullptr, 1, 0, false)
{
    sampleRateChanged(getSampleRate());
    loadProgram(0);

    delayFilter.set_input_port(0, &inFilterL, 0);
    delayFilter.set_input_port(1, &inFilterR, 0);
    outFilterL.set_input_port(0, &delayFilter, 0);
    outFilterR.set_input_port(0, &delayFilter, 1);
    endPoint.add_filter(&outFilterL);
    endPoint.add_filter(&outFilterR);
}

// -----------------------------------------------------------------------
// Init

void Plugin{{ cookiecutter.plugin_name }}::initParameter(uint32_t index, Parameter& parameter) {
    if (index >= paramCount)
        return;

    parameter.ranges.min = 0.0f;
    parameter.ranges.max = 1.0f;
    parameter.ranges.def = 0.1f;
    parameter.hints = kParameterIsAutomable;

    switch (index) {
        case paramDelay:
            parameter.name = "Delay";
            parameter.symbol = "delay";
            parameter.ranges.min = 0.1f;
            parameter.ranges.max = 500.0f;
            parameter.ranges.def = 1.0f;
            break;
        case paramBlend:
            parameter.name = "DryWet";
            parameter.symbol = "blend";
            parameter.ranges.min = 0.0f;
            parameter.ranges.max = 100.0f;
            parameter.ranges.def = 100.0f;
            break;
    }

    parameter.symbol = parameter.name;
}

/**
  Set the name of the program @a index.
  This function will be called once, shortly after the plugin is created.
*/
void Plugin{{ cookiecutter.plugin_name }}::initProgramName(uint32_t index, String& programName) {
    switch (index) {
        case 0:
            programName = "Default";
            break;
    }
}

// -----------------------------------------------------------------------
// Internal data

/**
  Optional callback to inform the plugin about a sample rate change.
*/
void Plugin{{ cookiecutter.plugin_name }}::sampleRateChanged(double newSampleRate) {
    fSampleRate = newSampleRate;

    if (fSampleRate != inFilterL.get_output_sampling_rate()) {
        inFilterL.set_input_sampling_rate(fSampleRate);
        inFilterL.set_output_sampling_rate(fSampleRate);
        inFilterR.set_input_sampling_rate(fSampleRate);
        inFilterR.set_output_sampling_rate(fSampleRate);
        delayFilter.set_input_sampling_rate(fSampleRate);
        delayFilter.set_output_sampling_rate(fSampleRate);
        outFilterL.set_input_sampling_rate(fSampleRate);
        outFilterL.set_output_sampling_rate(fSampleRate);
        outFilterR.set_input_sampling_rate(fSampleRate);
        outFilterR.set_output_sampling_rate(fSampleRate);
        endPoint.set_input_sampling_rate(fSampleRate);
        endPoint.set_output_sampling_rate(fSampleRate);
    }
}


/**
  Get the current value of a parameter.
*/
float Plugin{{ cookiecutter.plugin_name }}::getParameterValue(uint32_t index) const {
    return fParams[index];
}

/**
  Change a parameter value.
*/
void Plugin{{ cookiecutter.plugin_name }}::setParameterValue(uint32_t index, float value) {
    fParams[index] = value;

    switch (index) {
        case paramDelay:
            delayFilter.set_delay_ch1(value / 1000. * fSampleRate);
            delayFilter.set_delay_ch2(value / 1000. * fSampleRate);
            break;
        case paramBlend:
            delayFilter.set_blend_ch1(value / 100.);
            delayFilter.set_blend_ch2(value / 100.);
            break;
    }
}

/**
  Load a program.
  The host may call this function from any context,
  including realtime processing.
*/
void Plugin{{ cookiecutter.plugin_name }}::loadProgram(uint32_t index) {
    switch (index) {
        case 0:
            setParameterValue(paramDelay, 120.0f);
            setParameterValue(paramBlend, 30.0f);
            break;
    }
}

// -----------------------------------------------------------------------
// Process

void Plugin{{ cookiecutter.plugin_name }}::activate() {
}

void Plugin{{ cookiecutter.plugin_name }}::run(const float** inputs, float** outputs,
        uint32_t frames) {
    inFilterL.set_pointer(inputs[0], frames);
    inFilterR.set_pointer(inputs[1], frames);
    outFilterL.set_pointer(outputs[0], frames);
    outFilterR.set_pointer(outputs[1], frames);
    endPoint.process(frames);
}

// -----------------------------------------------------------------------

Plugin* createPlugin() {
    return new Plugin{{ cookiecutter.plugin_name }}();
}

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO
