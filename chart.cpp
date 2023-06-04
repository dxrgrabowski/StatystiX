#include "chart.h"

Chart::Chart(std::vector<QPointF> points) {
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
    chart->addAxis(xAxis, Qt::AlignBottom);
    series->attachAxis(xAxis);

    QValueAxis* yAxis = new QValueAxis();
    yAxis->setTitleText("Y Axis");
    chart->addAxis(yAxis, Qt::AlignLeft);
    series->attachAxis(yAxis);

    // Set the point size and shape
    series->setMarkerSize(10);
    series->setMarkerShape(QScatterSeries::MarkerShapeCircle);

    // Create a chart view and set the chart
    QChartView* chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Set the central widget
    setCentralWidget(chartView);
}
