//
//  Model.hpp
//  Lazarus
//
//  Created by Alex Birch on 01/09/2017.
//
//

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class TableComponent    : public Component,
                          public TableListBoxModel {
public:
    TableComponent();

    int getNumRows() override;

    void paintRowBackground (
            Graphics& g,
            int rowNumber,
            int width,
            int height,
            bool rowIsSelected
    ) override;
    void paintCell (
            Graphics& g,
            int rowNumber,
            int columnId,
            int width,
            int height,
            bool rowIsSelected
    ) override;

    void sortOrderChanged (int newSortColumnId, bool isForwards) override;

    int getColumnAutoSizeWidth (int columnId) override;

    void resized() override;

private:
    TableListBox table;     // the table component itself
    Font font;

    ScopedPointer<XmlElement> demoData;   // This is the XML document loaded from the embedded file "demo table data.xml"
    std::vector<String> columnList;
    std::vector<std::vector<String>> dataList;

    void loadData();
    String getAttributeNameForColumnId (const int columnId) const;

    // A comparator used to sort our data when the user clicks a column header
    class DataSorter {
    public:
        DataSorter (
                const String& attributeToSortBy,
                bool forwards
        );

        int compareElements (
                XmlElement* first,
                XmlElement* second
        ) const;

    private:
        String attributeToSort;
        int direction;
    };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TableComponent)
};