#include "dialog/SnInputDialog.h"


SnInputDialog::SnInputDialog(const char* title)
{
	init(std::string(title),std::string(""));
}

SnInputDialog::SnInputDialog(const char* title,const char* value)
{
	init(std::string(title),std::string(value));
}


void SnInputDialog::setTitle(const char* title)
{
    m_ui->m_title->setText(QString(title));
}
void SnInputDialog::setTextField(const char* value)
{
    m_ui->m_editText->setText(QString(value));
}

std::string SnInputDialog::getTextField()
{
    return m_ui->m_editText->text().toUtf8().constData();
}

void SnInputDialog::init(const std::string& title,const std::string& value)
{
	m_ui=new Ui_input;
	m_ui->setupUi(this);
	setTitle(title.c_str());
    setTextField(value.c_str());
}





