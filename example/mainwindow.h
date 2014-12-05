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
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QLineEdit;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);

private slots:
    void computeTLD();
    void doTest();

private:
    QLineEdit* m_urlLineEdit;
    QLineEdit* m_registrableDomainLineEdit;
    QLineEdit* m_subDomainLineEdit;
    QLineEdit* m_domainLineEdit;
    QLineEdit* m_tldLineEdit;
};

#endif // MAINWINDOW_H
