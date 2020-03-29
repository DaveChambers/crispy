/*
  ==============================================================================

    SaturationWindow.h
    Created: 28 Mar 2020 7:59:54am
    Author:  Spenser Saling

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Constants.h"
#include "DebugWindow.h"

//==============================================================================
/*
*/
class SaturationWindow    : public Component, private Slider::Listener
{
public:
    SaturationWindow(AudioProcessorValueTreeState& params) : parameters(params)
    {
        addAndMakeVisible(saturationVisualizer);
        initSlider(oddSlider, oddSliderAttachment, Constants::ID_ODD);
        initSlider(evenSlider, evenSliderAttachment, Constants::ID_EVEN);
    }

    ~SaturationWindow()
    {
        
    }

    void paint (Graphics& g) override
    {
        
    }

    void resized() override
    {
        const int padding = getWidth()*0.03;
        Rectangle<int> bounds = getLocalBounds();
        saturationVisualizer.setBounds(bounds);
        oddSlider.setBounds(bounds.removeFromLeft(getWidth()/2).reduced(padding));
        evenSlider.setBounds(bounds.reduced(padding));
    }
    
    void sliderValueChanged (Slider *slider) override
    {
        DebugWindow::debugLines[2] = String(oddSlider.getValue());
        DebugWindow::debugLines[3] = String(evenSlider.getValue());
        saturationVisualizer.reset(oddSlider.getValue(), evenSlider.getValue(), true);
        repaint();
    }

private:
    AudioProcessorValueTreeState& parameters;
    SaturationVisualizer2 saturationVisualizer;
    Slider oddSlider, evenSlider;
    
    typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
    std::unique_ptr<SliderAttachment> oddSliderAttachment, evenSliderAttachment;
    
    void initSlider(Slider& slider, std::unique_ptr<SliderAttachment>& attachment, String paramId){
        addAndMakeVisible(slider);
        slider.setSliderStyle(Slider::RotaryVerticalDrag);
        slider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
        slider.addListener(this);
        attachment.reset(new SliderAttachment(parameters, paramId, slider));
    }
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SaturationWindow)
};
