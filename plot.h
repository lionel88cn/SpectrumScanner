#ifndef PLOT_H
#define PLOT_H

#include <qwt_plot.h>

class QwtPlotCurve;
class QwtPlotMarker;

class Plot: public QwtPlot
{
    Q_OBJECT

public:
    Plot( QWidget *parent );
public Q_SLOTS:
    void showData( const double *wavelength, const double *amplitude, int count );
private:
    QwtPlotCurve *d_curve1;
    QwtPlotMarker *d_marker1;
};

#endif // PLOT_H
