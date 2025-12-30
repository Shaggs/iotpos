#pragma once

#include <QDialog>
#include <QDialogButtonBox>
#include <QPointer>
#include <QPushButton>
#include <QVBoxLayout>

class KDialog : public QDialog
{
    Q_OBJECT

public:
    enum ButtonCode {
        None = 0x0,
        Ok = QDialogButtonBox::Ok,
        Cancel = QDialogButtonBox::Cancel,
        NoDefault = 0x0
    };
    Q_DECLARE_FLAGS(ButtonCodes, ButtonCode)

    explicit KDialog(QWidget *parent = nullptr);

    void setMainWidget(QWidget *widget);
    void setButtons(int buttons);
    void setDefaultButton(int button);
    void enableButton(int button, bool enable);
    void enableButtonOk(bool enable);
    QPushButton *button(int button) const;
    void setCaption(const QString &caption);

signals:
    void buttonClicked(int button);

protected slots:
    virtual void slotButtonClicked(int button);

private slots:
    void handleButtonClicked(QAbstractButton *button);

private:
    void ensureLayout();
    static QDialogButtonBox::StandardButtons toStandardButtons(int buttons);

    QPointer<QDialogButtonBox> m_buttonBox;
    QPointer<QWidget> m_mainWidget;
    QPointer<QVBoxLayout> m_layout;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(KDialog::ButtonCodes)
