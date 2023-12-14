#include "SettingsMenu.h"


SettingsMenu::SettingsMenu(QWidget* parent)
    : QWidget(parent)
{
    QVBoxLayout* main_layout = new QVBoxLayout(this);

    QFormLayout *formLayout = new QFormLayout(this);

    fontSizeField = new QLineEdit;
    QLabel* fontSizeLabel = new QLabel("Font size: ");
    fontSizeField->setValidator( new QIntValidator(6, 100, this));
    fontSizeField->insert(fontSize);
    formLayout->addRow(fontSizeLabel, fontSizeField);

    QLabel* fontColorLabel = new QLabel("Font color: ");
    fontColorField = new QComboBox;
    fontColorField->addItems(colors);
    fontColorField->setCurrentText(fontColor);
    formLayout->addRow(fontColorLabel, fontColorField);

    QLabel* backgroundColorLabel = new QLabel("Background color");
    backgroundColorField = new QComboBox;
    backgroundColorField->addItems(colors);
    backgroundColorField->setCurrentText(backgroundColor);
    formLayout->addRow(backgroundColorLabel, backgroundColorField);

    main_layout->addLayout(formLayout);

    QPushButton* save_button = new QPushButton(tr("Save changes"));
    connect(save_button, SIGNAL(clicked()), this, SLOT(saveChanges()));
    main_layout->addWidget(save_button);

    main_layout->setAlignment(Qt::AlignCenter);
    this->setLayout(main_layout);
}


QString SettingsMenu::getFontSize() const
{
    return fontSize;
}


QString SettingsMenu::getFontColor() const
{
    return fontColor;
}


QString SettingsMenu::getBackgroundColor() const
{
    return backgroundColor;
}


void SettingsMenu::saveChanges()
{
    fontSize = fontSizeField->text();
    fontColor = fontColorField->currentText();
    backgroundColor = backgroundColorField->currentText();

    emit fontSizeChanged();
    emit fontColorChanged();
    emit backgroundColorChanged();
}


void SettingsMenu::importXml()
{
    auto filename = QFileDialog::getOpenFileName(this, tr("Open setting`s file"), "./", tr("Settings (*.xml)"));

    QFile* file = new QFile(filename); 
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }
    QXmlStreamReader xml(file);

    xml.readNext();

    
    while (!xml.atEnd() && !xml.hasError())
    {
        QXmlStreamReader::TokenType token = xml.readNext();
        if (token == QXmlStreamReader::StartDocument)
        {
            continue;
        }
        if(token == QXmlStreamReader::Invalid)
        {
            qDebug() << xml.errorString();
        }
        if (token == QXmlStreamReader::StartElement)
        {
            if (xml.name() == "FontSize")
            {
                xml.readNext();
                fontSize = xml.text().toString();
                fontSizeField->insert(fontSize);
            }
            else if (xml.name() == "FontColor")
            {
                xml.readNext();
                fontColor = xml.text().toString();
                fontColorField->setCurrentText(fontColor);
            }
            else if (xml.name() == "BackgroundColor")
            {
                xml.readNext();
                backgroundColor = xml.text().toString();
                backgroundColorField->setCurrentText(backgroundColor);
            }
            xml.readNext();
        }
    }

    emit fontSizeChanged();
    emit fontColorChanged();
    emit backgroundColorChanged();
}


void SettingsMenu::exportXml()
{
    QFile* file = new QFile("settings.xml");

    file->open(QIODevice::Text|QIODevice::WriteOnly);
    QXmlStreamWriter xmlWriter(file);

    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("Settings");

    xmlWriter.writeTextElement("FontSize", fontSize);
    xmlWriter.writeTextElement("FontColor", fontColor);
    xmlWriter.writeTextElement("BackgroundColor", backgroundColor);

    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();
    file->close();
}
