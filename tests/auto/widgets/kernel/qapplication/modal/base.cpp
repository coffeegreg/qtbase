// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "base.h"
#include "qapplication.h"

base::base(QWidget *parent) :
    QWidget(parent)
{
    m_timer = new QTimer(this);
    m_timer->setSingleShot(false);
    connect(m_timer, &QTimer::timeout, this, &base::periodicTimer);
    m_timer->start(5000);
}

void base::periodicTimer()
{
    if(m_modalStarted)
        qApp->quit();
    m_modalDialog = new QDialog(this);
    m_modalDialog->setWindowTitle(QLatin1String("modal"));
    m_modalDialog->setModal(true);
    m_modalDialog->show();
    m_modalStarted = true;
}
