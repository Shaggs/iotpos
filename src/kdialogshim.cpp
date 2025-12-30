#include "kdialogshim.h"

#include <QAbstractButton>

KDialog::KDialog(QWidget *parent)
    : QDialog(parent)
{
    ensureLayout();
    connect(this, SIGNAL(buttonClicked(int)), this, SLOT(slotButtonClicked(int)));
}

void KDialog::setCaption(const QString &caption)
{
    setWindowTitle(caption);
}

void KDialog::setMainWidget(QWidget *widget)
{
    ensureLayout();
    if (m_mainWidget) {
        m_layout->removeWidget(m_mainWidget);
        m_mainWidget->setParent(nullptr);
    }
    m_mainWidget = widget;
    if (m_mainWidget) {
        m_layout->insertWidget(0, m_mainWidget);
    }
}

void KDialog::setButtons(int buttons)
{
    ensureLayout();
    if (!m_buttonBox) {
        m_buttonBox = new QDialogButtonBox(this);
        m_layout->addWidget(m_buttonBox);
        connect(m_buttonBox, SIGNAL(clicked(QAbstractButton*)), this, SLOT(handleButtonClicked(QAbstractButton*)));
    }

    m_buttonBox->setStandardButtons(toStandardButtons(buttons));
}

void KDialog::setDefaultButton(int button)
{
    if (!m_buttonBox) {
        return;
    }

    const auto buttons = m_buttonBox->buttons();
    for (QAbstractButton *btn : buttons) {
        if (auto *pushButton = qobject_cast<QPushButton *>(btn)) {
            pushButton->setDefault(false);
        }
    }

    if (button == NoDefault || button == None) {
        return;
    }

    if (auto *pushButton = button(button)) {
        pushButton->setDefault(true);
    }
}

void KDialog::enableButton(int button, bool enable)
{
    if (auto *pushButton = button(button)) {
        pushButton->setEnabled(enable);
    }
}

void KDialog::enableButtonOk(bool enable)
{
    enableButton(Ok, enable);
}

QPushButton *KDialog::button(int button) const
{
    if (!m_buttonBox) {
        return nullptr;
    }
    auto standardButton = static_cast<QDialogButtonBox::StandardButton>(button);
    return m_buttonBox->button(standardButton);
}

void KDialog::slotButtonClicked(int)
{
}

void KDialog::handleButtonClicked(QAbstractButton *clickedButton)
{
    if (!m_buttonBox) {
        return;
    }

    const auto standardButton = m_buttonBox->standardButton(clickedButton);
    emit buttonClicked(static_cast<int>(standardButton));
}

void KDialog::ensureLayout()
{
    if (m_layout) {
        return;
    }

    m_layout = new QVBoxLayout(this);
    m_layout->setContentsMargins(0, 0, 0, 0);
}

QDialogButtonBox::StandardButtons KDialog::toStandardButtons(int buttons)
{
    if (buttons == None || buttons == NoDefault) {
        return QDialogButtonBox::NoButton;
    }
    return static_cast<QDialogButtonBox::StandardButtons>(buttons);
}
