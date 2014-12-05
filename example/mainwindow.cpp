/* ============================================================
* TLDExtractor, a simple Qt interface to extract TLD part of a host
* Copyright (C) 2014  Razi Alavizadeh <s.r.alavizadeh@gmail.com>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
* ============================================================ */
#include "mainwindow.h"

#include <QApplication>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QUrl>

#include "tldextractor.h"

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent)
{
    // Adds QApplication::applicationDirPath() to data search paths,
    // TLDExtractor::defaultDataSearchPaths() is always added as last data search path
    TLDExtractor::instance()->setDataSearchPaths(QStringList() << QApplication::applicationDirPath());

    QFormLayout* formLayout = new QFormLayout;
    QWidget* w = new QWidget(this);

    QLabel* urlLabel = new QLabel(tr("URL:"), this);
    m_urlLineEdit = new QLineEdit(this);
    m_urlLineEdit->setPlaceholderText(tr("Enter URL here"));
    QObject::connect(m_urlLineEdit, SIGNAL(textChanged(QString)), this, SLOT(computeTLD()));

    QLabel* registrableDomainLabel = new QLabel(tr("Registrable domain:"), this);
    m_registrableDomainLineEdit = new QLineEdit(this);
    m_registrableDomainLineEdit->setReadOnly(true);

    QLabel* subDomainLabel = new QLabel(tr("sub domain:"), this);
    m_subDomainLineEdit = new QLineEdit(this);
    m_subDomainLineEdit->setReadOnly(true);

    QLabel* domainLabel = new QLabel(tr("domain:"), this);
    m_domainLineEdit = new QLineEdit(this);
    m_domainLineEdit->setReadOnly(true);

    QLabel* tldLabel = new QLabel(tr("TLD:"), this);
    m_tldLineEdit = new QLineEdit(this);
    m_tldLineEdit->setReadOnly(true);

    QLabel* testLabel = new QLabel(tr("Do test -> "), this);
    QPushButton* testButton = new QPushButton(tr("start test"));
    connect(testButton, SIGNAL(clicked()), this, SLOT(doTest()));

    formLayout->addRow(urlLabel, m_urlLineEdit);
    formLayout->addRow(registrableDomainLabel, m_registrableDomainLineEdit);
    formLayout->addRow(subDomainLabel, m_subDomainLineEdit);
    formLayout->addRow(domainLabel, m_domainLineEdit);
    formLayout->addRow(tldLabel, m_tldLineEdit);
    formLayout->addRow(testLabel, testButton);

    w->setLayout(formLayout);

    setCentralWidget(w);
    computeTLD();
    adjustSize();
}

QString fromPunycode(const QString &str)
{
    const QStringList sections = str.split(QLatin1Char('.'));
    QStringList decodedSections;
    foreach (const QString &section, sections) {
        QString tmpSection = section;

        if (section.startsWith(QLatin1String("xn--"))) {
            tmpSection = QUrl::fromAce(section.toUtf8() + QByteArray(".org"));
            tmpSection = tmpSection.left(tmpSection.size() - 4);
        }

        decodedSections << (tmpSection.isEmpty() ? section : tmpSection);
    }

    return decodedSections.join(QLatin1String("."));
}

void MainWindow::computeTLD()
{
    const QString host = fromPunycode(QUrl::fromUserInput(m_urlLineEdit->text()).host());

    const TLDExtractor::HostParts hostParts = TLDExtractor::instance()->splitParts(host);

    if (!hostParts.tld.isEmpty()) {
        m_tldLineEdit->setText(hostParts.tld);
        m_domainLineEdit->setText(hostParts.domain);
        m_subDomainLineEdit->setText(hostParts.subdomain);
        m_registrableDomainLineEdit->setText(hostParts.registrableDomain);
    }
    else {
        const QString unknownURL = tr("Unknown URL");

        m_tldLineEdit->setText(unknownURL);
        m_domainLineEdit->setText(unknownURL);
        m_subDomainLineEdit->setText(unknownURL);
        m_registrableDomainLineEdit->setText(unknownURL);
    }
}

void MainWindow::doTest()
{
    if (TLDExtractor::instance()->test()) {
        QMessageBox::information(this, tr("Successful"), tr("Test was passed successfully."));
    }
    else {
        QMessageBox::information(this, tr("Failed!"), tr("Test finished with some errors!"));
    }
}
