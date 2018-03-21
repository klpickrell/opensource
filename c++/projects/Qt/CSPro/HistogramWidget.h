#ifndef HISTOGRAM_WIDGET__H
#define HISTOGRAM_WIDGET__H

#include <QGLWidget>
#include <vector>

class HistogramWidget : public QGLWidget
{
    Q_OBJECT

public:
    HistogramWidget( bool report = false, QWidget *parent = 0);
    ~HistogramWidget();

    QSize minimumSizeHint() const;
    QSize sizeHint() const;

    void plotSequence( const std::vector<int>& sequence );
    std::vector<int> getCurrentSpatialSequence() { return currentSpatialSequence; }
    std::vector<int> getCurrentTemporalSequence() { return std::vector<int>(); }

public slots:
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);

signals:
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);
    void currentValue( const QString& );

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:

    GLuint makeCube();
    GLuint makeHistogram();
    GLuint makeObject();
    
    void renderBar( GLdouble height, GLdouble xpos, GLdouble width, GLdouble depth, const QColor& color );

    void quad(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2,
              GLdouble x3, GLdouble y3, GLdouble x4, GLdouble y4);
    void extrude(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2);
    void normalizeAngle(int *angle);

    bool report;

    GLuint object;
    int xRot;
    int yRot;
    int zRot;
    QPoint lastPos;

    QColor histogramBarsColor;
    QColor backgroundColor;

    float histogramWidth;
    float histogramHeight;

    std::vector<int> currentSpatialSequence;

    int currentViewportWidth;
};

#endif
