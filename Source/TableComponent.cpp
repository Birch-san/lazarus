//
//  Model.cpp
//  Lazarus
//
//  Created by Alex Birch on 01/09/2017.
//
//

#include "TableComponent.h"

//==============================================================================
/**
    This class shows how to implement a TableListBoxModel to show in a TableListBox.
*/
TableComponent::TableComponent()
        : font (14.0f)
{
    // Load some data from an embedded XML file..
    loadData();

    // Create our table component and add it to this component..
    addAndMakeVisible (table);
    table.setModel (this);

    // give it a border
    table.setColour (ListBox::outlineColourId, Colours::grey);
    table.setOutlineThickness (1);

    // Add some columns to the table header, based on the column list in our database..
    forEachXmlChildElement (*columnList, columnXml)
    {
        table.getHeader().addColumn (columnXml->getStringAttribute ("name"),
                columnXml->getIntAttribute ("columnId"),
                columnXml->getIntAttribute ("width"),
                50, 400,
                TableHeaderComponent::defaultFlags);
    }

    // we could now change some initial settings..
    table.getHeader().setSortColumnId (1, true); // sort forwards by the ID column
//    table.getHeader().setColumnVisible (7, false); // hide the "length" column until the user shows it

    // un-comment this line to have a go of stretch-to-fit mode
    // table.getHeader().setStretchToFitActive (true);

    table.setMultipleSelectionEnabled (true);
}

// This is overloaded from TableListBoxModel, and must return the total number of rows in our table
int TableComponent::getNumRows()
{
    return numRows;
}

// This is overloaded from TableListBoxModel, and should fill in the background of the whole row
void TableComponent::paintRowBackground (
        Graphics& g,
        int rowNumber,
        int /*width*/,
        int /*height*/,
        bool rowIsSelected
) {
    const Colour alternateColour (getLookAndFeel().findColour (ListBox::backgroundColourId)
            .interpolatedWith (getLookAndFeel().findColour (ListBox::textColourId), 0.03f));
    if (rowIsSelected)
        g.fillAll (Colours::lightblue);
    else if (rowNumber % 2)
        g.fillAll (alternateColour);
}

// This is overloaded from TableListBoxModel, and must paint any cells that aren't using custom
// components.
void TableComponent::paintCell (
        Graphics& g,
        int rowNumber,
        int columnId,
        int width,
        int height,
        bool /*rowIsSelected*/
) {
    g.setColour (getLookAndFeel().findColour (ListBox::textColourId));
    g.setFont (font);

    if (const XmlElement* rowElement = dataList->getChildElement (rowNumber))
    {
        const String text (rowElement->getStringAttribute (getAttributeNameForColumnId (columnId)));

        g.drawText (text, 2, 0, width - 4, height, Justification::centredLeft, true);
    }

    g.setColour (getLookAndFeel().findColour (ListBox::backgroundColourId));
    g.fillRect (width - 1, 0, 1, height);
}

// This is overloaded from TableListBoxModel, and tells us that the user has clicked a table header
// to change the sort order.
void TableComponent::sortOrderChanged (
        int newSortColumnId,
        bool isForwards
) {
    if (newSortColumnId != 0)
    {
        DataSorter sorter (getAttributeNameForColumnId (newSortColumnId), isForwards);
        dataList->sortChildElements (sorter);

        table.updateContent();
    }
}

// // This is overloaded from TableListBoxModel, and must update any custom components that we're using
// Component* TableComponent::refreshComponentForCell (
//         int rowNumber,
//         int columnId,
//         bool /*isRowSelected*/,
//         Component* existingComponentToUpdate
// ) {
//     if (columnId == 1 || columnId == 7) // The ID and Length columns do not have a custom component
//     {
//         jassert (existingComponentToUpdate == nullptr);
//         return nullptr;
//     }
//
//     if (columnId == 5) // For the ratings column, we return the custom combobox component
//     {
//         RatingColumnCustomComponent* ratingsBox = static_cast<RatingColumnCustomComponent*> (existingComponentToUpdate);
//
//         // If an existing component is being passed-in for updating, we'll re-use it, but
//         // if not, we'll have to create one.
//         if (ratingsBox == nullptr)
//             ratingsBox = new RatingColumnCustomComponent (*this);
//
//         ratingsBox->setRowAndColumn (rowNumber, columnId);
//         return ratingsBox;
//     }
//
//     // The other columns are editable text columns, for which we use the custom Label component
//     EditableTextCustomComponent* textLabel = static_cast<EditableTextCustomComponent*> (existingComponentToUpdate);
//
//     // same as above...
//     if (textLabel == nullptr)
//         textLabel = new EditableTextCustomComponent (*this);
//
//     textLabel->setRowAndColumn (rowNumber, columnId);
//     return textLabel;
// }

// This is overloaded from TableListBoxModel, and should choose the best width for the specified
// column.
int TableComponent::getColumnAutoSizeWidth (int columnId) {
    if (columnId == 5)
        return 100; // (this is the ratings column, containing a custom combobox component)

    int widest = 32;

    // find the widest bit of text in this column..
    for (int i = getNumRows(); --i >= 0;)
    {
        if (const XmlElement* rowElement = dataList->getChildElement (i))
        {
            const String text (rowElement->getStringAttribute (getAttributeNameForColumnId (columnId)));

            widest = jmax (widest, font.getStringWidth (text));
        }
    }

    return widest + 8;
}

// A couple of quick methods to set and get cell values when the user changes them
int TableComponent::getRating (const int rowNumber) const
{
    return dataList->getChildElement (rowNumber)->getIntAttribute ("Rating");
}

void TableComponent::setRating (
        const int rowNumber,
        const int newRating
) {
    dataList->getChildElement (rowNumber)->setAttribute ("Rating", newRating);
}

String TableComponent::getText (
        const int columnNumber,
        const int rowNumber
) const {
    return dataList->getChildElement (rowNumber)->getStringAttribute ( getAttributeNameForColumnId(columnNumber));
}

void TableComponent::setText (
        const int columnNumber,
        const int rowNumber,
        const String& newText
) {
    const String& columnName = table.getHeader().getColumnName (columnNumber);
    dataList->getChildElement (rowNumber)->setAttribute (columnName, newText);
}

//==============================================================================
void TableComponent::resized() {
    // position our table with a gap around its edge
    table.setBoundsInset (BorderSize<int> (8));
}

//==============================================================================
// A comparator used to sort our data when the user clicks a column header

TableComponent::DataSorter::DataSorter (
        const String& attributeToSortBy,
        bool forwards
)
        : attributeToSort (attributeToSortBy),
          direction (forwards ? 1 : -1)
{}

int TableComponent::DataSorter::compareElements (
        XmlElement* first,
        XmlElement* second
) const {
    int result = first->getStringAttribute (attributeToSort)
            .compareNatural (second->getStringAttribute (attributeToSort));

    if (result == 0)
        result = first->getStringAttribute ("ID")
                .compareNatural (second->getStringAttribute ("ID"));

    return direction * result;
}

//==============================================================================
// this loads the embedded database XML file into memory
void TableComponent::loadData() {
    demoData = XmlDocument::parse (BinaryData::demo_table_data_xml);

    dataList   = demoData->getChildByName ("DATA");
    columnList = demoData->getChildByName ("COLUMNS");

    numRows = dataList->getNumChildElements();
}

// (a utility method to search our XML for the attribute that matches a column ID)
String TableComponent::getAttributeNameForColumnId (const int columnId) const {
    forEachXmlChildElement (*columnList, columnXml)
    {
        if (columnXml->getIntAttribute ("columnId") == columnId)
            return columnXml->getStringAttribute ("name");
    }

    return String();
}