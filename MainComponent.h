/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Filter.h"
#include "Parametricfilter.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent   : public AudioAppComponent
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    //==============================================================================
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    //==============================================================================
    void releaseResources() override;

    //==============================================================================
    void resized() override;
    //==============================================================================
    // decibel slider
    class DecibelSlider : public Slider
    {
    public:
        DecibelSlider() {}
        
        double getValueFromText (const String& text) override
        {
            auto minusInfinitydB = -100.0;
            auto decibelText = text.upToFirstOccurrenceOf ("dB", false, false).trim();    // [1]
            return decibelText.equalsIgnoreCase ("-INF") ? minusInfinitydB
            : decibelText.getDoubleValue();  // [2]
        }
        
        String getTextFromValue (double value) override
        {
            return Decibels::toString (value);
        }
        
    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DecibelSlider)
    };
    //==============================================================================


    
private:
    //==============================================================================
    // Your private member variables go here...
    Filter mFilter; Parametricfilter mParametric;
    //==============================================================================
    // sliders
    Slider cutoff_fSlider; Label cutoff_fLabel;
    //==============================================================================
    Random random;DecibelSlider decibelSlider;Label decibelLabel;float level = 0.0f;
    //==============================================================================
    Slider resonanceSlider; Label resonanceLabel;
    float targetResonance = 0.5, targetFrequency = 10000.0;
    //==============================================================================
    Slider r_zSlider; Label r_zLabel;
    Slider r_pSlider; Label r_pLabel;
    float target_r_z = 0.5, target_r_p = 0.3;
    //==============================================================================
    // combo box
    Label textLabel { {}, "Filtro" };Font textFont   { 12.0f };ComboBox styleMenu;
    int opcion;
    void styleMenuChanged()
    {
        switch (styleMenu.getSelectedId())
        {
            case 1:
                opcion = 0;
                mFilter.setFilterMode(Filter::FILTER_MODE_LOWPASS); break;
            case 2:
                opcion = 0;
                mFilter.setFilterMode(Filter::FILTER_MODE_HIGHPASS); break;
            case 3:
                opcion = 0;
                mFilter.setFilterMode(Filter::FILTER_MODE_BANDPASS); break;
            case 4:
                opcion = 1; break;
        }
        textLabel.setFont (textFont);
    }
    //==============================================================================
    Label textLabel2 { {}, " Realizacion Kuo:" };Font textFont2   { 12.0f }; ComboBox styleMenu2;
    int seleccion = 0;
    void styleMenuChanged2()
    {
        switch (styleMenu2.getSelectedId())
        {
            case 1:
                seleccion = 0;
                mParametric.setRealizacion(Parametricfilter::Forma_Directa_II); break;
        }
        textLabel2.setFont (textFont2);
    }
    
    
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
