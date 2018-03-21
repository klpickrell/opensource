#include <QtGui>
#include <QtOpenGL>

#include <math.h>
#include <algorithm>

#include "HistogramWidget.h"

using namespace std;

HistogramWidget::HistogramWidget(bool report, QWidget *parent)
    : QGLWidget(parent),
      report( report )
{
    object = 0;
    xRot = 0;
    yRot = 0;
    zRot = 0;

    histogramWidth = 100;
    histogramHeight = 100;

    histogramBarsColor = QColor::fromCmykF(0.40, 0.0, 1.0, 0.0);
    backgroundColor = QColor::fromCmykF(0.39, 0.39, 0.0, 0.0);
}

HistogramWidget::~HistogramWidget()
{
    makeCurrent();
    glDeleteLists(object, 1);
}

QSize HistogramWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize HistogramWidget::sizeHint() const
{
    return QSize(400, 400);
}

void HistogramWidget::setXRotation(int angle)
{
    normalizeAngle(&angle);
    if (angle != xRot) {
        xRot = angle;
        emit xRotationChanged(angle);
        updateGL();
    }
}

void HistogramWidget::setYRotation(int angle)
{
    normalizeAngle(&angle);
    if (angle != yRot) {
        yRot = angle;
        emit yRotationChanged(angle);
        updateGL();
    }
}

void HistogramWidget::setZRotation(int angle)
{
    normalizeAngle(&angle);
    if (angle != zRot) {
        zRot = angle;
        emit zRotationChanged(angle);
        updateGL();
    }
}

/*
void HistogramWidget::initializeGL()
{
    qglClearColor(backgroundColor.dark());
    object = makeObject();
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}

void HistogramWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslated(0.0, 0.0, -10.0);
    glRotated(xRot / 16.0, 1.0, 0.0, 0.0);
    glRotated(yRot / 16.0, 0.0, 1.0, 0.0);
    glRotated(zRot / 16.0, 0.0, 0.0, 1.0);
    glCallList(object);
}
*/

void HistogramWidget::plotSequence( const vector<int>& sequence )
{
    if( sequence.empty() ) {
        return;
    } else {
        int max_size = 512;
        if( (int)sequence.size() > max_size ) {
            currentSpatialSequence.assign( sequence.begin(), sequence.begin()+max_size );
        } else {
            currentSpatialSequence = sequence;
        }
        
        int themax = *max_element( currentSpatialSequence.begin(), currentSpatialSequence.end() );
        histogramHeight = themax * 1.10; // 120% of the maximum
        
        lastPos = QPoint( 0, 0 );
    }

    paintGL();
    updateGL();
}
    //    GLuint line_idx = glGenLists(1);
    //    glNewList( line_idx, GL_COMPILE );
/*
    float width = histogramWidth/sequence.size();
    int count = 0;

    glBegin( GL_QUADS );
    for( vector<int>::const_iterator it = sequence.begin();
         it != sequence.end();
         ++it ) {
        
        renderBar( *it, count*width, width, 1, histogramBarsColor );
        ++count;
    }
    glEnd();
*/

    //    glEndList();
      
    //    object = line_idx;
//}

void HistogramWidget::initializeGL()
{
    qglClearColor(backgroundColor.dark());

    //    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
    //    object = makeCube();
    //    object = makeHistogram();

    //    int cints[] = {1,2,3,4,5,6,7,8,9,10};
    //    vector<int> ints( &cints[0], &cints[sizeof( cints ) / sizeof( cints[0] )] );
    //    plotSequence( ints );
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);


    /*
    * Set GL_LIGHT_0's position to something like 45 degrees to the 'vertical'. 
      Coordinate (1,1,0) should work nicely in most cases.
    * Set GL_LIGHT_0's Ambient color to 0,0,0,1
    * Set GL_LIGHT_0's Diffuse color to 1,1,1,1
    * Set GL_LIGHT_0's Specular color to 1,1,1,1
    * Set the glLightModel's global ambient to 0.2,0.2,0.2,1 (this is the default).
    * Don't set any other glLight or glLightModel options - just let them default.
    * Enable GL_LIGHTING and GL_LIGHT_0.
    * Enable GL_COLOR_MATERIAL and set glColorMaterial to GL_AMBIENT_AND_DIFFUSE. This means 
      that glMaterial will control the polygon's specular and emission colours and the ambient and diffuse will both be set using glColor.
    * Set the glMaterial's Specular colour to 1,1,1,1
    * Set the glMaterial's Emission colour to 0,0,0,1
    * Set the glColor to whatever colour you want each polygon to basically appear to be. That sets the 
      Ambient and Diffuse to the same value which is what you generally want. 
    */

    // lighting
    bool enable_lighting = false;
    if( enable_lighting ) {
        GLfloat diffuseMaterial[4] = { 0.5, 0.5, 0.5, 1.0 };
        GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
        GLfloat light_position[] = { 0.5, 0.5, 0.0, 0.0 };

        glShadeModel (GL_SMOOTH);

        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMaterial);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialf(GL_FRONT, GL_SHININESS, 25.0);
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);

        glColorMaterial(GL_FRONT, GL_DIFFUSE);
        glEnable(GL_COLOR_MATERIAL);
    }
}

void HistogramWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    /*
    glRotated(xRot / 16.0, 1.0, 0.0, 0.0);
    glRotated(yRot / 16.0, 0.0, 1.0, 0.0);
    glRotated(zRot / 16.0, 0.0, 0.0, 1.0);
    */

    /*
    if( report ) {
        glColor3f( 1.0, 1.0, 0.0 );

        glBegin( GL_LINE_STRIP );
        float yval = -0.5;
        for( float i = -0.5; i < +0.5; i += (2.0f*1/50) ) {

            glVertex2f( i, yval );
            yval += ((rand()/(float)RAND_MAX))/10;
            glVertex2f( i, yval );

        }
        glEnd();

        glColor3f( 0.0, 1.0, 0.0 );

        glBegin( GL_LINE_STRIP );
        yval = -0.5;
        for( float i = -0.5; i < +0.5; i += (2.0f*1/50) ) {

            glVertex2f( i, yval );
            yval += ((rand()/(float)RAND_MAX))/10;
            glVertex2f( i, yval );

        }
        glEnd();
    } else {
        glColor3f( 1.0, 0.0, 0.0 );

        glBegin( GL_LINES );
        for( float i = -0.5; i < +0.5; i += (2.0f*1/50) ) {
      
            glVertex2f( i, -0.5 );
            glVertex2f( i, (rand()/(float)RAND_MAX) - 0.5 );

        }
        glEnd();
    }
    */

    float width = histogramWidth/currentSpatialSequence.size();
    float offset = -histogramWidth/2;
    int count = 0;

    QColor currentBarsColor = Qt::red;

    //    glBegin( GL_QUADS );
    //    renderBar( 5, offset, width, 1, currentBarsColor );
    //    renderBar( 4, offset + (1*width), width, 1, currentBarsColor );
    //    renderBar( 3, offset + (2*width), width, 1, currentBarsColor );

    for( vector<int>::const_iterator it = currentSpatialSequence.begin();
         it != currentSpatialSequence.end();
         ++it ) {
        
        if( count % 2 ) {
            renderBar( *it, offset + (count*width), width, 1, histogramBarsColor );
        } else {
            renderBar( *it, offset + (count*width), width, 1, currentBarsColor );
        }

        ++count;
    }


    if( !currentSpatialSequence.empty() ) {
        glPointSize( 8 );

        qglColor( Qt::white );

        glBegin( GL_POINTS );
        glEnable( GL_POINT_SMOOTH );

        //        qDebug( (QString( "lastPos.x=" ) + QString::number( lastPos.x() )).toStdString().c_str() );

        int index = static_cast<int>(lastPos.x() * (float)currentSpatialSequence.size()/currentViewportWidth);

        if( index >= (int)currentSpatialSequence.size() ) {
            index = currentSpatialSequence.size() - 1;
        }

        //        qDebug( (QString( "last pos index=" ) + QString::number( index )).toStdString().c_str() );

        glVertex3f( (lastPos.x()/(float)currentViewportWidth * histogramWidth) + (-histogramWidth/2), 
                    -histogramHeight/2+currentSpatialSequence[ index ], 2 );

        emit currentValue( (QString( "x=" ) + QString::number( index ) + 
                            QString( ", value=" ) + QString::number( currentSpatialSequence[ index ] )) );

        glEnd();
    }
}

void HistogramWidget::resizeGL(int width, int height)
{
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    currentViewportWidth = side;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho( -histogramWidth/2, histogramWidth/2, -histogramHeight/2, histogramHeight/2, -10, 10 );
    //    glFrustum( -histogramWidth/2, histogramWidth/2, -histogramHeight/2, histogramHeight/2, 0, 10 );
    glMatrixMode(GL_MODELVIEW);
}

void HistogramWidget::mousePressEvent(QMouseEvent *event)
{
    if( event->x() > 0 && event->x() < currentViewportWidth ) {
        lastPos = event->pos();
    }
}

void HistogramWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {

        if( event->x() > 0 && event->x() < currentViewportWidth ) {
            
            lastPos = event->pos();

            paintGL();
            updateGL();
        }
    }
}

GLuint HistogramWidget::makeCube()
{
    GLuint cube_idx = glGenLists(1);
    float half_width = 0.25;

    glNewList( cube_idx, GL_COMPILE );

      qglColor( histogramBarsColor );

      glBegin( GL_QUADS );

      // front face
          glVertex3f( -half_width, half_width, half_width );
          glVertex3f( -half_width, -half_width, half_width );
          glVertex3f( half_width, -half_width, half_width );
          glVertex3f( half_width, half_width, half_width );

      // back face
          glVertex3f( half_width, -half_width, -half_width );
          glVertex3f( -half_width, -half_width, -half_width );
          glVertex3f( -half_width, half_width, -half_width );
          glVertex3f( half_width, half_width, -half_width );

      // left face
          glVertex3f( -half_width, half_width, half_width );
          glVertex3f( -half_width, half_width, -half_width );
          glVertex3f( -half_width, -half_width, -half_width );
          glVertex3f( -half_width, -half_width, half_width );

      // right face
          glVertex3f( half_width, half_width, half_width );
          glVertex3f( half_width, -half_width, half_width );
          glVertex3f( half_width, -half_width, -half_width );
          glVertex3f( half_width, half_width, -half_width );

      // top face
          glVertex3f( -half_width, half_width, -half_width );
          glVertex3f( -half_width, half_width, half_width );
          glVertex3f( half_width, half_width, half_width );
          glVertex3f( half_width, half_width, -half_width );

      // bottom face
          glVertex3f( -half_width, -half_width, -half_width );
          glVertex3f( half_width, -half_width, -half_width );
          glVertex3f( half_width, -half_width, half_width );
          glVertex3f( -half_width, -half_width, half_width );


      glEnd();

    glEndList();
      
    return cube_idx;
}

GLuint HistogramWidget::makeHistogram()
{
    GLuint line_idx = glGenLists(1);
    float count = 100;

    glNewList( line_idx, GL_COMPILE );

    glColor3f( 1.0, 0.0, 0.0 );

      glBegin( GL_LINES );
      
      for( float i = -0.5; i < +0.5; i+=2*(1/count) ) {

          glVertex2f( i, -0.5 );
          glVertex2f( i, rand()/RAND_MAX - 0.5 );

      }

      glEnd();

    glEndList();
      
    return line_idx;
}

GLuint HistogramWidget::makeObject()
{
    GLuint list = glGenLists(1);
    glNewList(list, GL_COMPILE);

    glBegin(GL_QUADS);

    GLdouble x1 = +0.06;
    GLdouble y1 = -0.14;
    GLdouble x2 = +0.14;
    GLdouble y2 = -0.06;
    GLdouble x3 = +0.08;
    GLdouble y3 = +0.00;
    GLdouble x4 = +0.30;
    GLdouble y4 = +0.22;

    quad(x1, y1, x2, y2, y2, x2, y1, x1);
    quad(x3, y3, x4, y4, y4, x4, y3, x3);

    extrude(x1, y1, x2, y2);
    extrude(x2, y2, y2, x2);
    extrude(y2, x2, y1, x1);
    extrude(y1, x1, x1, y1);
    extrude(x3, y3, x4, y4);
    extrude(x4, y4, y4, x4);
    extrude(y4, x4, y3, x3);

    const double Pi = 3.14159265358979323846;
    const int NumSectors = 200;

    for (int i = 0; i < NumSectors; ++i) {
        double angle1 = (i * 2 * Pi) / NumSectors;
        GLdouble x5 = 0.30 * sin(angle1);
        GLdouble y5 = 0.30 * cos(angle1);
        GLdouble x6 = 0.20 * sin(angle1);
        GLdouble y6 = 0.20 * cos(angle1);

        double angle2 = ((i + 1) * 2 * Pi) / NumSectors;
        GLdouble x7 = 0.20 * sin(angle2);
        GLdouble y7 = 0.20 * cos(angle2);
        GLdouble x8 = 0.30 * sin(angle2);
        GLdouble y8 = 0.30 * cos(angle2);

        quad(x5, y5, x6, y6, x7, y7, x8, y8);

        extrude(x6, y6, x7, y7);
        extrude(x8, y8, x5, y5);
    }

    glEnd();

    glEndList();
    return list;
}

void HistogramWidget::quad(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2,
                    GLdouble x3, GLdouble y3, GLdouble x4, GLdouble y4)
{
    qglColor(histogramBarsColor);

    glVertex3d(x1, y1, -0.05);
    glVertex3d(x2, y2, -0.05);
    glVertex3d(x3, y3, -0.05);
    glVertex3d(x4, y4, -0.05);

    glVertex3d(x4, y4, +0.05);
    glVertex3d(x3, y3, +0.05);
    glVertex3d(x2, y2, +0.05);
    glVertex3d(x1, y1, +0.05);
}

void HistogramWidget::extrude(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2)
{
    qglColor(histogramBarsColor.dark(250 + int(100 * x1)));

    glVertex3d(x1, y1, +0.05);
    glVertex3d(x2, y2, +0.05);
    glVertex3d(x2, y2, -0.05);
    glVertex3d(x1, y1, -0.05);
}

void HistogramWidget::renderBar( GLdouble height, 
                                 GLdouble xpos, 
                                 GLdouble width, 
                                 GLdouble depth, 
                                 const QColor& color )
{

    glBegin( GL_QUADS );

    // face values
    float x1, y1, x2, y2;
    float near = 1;
    float far = 1+depth;

    x1 = xpos;
    x2 = xpos + width;

    y1 = -histogramHeight/2;
    y2 = (height>histogramHeight ? y1+histogramHeight : y1+height);

    int darkvalue = 0;
    int darkscale = 100;
    qglColor( color.darker( darkvalue * darkscale ) );

    // front face
    glEdgeFlag( GL_TRUE );
    glVertex3f( x1, y1, near );
    glVertex3f( x2, y1, near );
    glVertex3f( x2, y2, near );
    glVertex3f( x1, y2, near );


    darkvalue = 2;
    qglColor( color.darker( darkvalue * darkscale ) );

    // left face
    glEdgeFlag( GL_TRUE );
    glVertex3f( x1, y1, far );
    glVertex3f( x1, y1, near );
    glVertex3f( x1, y2, near );
    glVertex3f( x1, y2, far );

    // right face
    glEdgeFlag( GL_TRUE );
    glVertex3f( x2, y2, far );
    glVertex3f( x2, y2, near );
    glVertex3f( x2, y1, near );
    glVertex3f( x2, y1, far );

    darkvalue = 3;
    qglColor( color.darker( darkvalue * darkscale ) );

    // top face
    glEdgeFlag( GL_TRUE );
    glVertex3f( x1, y2, far );
    glVertex3f( x1, y2, near );
    glVertex3f( x2, y2, near );
    glVertex3f( x2, y2, far );

    // bottom face
    glEdgeFlag( GL_TRUE );
    glVertex3f( x1, y1, near );
    glVertex3f( x1, y1, far );
    glVertex3f( x2, y1, far );
    glVertex3f( x2, y1, near );

    darkvalue = 4;
    qglColor( color.darker( darkvalue * darkscale ) );

    // back face
    glEdgeFlag( GL_TRUE );
    glVertex3f( x1, y2, far );
    glVertex3f( x2, y2, far );    
    glVertex3f( x2, y1, far );
    glVertex3f( x1, y1, far );

    glEnd();
}


void HistogramWidget::normalizeAngle(int *angle)
{
    while (*angle < 0)
        *angle += 360 * 16;
    while (*angle > 360 * 16)
        *angle -= 360 * 16;
}
