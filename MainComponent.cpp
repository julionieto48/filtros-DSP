/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"
#include <iostream>
using namespace std;
//==============================================================================
MainComponent::MainComponent()
{
    //ComboBox
    addAndMakeVisible (textLabel); textLabel.setFont (textFont);
    addAndMakeVisible (styleMenu);
    styleMenu.addItem ("Low Pass", 1); styleMenu.addItem ("High Pass", 2);
    styleMenu.addItem ("Band Pass", 3); styleMenu.addItem ("Parametric", 4);
    
    styleMenu2.addItem ("Forma Directa II", 1);
    styleMenu2.onChange = [this] {styleMenuChanged2();};
    
    styleMenu.onChange = [this]
    {
        styleMenuChanged();
        // finke
        if (opcion == 0) {
            
            removeAllChildren();
            addAndMakeVisible (textLabel); addAndMakeVisible (styleMenu);
            // slider frec corte
            addAndMakeVisible(cutoff_fSlider);
            cutoff_fSlider.setRange(50, 22000);
            cutoff_fSlider.setSkewFactorFromMidPoint(11000);
            cutoff_fSlider.setValue(10000, dontSendNotification);
            cutoff_fSlider.setTextValueSuffix(" Hz");
            // Label frecuencia
            addAndMakeVisible(cutoff_fLabel);
            cutoff_fLabel.setText("Frecuencia", dontSendNotification);
            cutoff_fLabel.attachToComponent(& cutoff_fSlider, 1);
            cutoff_fSlider.onValueChange = [this]
            {
                targetFrequency = cutoff_fSlider.getValue();
                mFilter.setCutoff(2*targetFrequency/44100);
            };
            
            // slider resonancia
            addAndMakeVisible(resonanceSlider);
            resonanceSlider.setRange(0.0, 1.0);
            resonanceSlider.setSkewFactorFromMidPoint(0.5);
            resonanceSlider.setValue (0.5, dontSendNotification);
            // Label resonancia
            addAndMakeVisible(resonanceLabel);
            resonanceLabel.setText("Resonancia", dontSendNotification);
            resonanceLabel.attachToComponent(& resonanceSlider, 1);
            resonanceSlider.onValueChange = [this]
            {
                targetResonance = resonanceSlider.getValue();
                mFilter.setResonance(targetResonance);
            };
            // dB_Slider
            //===========================================================================
            decibelSlider.setRange (-100, -12);
            decibelSlider.setTextBoxStyle (Slider::TextBoxRight, false, 100, 20);
            decibelSlider.onValueChange = [this]
            {
                level = Decibels::decibelsToGain ((float) decibelSlider.getValue());
            };
            decibelSlider.setValue (Decibels::gainToDecibels (level));
            decibelLabel.setText ("Nivel de Ruido dB", dontSendNotification);
            addAndMakeVisible (decibelSlider);
            addAndMakeVisible (decibelLabel);
        }
        // parametrico kuo
        else if (opcion == 1) {
            removeAllChildren(); addAndMakeVisible (textLabel); addAndMakeVisible (styleMenu);
            
            // dB_Slider
            //===========================================================================
            decibelSlider.setRange (-100, -12);
            decibelSlider.setTextBoxStyle (Slider::TextBoxRight, false, 100, 20);
            decibelSlider.onValueChange = [this]
            {level = Decibels::decibelsToGain ((float) decibelSlider.getValue());};
            decibelSlider.setValue (Decibels::gainToDecibels (level));
            decibelLabel.setText ("Nivel [dB]", dontSendNotification);
            addAndMakeVisible (decibelSlider);
            addAndMakeVisible (decibelLabel);
            // slider frec corte
            addAndMakeVisible(cutoff_fSlider);
            cutoff_fSlider.setRange(50, 22000);
            cutoff_fSlider.setSkewFactorFromMidPoint(11000);
            cutoff_fSlider.setValue(10000, dontSendNotification);
            cutoff_fSlider.setTextValueSuffix(" [Hz]");
            //Label frec
            addAndMakeVisible(cutoff_fLabel);
            cutoff_fLabel.setText("Frecuencia", dontSendNotification);
            cutoff_fLabel.attachToComponent(& cutoff_fSlider, 1);
            cutoff_fSlider.onValueChange = [this]
            {
                targetFrequency = cutoff_fSlider.getValue();
                mParametric.setf(targetFrequency);
            };
            //r_z_Slider
            addAndMakeVisible(r_zSlider);
            r_zSlider.setRange(0.0, 1.0);
            r_zSlider.setSkewFactorFromMidPoint(0.5);
            r_zSlider.setValue (0.5, dontSendNotification);
            //Label
            addAndMakeVisible(r_zLabel);
            r_zLabel.setText("Rz", dontSendNotification);
            r_zLabel.attachToComponent(& r_zSlider, 1);
            r_zSlider.onValueChange = [this]
            {
                target_r_z = r_zSlider.getValue();
                mParametric.setr_z(target_r_z);
            };
            //r_p_Slider
            addAndMakeVisible(r_pSlider);
            r_pSlider.setRange(0.0, 0.99);
            r_pSlider.setSkewFactorFromMidPoint(0.5);
            r_pSlider.setValue (0.3, dontSendNotification);
            //Label
            addAndMakeVisible(r_pLabel);
            r_pLabel.setText("Rp", dontSendNotification);
            r_pLabel.attachToComponent(& r_pSlider, 1);
            r_pSlider.onValueChange = [this]
            {
                target_r_p = r_pSlider.getValue();
                mParametric.setr_p(target_r_p);
            };
            addAndMakeVisible (textLabel2);
            textLabel2.setFont (textFont2);
            addAndMakeVisible (styleMenu2);
        }
    };
    styleMenu.setSelectedId (1); styleMenu2.setSelectedId (1);
    

    
    // elementos default
    setAudioChannels (0, 2); setSize (800, 600);
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{}
//==============================================================================
void MainComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    bufferToFill.clearActiveBufferRegion();
    // usando Finke...
    if (opcion == 0){
        auto currentLevel = level; auto levelScale = currentLevel * 2.0f;
        for (auto channel = 0; channel < bufferToFill.buffer->getNumChannels(); ++channel)
            {
                auto* buffer = bufferToFill.buffer->getWritePointer (channel, bufferToFill.startSample);
                
                for (auto sample = 0; sample < bufferToFill.numSamples; ++sample)
                    buffer[sample] = mFilter.process(random.nextFloat() * levelScale - currentLevel);
            }
    }
    
    // usando kuo...
    if (opcion == 1){
        auto currentLevel = level; auto levelScale = currentLevel * 2.0f;
        for (auto channel = 0; channel < bufferToFill.buffer->getNumChannels(); ++channel)
        {
            auto* buffer = bufferToFill.buffer->getWritePointer (channel, bufferToFill.startSample);
            
            for (auto sample = 0; sample < bufferToFill.numSamples; ++sample)
                
                buffer[sample] = mParametric.proceso(random.nextFloat() * levelScale - currentLevel,,) }
    }
    
    
    
 
    
}

//==============================================================================
void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
}

//==============================================================================


void MainComponent::resized()
// setBounds (int x, int y, int width, int height)
{
    const int limite = 120;
    cutoff_fSlider.setBounds(limite, 20, getWidth() - limite, 20);
    resonanceSlider.setBounds(limite, 50, getWidth() - limite, 50);
    //==============================================================================
    r_zSlider.setBounds(40 , 50, getWidth() - 450, 50);
    r_pSlider.setBounds(440, 50, getWidth() - 450, 50);
    //==============================================================================
    textLabel.setBounds(10, 170, getWidth() - limite, 40);
    styleMenu.setBounds(limite, 170, getWidth() - limite, 40);
    
    textLabel2.setBounds(10, 220, getWidth() - limite, 40);
    styleMenu2.setBounds(limite, 220, getWidth() - limite, 40);
    //==============================================================================
    decibelLabel .setBounds (10, 100, 120, 50);
    decibelSlider.setBounds (130, 100, getWidth() - 140, 50);

}
