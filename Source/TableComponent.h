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

    // Component* refreshComponentForCell (
    //         int rowNumber,
    //         int columnId,
    //         bool isRowSelected,
    //         Component* existingComponentToUpdate
    // ) override;

    int getColumnAutoSizeWidth (int columnId) override;

    int getRating (const int rowNumber) const;
    void setRating (const int rowNumber, const int newRating);

    String getText (
            const int columnNumber,
            const int rowNumber
    ) const;
    void setText (
            const int columnNumber,
            const int rowNumber,
            const String& newText
    );

    void resized() override;

private:
    TableListBox table;     // the table component itself
    Font font;

    ScopedPointer<XmlElement> demoData;   // This is the XML document loaded from the embedded file "demo table data.xml"
    XmlElement* columnList; // A pointer to the sub-node of demoData that contains the list of columns
    XmlElement* dataList;   // A pointer to the sub-node of demoData that contains the list of data rows
    int numRows;            // The number of rows of data we've got

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