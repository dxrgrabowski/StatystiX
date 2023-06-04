#ifndef CHART_H
#define CHART_H

#include <QApplication>
#include <QMainWindow>
#include <QGraphicsWidget>
#include <QChart>
#include <QScatterSeries>
#include <QValueAxis>
#include <QChartView>

class Chart : public QMainWindow {
public:
    Chart(std::vector<QPointF> points);
};

#endif // CHART_H
