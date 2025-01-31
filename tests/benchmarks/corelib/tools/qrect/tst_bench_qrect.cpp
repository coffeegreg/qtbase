// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only
// This file contains benchmarks for QRect/QRectF functions.

#include <QDebug>
#include <qtest.h>

class tst_QRect : public QObject
{
    Q_OBJECT
private slots:
    // QRect functions:
    void contains_point_data();
    void contains_point();
    void contains_rect_data();
    void contains_rect();
    void intersects_data();
    void intersects();
    void intersected_data();
    void intersected();
    void united_data();
    void united();

    // QRectF functions:
    void contains_point_f_data();
    void contains_point_f();
    void contains_rect_f_data();
    void contains_rect_f();
    void intersects_f_data();
    void intersects_f();
    void intersected_f_data();
    void intersected_f();
    void united_f_data();
    void united_f();
};

struct RectRectCombination
{
    QString tag;
    qreal x1, y1, w1, h1, x2, y2, w2, h2;
    RectRectCombination(
        const QString &tag,
        const qreal x1, const qreal y1, const qreal w1, const qreal h1,
        const qreal x2, const qreal y2, const qreal w2, const qreal h2)
        : tag(tag), x1(x1), y1(y1), w1(w1), h1(h1), x2(x2), y2(y2), w2(w2), h2(h2) {}
};

static QList<RectRectCombination> createRectRectCombinations()
{
    QList<RectRectCombination> result;
    result << RectRectCombination("null", 0, 0, 0, 0, 0, 0, 0, 0);
    result << RectRectCombination("null1", 0, 0, 0, 0, 0, 0, 10, 10);
    result << RectRectCombination("null2", 0, 0, 10, 10, 0, 0, 0, 0);

    result << RectRectCombination("miss", 0, 0, 10, 10, 11, 11, 10, 10);
    result << RectRectCombination("intersect", 0, 0, 10, 10, 5, 5, 10, 10);
    result << RectRectCombination("contain1", 0, 0, 10, 10, 1, 1, 8, 8);
    result << RectRectCombination("contain2", 1, 1, 8, 8, 0, 0, 10, 10);

    result << RectRectCombination("miss_flip1", 9, 9, -10, -10, 11, 11, 10, 10);
    result << RectRectCombination("intersect_flip1", 9, 9, -10, -10, 5, 5, 10, 10);
    result << RectRectCombination("contain1_flip1", 9, 9, -10, -10, 1, 1, 8, 8);
    result << RectRectCombination("contain2_flip1", 8, 8, -8, -8, 0, 0, 10, 10);

    result << RectRectCombination("miss_flip2", 0, 0, 10, 10, 20, 20, -10, -10);
    result << RectRectCombination("intersect_flip2", 0, 0, 10, 10, 14, 14, -10, -10);
    result << RectRectCombination("contain1_flip2", 0, 0, 10, 10, 8, 8, -8, -8);
    result << RectRectCombination("contain2_flip2", 1, 1, 8, 8, 9, 9, -10, -10);

    return result;
}

static void addRectRectData(bool includeProperArg = false)
{
    QTest::addColumn<QRectF>("rf1");
    QTest::addColumn<QRectF>("rf2");
    if (includeProperArg)
        QTest::addColumn<bool>("proper");
    for (int i = 0; i < (includeProperArg ? 2 : 1); ++i) {
        const QList<RectRectCombination> combinations = createRectRectCombinations();
        for (const RectRectCombination &c : combinations) {
            QTestData &testData = QTest::newRow(c.tag.toLatin1().data());
            QRectF r1(c.x1, c.y1, c.w1, c.h1);
            QRectF r2(c.x2, c.y2, c.w2, c.h2);
            testData << r1 << r2;
            if (includeProperArg)
                testData << (i == 0);
        }
    }
}

struct RectPointCombination
{
    QString tag;
    qreal x, y, w, h, px, py;
    RectPointCombination(
        const QString &tag,
        const qreal x, const qreal y, const qreal w, const qreal h, const qreal px, const qreal py)
        : tag(tag), x(x), y(y), w(w), h(h), px(px), py(py) {}
};

static QList<RectPointCombination> createRectPointCombinations()
{
    QList<RectPointCombination> result;
    result << RectPointCombination("null", 0, 0, 0, 0, 0, 0);

    result << RectPointCombination("miss", 0, 0, 10, 10, -1, -1);
    result << RectPointCombination("contain", 0, 0, 10, 10, 0, 0);
    result << RectPointCombination("contain_proper", 0, 0, 10, 10, 1, 1);

    result << RectPointCombination("miss_flip", 9, 9, -10, -10, -1, -1);
    result << RectPointCombination("contain_flip", 9, 9, -10, -10, 0, 0);
    result << RectPointCombination("contain_flip_proper", 9, 9, -10, -10, 1, 1);

    return result;
}

static void addRectPointData(bool includeProperArg = false)
{
    QTest::addColumn<QRectF>("rf");
    QTest::addColumn<QPointF>("pf");
    if (includeProperArg)
        QTest::addColumn<bool>("proper");
    for (int i = 0; i < (includeProperArg ? 2 : 1); ++i) {
        const QList<RectPointCombination> combinations = createRectPointCombinations();
        for (const RectPointCombination &c : combinations) {
            QTestData &testData = QTest::newRow(c.tag.toLatin1().data());
            QRectF r(c.x, c.y, c.w, c.h);
            QPointF p(c.px, c.py);
            testData << r << p;
            if (includeProperArg)
                testData << (i == 0);
        }
    }
}

void tst_QRect::contains_point_data()
{
    addRectPointData(true);
}

void tst_QRect::contains_point()
{
    QFETCH(QRectF, rf);
    QFETCH(QPointF, pf);
    QFETCH(bool, proper);
    QRect r(rf.toRect());
    QPoint p(pf.toPoint());
    QBENCHMARK {
        r.contains(p, proper);
    }
}

void tst_QRect::contains_rect_data()
{
    addRectRectData(true);
}

void tst_QRect::contains_rect()
{
    QFETCH(QRectF, rf1);
    QFETCH(QRectF, rf2);
    QFETCH(bool, proper);
    QRect r1(rf1.toRect());
    QRect r2(rf2.toRect());
    QBENCHMARK {
        r1.contains(r2, proper);
    }
}

void tst_QRect::intersects_data()
{
    addRectRectData();
}

void tst_QRect::intersects()
{
    QFETCH(QRectF, rf1);
    QFETCH(QRectF, rf2);
    QRect r1(rf1.toRect());
    QRect r2(rf2.toRect());
    QBENCHMARK {
        r1.intersects(r2);
    }
}

void tst_QRect::intersected_data()
{
    addRectRectData();
}

void tst_QRect::intersected()
{
    QFETCH(QRectF, rf1);
    QFETCH(QRectF, rf2);
    QRect r1(rf1.toRect());
    QRect r2(rf2.toRect());
    QBENCHMARK {
        Q_UNUSED(r1.intersected(r2))
    }
}

void tst_QRect::united_data()
{
    addRectRectData();
}

void tst_QRect::united()
{
    QFETCH(QRectF, rf1);
    QFETCH(QRectF, rf2);
    QRect r1(rf1.toRect());
    QRect r2(rf2.toRect());
    QBENCHMARK {
        Q_UNUSED(r1.united(r2))
    }
}

void tst_QRect::contains_point_f_data()
{
    addRectPointData();
}

void tst_QRect::contains_point_f()
{
    QFETCH(QRectF, rf);
    QFETCH(QPointF, pf);
    QBENCHMARK {
        rf.contains(pf);
    }
}

void tst_QRect::contains_rect_f_data()
{
    addRectRectData();
}

void tst_QRect::contains_rect_f()
{
    QFETCH(QRectF, rf1);
    QFETCH(QRectF, rf2);
    QBENCHMARK {
        rf1.contains(rf2);
    }
}

void tst_QRect::intersects_f_data()
{
    addRectRectData();
}

void tst_QRect::intersects_f()
{
    QFETCH(QRectF, rf1);
    QFETCH(QRectF, rf2);
    QBENCHMARK {
        rf1.intersects(rf2);
    }
}

void tst_QRect::intersected_f_data()
{
    addRectRectData();
}

void tst_QRect::intersected_f()
{
    QFETCH(QRectF, rf1);
    QFETCH(QRectF, rf2);
    QBENCHMARK {
        Q_UNUSED(rf1.intersected(rf2))
    }
}

void tst_QRect::united_f_data()
{
    addRectRectData();
}

void tst_QRect::united_f()
{
    QFETCH(QRectF, rf1);
    QFETCH(QRectF, rf2);
    QBENCHMARK {
        Q_UNUSED(rf1.united(rf2))
    }
}

QTEST_MAIN(tst_QRect)

#include "tst_bench_qrect.moc"
