#include "opersPopupDialog.h"

#include <QBoxLayout>
#include <QFile>
#include <QFormLayout>
#include <QIntValidator>

OpersPopupDialog::OpersPopupDialog(DBWorker &db, const QHash<QString, QString> &data, QWidget *parent)
    : QDialog(parent)
    , m_name(new QLineEdit(this))
    , m_mcc(new QLineEdit(this))
    , m_mnc(new QLineEdit(this))
    , m_save(new QPushButton("Save", this))
    , m_cancel(new QPushButton("Cancel", this))
    , m_iconCountry(new QLabel(this))
    , m_iconOper(new QLabel(this))
    , m_db(db)
{
    setWindowTitle("Operator Editor");

    QString mcc = data["mcc"];

    if(!mcc.isEmpty())
    {
        QString name = data["name"];
        QString mnc = data["mnc"];

        m_name->setText(name);
        m_mcc->setText(mcc);
        m_mnc->setText(mnc);
        m_mcc->setEnabled(false);
        m_mnc->setEnabled(false);
    }
    else
    {
        m_name->setText("");
        m_mcc->setText("0");
        m_mnc->setText("0");
    }

    m_mcc->setValidator(new QIntValidator);
    m_mnc->setValidator(new QIntValidator);

    QLabel *topTextLabel = new QLabel("Operator Editor", this);
    topTextLabel->setContentsMargins(0, 0, (width() * .06), 0);

    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(m_iconOper);
    topLayout->addWidget(topTextLabel);

    QHBoxLayout *mccLayout = new QHBoxLayout;
    mccLayout->addWidget(m_mcc);
    mccLayout->addWidget(m_iconCountry);

    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow(topLayout);
    formLayout->addRow("Name", m_name);
    formLayout->addRow("MCC", mccLayout);
    formLayout->addRow("MNC", m_mnc);

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addWidget(m_save);
    buttonsLayout->addWidget(m_cancel);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(buttonsLayout);

    connect(m_save, &QPushButton::clicked, this, &OpersPopupDialog::accept);
    connect(m_cancel, &QPushButton::clicked, this, &OpersPopupDialog::reject);
    connect(m_name, &QLineEdit::textChanged, this, &OpersPopupDialog::onCheckForm);
    connect(m_mcc, &QLineEdit::textChanged, this, &OpersPopupDialog::onCheckForm);
    connect(m_mnc, &QLineEdit::textChanged, this, &OpersPopupDialog::onCheckForm);

    setLayout(mainLayout);
    emit onCheckForm();
}

void OpersPopupDialog::onCheckForm()
{
    CountryOperators country = m_db.countryByMcc(m_mcc->text());
    CountryOperators oper;
    oper.name       = m_name->text();
    oper.mcc        = m_mcc->text();
    oper.codeMnc    = m_mnc->text();

    const int iconSize = 16;
    QIcon question(QString(":/Icons/question.png"));
    QString countryPath(QString(":/Icons/%1.png").arg(country.codeMnc));
    QString operatorPath(QString(":/Icons/%1_%2.png").arg(m_mcc->text()).arg(m_mnc->text()));

    if(QFile::exists(countryPath))
    {
        QIcon icon(countryPath);
        m_iconCountry->setPixmap(icon.pixmap(QSize(iconSize, iconSize)));
    }
    else
        m_iconCountry->setPixmap(question.pixmap(QSize(iconSize, iconSize)));

    if(QFile::exists(operatorPath))
    {
        QIcon icon(operatorPath);
        m_iconOper->setPixmap(icon.pixmap(QSize(iconSize, iconSize)));
    }
    else
        m_iconOper->setPixmap(question.pixmap(QSize(iconSize, iconSize)));

    if(!country.mcc.isEmpty())
        m_mnc->setMaxLength(country.length);

    m_save->setEnabled(m_name->text().isEmpty() || country.mcc.isEmpty() || m_mnc->text().isEmpty()
                       || (m_mcc->isEnabled() && m_db.isExistOperator(oper)) ? false : true);
}
