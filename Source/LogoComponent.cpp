/*
  ==============================================================================

    LogoComponent.cpp
    Created: 6 May 2020 10:38:42pm
    Author:  Joe McLean

  ==============================================================================
*/

#include <JuceHeader.h>
#include "LogoComponent.h"

//==============================================================================
LogoComponent::LogoComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

LogoComponent::~LogoComponent()
{
}

void LogoComponent::paint (Graphics& g)
{
    g.setColour (Colours::white);
    g.setFont (18.0f);
    g.drawText ("Simple Sampler", getLocalBounds().reduced(16, 16),
                Justification::centredLeft, true);
}

void LogoComponent::resized()
{
}
