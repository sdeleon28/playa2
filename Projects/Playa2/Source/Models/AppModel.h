#pragma once

#include <juce_data_structures/juce_data_structures.h>
using namespace juce;

#include "Interfaces/Models/IAppModel.h"

class AppModel final : public IAppModel, public ValueTree::Listener
{
public:
    AppModel (ValueTree appState);
    ~AppModel() override;

    DTO getState() const override;

    void addListener (IAppModel::Listener* listener) override;
    void removeListener (IAppModel::Listener* listener) override;
    void valueTreePropertyChanged (ValueTree& treeWhosePropertyHasChanged,
                                   const Identifier& property) override;
    void togglePlaying() override;
    void notifyUpdate();
private:

    ListenerList<IAppModel::Listener> listeners;
    ValueTree appState;
};
