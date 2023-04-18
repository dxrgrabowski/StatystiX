#ifndef CHART_H
#define CHART_H

#include <QApplication>
#include <QMainWindow>
#include <QGraphicsWidget>
#include <QChart>

class Chart : public QMainWindow {
public:
    Chart(std::vector<QPointF> points) {
        // Create a chart and set the title
        QChart* chart = new QChart();
        chart->setTitle("Points Chart");

        // Create a scatter series and add it to the chart
        QScatterSeries* series = new QScatterSeries();
        for (QPointF point : points) {
            series->append(point);
        }
        chart->addSeries(series);

        // Set the axes
        QValueAxis* xAxis = new QValueAxis();
        xAxis->setTitleText("X Axis");
        chart->setAxisX(xAxis, series);

        QValueAxis* yAxis = new QValueAxis();
        yAxis->setTitleText("Y Axis");
        chart->setAxisY(yAxis, series);

        // Set the point size and shape
        series->setMarkerSize(10);
        series->setMarkerShape(QScatterSeries::MarkerShapeCircle);

        // Create a chart view and set the chart
        QChartView* chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);

        // Set the central widget
        setCentralWidget(chartView);
    }
};

#endif // CHART_H
