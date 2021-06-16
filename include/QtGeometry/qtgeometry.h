/****************************************************************************
 *                                                                          *
 * Copyright (C) 2001~2016 Neutrino International Inc.                      *
 *                                                                          *
 * Author : Brian Lin <lin.foxman@gmail.com>, Skype: wolfram_lin            *
 *                                                                          *
 ****************************************************************************/

#ifndef QT_GEOMETRY_H
#define QT_GEOMETRY_H

#include <QtCore>
#include <QtGui>
#include <QtNetwork>
#include <QtSql>
#include <QtScript>
#include <QtPositioning>
#include <QtOpenGL>
#include <QtCUDA>
#include <QtOpenCV>
#include <Essentials>
#include <QtGMP>
#include <QtGSL>
#include <QtAlgebra>
#include <QtDiscrete>
#include <QtFFT>
#include <Mathematics>
#include <QtFuzzy>
#include <QtFLP>

QT_BEGIN_NAMESPACE

#ifndef QT_STATIC
#    if defined(QT_BUILD_QTGEOMETRY_LIB)
#      define Q_GEOMETRY_EXPORT Q_DECL_EXPORT
#    else
#      define Q_GEOMETRY_EXPORT Q_DECL_IMPORT
#    endif
#else
#    define Q_GEOMETRY_EXPORT
#endif

namespace N
{

class Q_GEOMETRY_EXPORT FeaturePoint  ;
class Q_GEOMETRY_EXPORT FeaturePoints ;
class Q_GEOMETRY_EXPORT ControlPoint  ;
class Q_GEOMETRY_EXPORT Contour       ;
class Q_GEOMETRY_EXPORT Plane         ;
class Q_GEOMETRY_EXPORT Circle        ;
class Q_GEOMETRY_EXPORT Parabola      ;
class Q_GEOMETRY_EXPORT Sphere        ;
class Q_GEOMETRY_EXPORT Cylinder      ;
class Q_GEOMETRY_EXPORT Polyhedron    ;
class Q_GEOMETRY_EXPORT GlyphManager  ;

typedef QMap  < CUID    , ControlPoint > ControlPoints ;
typedef QList < Contour                > Contours      ;
typedef QMap  < CUID    , Circle       > Circles       ;
typedef QMap  < int     , QColor       > QColors       ;

namespace Graphics
{

Q_GEOMETRY_EXPORT int toVector    (Colors     & colors,QVector<QRgb> & rgb   ) ;
Q_GEOMETRY_EXPORT int toByteArray (Colors     & colors,QByteArray    & blob  ) ;
Q_GEOMETRY_EXPORT int toColors    (QImage     & image ,Colors        & colors) ;
Q_GEOMETRY_EXPORT int addColors   (QByteArray & blob  ,Colors        & colors) ;
Q_GEOMETRY_EXPORT int Uniqueness  (Colors     & colors) ;

}

namespace OpenGL
{

Q_GEOMETRY_EXPORT void Vertices(CUIDs Index,ControlPoints Points) ;

}

/*****************************************************************************
 *                                                                           *
 *                                Features                                   *
 *                                                                           *
 *****************************************************************************/

class Q_GEOMETRY_EXPORT FeaturePoint
{
  public:

    int   id       ;
    int   octave   ;
    float x        ;
    float y        ;
    float size     ;
    float angle    ;
    float response ;
    int   extra    ;

    explicit             FeaturePoint (float x,float y) ;
    explicit             FeaturePoint (QByteArray Blob) ;
    explicit             FeaturePoint (cv::KeyPoint & keypoint) ;
                         FeaturePoint (void) ;
    virtual             ~FeaturePoint (void) ;

    virtual int          packetSize   (void) const ;
    virtual QByteArray   toByteArray  (void) ;
    virtual bool         toByteArray  (QByteArray & Blob) ;
    virtual bool         operator =   (QByteArray & Blob) ;
    virtual bool         operator =   (cv::KeyPoint & keypoint) ;
    virtual bool         toKeyPoint   (cv::KeyPoint & keypoint) ;
    virtual cv::KeyPoint toKeyPoint   (void) ;
    virtual double       distance     (void) ;
    FeaturePoint &       operator /=  (QSizeF & size) ;
    FeaturePoint &       operator /=  (QSize  & size) ;

  protected:

  private:

};

class Q_GEOMETRY_EXPORT FeaturePoints : public QList<FeaturePoint *>
{
  public:

    explicit           FeaturePoints (QByteArray & Blob) ;
                       FeaturePoints (void) ;
    virtual           ~FeaturePoints (void) ;

    virtual int        fromByteArray (QByteArray & Blob) ;
    virtual QByteArray toByteArray   (void) ;
    virtual bool       toByteArray   (QByteArray & Blob) ;
    virtual bool       operator =    (QByteArray & Blob) ;
    virtual bool       operator <<   (QByteArray & Blob) ;
    virtual bool       operator =    (std::vector<cv::KeyPoint> & keypoints) ;
    virtual bool       operator <<   (std::vector<cv::KeyPoint> & keypoints) ;
    virtual bool       toKeyPoints   (std::vector<cv::KeyPoint> & keypoints) ;
    virtual std::vector<cv::KeyPoint> toKeyPoints (void) ;
    virtual double     distance      (void) ;
    virtual double     x             (void) ;
    virtual double     y             (void) ;
    virtual QRectF     Range         (void) ;
    FeaturePoints &    operator /=   (QSizeF & size) ;
    FeaturePoints &    operator /=   (QSize  & size) ;

  protected:

  private:

};

/*****************************************************************************
 *                                                                           *
 *                           Geometry Operations                             *
 *                                                                           *
 *****************************************************************************/

#pragma pack(push,1)

typedef struct {
  double x     ;
  double y     ;
  double z     ;
  double t     ;
} PackedPoint  ;

typedef struct       {
  SUID   uuid        ;
  int    Type        ;
  int    DOF         ; // Degree of Freedom Type
  int    Unit        ;
  int    Flag        ;
  double x           ;
  double y           ;
  double z           ;
  double t           ;
  double r           ;
  double f           ;
} PackedControlPoint ;

#pragma pack(pop)

Q_GEOMETRY_EXPORT bool Rotation    (Matrix     & matrix,ControlPoint & R) ;
Q_GEOMETRY_EXPORT bool Assign      (Matrix     & matrix,const QTransform & transform) ;
Q_GEOMETRY_EXPORT bool toTransform (QTransform & transform,Matrix & matrix) ;
Q_GEOMETRY_EXPORT bool Transform   (Matrix     & matrix,ControlPoint & Source,ControlPoint & Target) ;

class Q_GEOMETRY_EXPORT ControlPoint
{
  public:

    enum DofActions    {
      DofNone      = 0 ,
      DofTranslate = 1 ,
      DofRotate    = 2 ,
      DofScale     = 3
    };

    SUID   uuid ;
    int    Type ;
    int    DOF  ; // Degree of Freedom Type
    int    Unit ;
    int    Flag ;
    double x    ;
    double y    ;
    double z    ;
    double t    ;
    double r    ;
    double f    ;

    explicit ControlPoint          (void) ;
    explicit ControlPoint          (double X,double Y,double Z = 0) ;
    explicit ControlPoint          (double X,double Y,double Z,double R) ;
    explicit ControlPoint          (QPoint    P) ;
    explicit ControlPoint          (QPointF   P) ;
    explicit ControlPoint          (QVector3D V) ;
    explicit ControlPoint          (QColor    C) ;
             ControlPoint          (const ControlPoint       & point) ;
             ControlPoint          (const PackedPoint        & packp) ;
             ControlPoint          (const PackedControlPoint & packp) ;
    virtual ~ControlPoint          (void) ;

    int            Control         (void) ;

    QPointF        Point           (void) ;
    QPointF        Point           (int DPI) ;
    QVector3D      Vertex          (void) ;
    QColor         Color           (void) ;

    bool           toPacked        (PackedPoint        & packp) ;
    bool           toPacked        (PackedControlPoint & packp) ;

    bool           Within          (QPointF & p,double R2) ; // R2 = radius * radius

    double         length          (void) const ;
    double         lengthSquared   (void) const ;
    void           normalize       (void) ;
    ControlPoint   normalized      (void) const ;

    double         distanceToLine  (ControlPoint & point ,ControlPoint & direction) const ;
    double         distanceToPlane (ControlPoint & plane ,ControlPoint & normalx) const ;
    double         distanceToPlane (ControlPoint & plane1,ControlPoint & plane2,ControlPoint & plane3) const ;

    ControlPoint & operator  =     (const ControlPoint & p      ) ;
    ControlPoint & operator  =     (const QPointF      & p      ) ;
    ControlPoint & operator  =     (const QVector3D    & p      ) ;
    ControlPoint & operator  =     (const QColor       & c      ) ;

    ControlPoint & operator *=     (double               factor ) ;
    ControlPoint & operator *=     (const ControlPoint & vector ) ;
    ControlPoint & operator +=     (const ControlPoint & vector ) ;
    ControlPoint & operator -=     (const ControlPoint & vector ) ;
    ControlPoint & operator /=     (double               divisor) ;

    void Light                     (GLenum light,GLenum pname) ; // OpenGL glLightfv
    void Material                  (GLenum face ,GLenum pname) ; // OpenGL glMaterialfv
    void Vertex3f                  (void) ; // OpenGL glVertex3f
    void Vertex3d                  (void) ; // OpenGL glVertex3d
    void Normal3f                  (void) ; // OpenGL glNormal3f
    void Normal3d                  (void) ; // OpenGL glNormal3d
    void Translatef                (void) ; // OpenGL glTranslatef
    void Translate                 (void) ; // OpenGL glTranslated
    void Rotatef                   (void) ; // OpenGL glRotatef
    void Rotate                    (void) ; // OpenGL glRotated
    void Scalef                    (void) ; // OpenGL glScalef
    void Scale                     (void) ; // OpenGL glScaled
    void Color3f                   (void) ; // OpenGL glColor3f
    void Color4f                   (void) ; // OpenGL glColor4f
    void Color3d                   (void) ; // OpenGL glColor3d
    void Color4d                   (void) ; // OpenGL glColor4d

  protected:

  private:

};

class Q_GEOMETRY_EXPORT Contour
{
  public:

    SUID          uuid      ;
    QString       name      ;
    int           type      ;
    bool          closed    ;
    bool          substract ;
    CUIDs         index     ;
    ControlPoint  thickness ;
    ControlPoints points    ;

    explicit   Contour    (void) ;
               Contour    (const Contour & contour) ;
    virtual   ~Contour    (void) ;

    int        count      (void) ;

    void       begin      (void) ;
    int        add        (int Id,ControlPoint & point) ;
    int        remove     (int Id) ;
    void       end        (void);
    void       close      (int Type = Graphics::Quadratic) ;

    int        find       (QPointF & point,double R) ;

    QByteArray Data       (void);
    void       setData    (QByteArray & contour) ;

    QRectF boundingRect   (void) ;

    Contour & operator  = (const Contour & contour  ) ;
    Contour & operator += (QPointF         center   ) ;
    Contour & operator += (FeaturePoints & features ) ;
    Contour & operator -= (QPointF         center   ) ;
    Contour & operator *= (double          factor   ) ;
    Contour & operator *= (QSizeF          size     ) ;
    Contour & operator /= (double          divisor  ) ;

  protected:

  private:

};

class Q_GEOMETRY_EXPORT Plane
{
  public:

    ControlPoint O ; // Base point
    ControlPoint X ; // X Axis
    ControlPoint Y ; // Y Axis
    ControlPoint T ; // Thickness
    ControlPoint N ; // Normal
    int          W ; // Width segments
    int          H ; // Height segments
    bool         A ; // Activation

    explicit Plane     (void) ;
             Plane     (const Plane & plane) ;
    virtual ~Plane     (void) ;

    Plane & operator = (const Plane & plane) ;

    bool    Upon       (ControlPoint & At                 ,
                        ControlPoint & Base               ,
                        ControlPoint & Vector             ,
                        double         detail = 0.000001) ;
    QPointF Axis       (ControlPoint & At) ;
    // For acceleration, this function will not divided X.length and Y.length

  protected:

  private:

};

class Q_GEOMETRY_EXPORT Circle
{
  public:

    ControlPoint O ; // Center
    ControlPoint X ; // X Vector
    ControlPoint Y ; // Y Vector
    int          N ; // N sectors

    explicit Circle     (void) ;
             Circle     (const Circle & circle) ;
    virtual ~Circle     (void) ;

    Circle & operator = (const Circle & circle) ;

    bool Angle          (double angle,ControlPoint & P) ;

  protected:

  private:

};

class Q_GEOMETRY_EXPORT Parabola
{ // y = a * x ^ 2 + b * x + c
  public:

    int    n   ;
    double a   ;
    double b   ;
    double c   ;
    double PA0 ;
    double PA1 ;
    double PA2 ;
    double T1  ;
    double T2  ;
    double T3  ;
    double T4  ;
    double pa0 ;
    double pa1 ;
    double pa2 ;
    double t1  ;
    double t2  ;
    double t3  ;
    double t4  ;
    double V1  ;
    double V2  ;
    double V3  ;
    double W1  ;
    double W2  ;
    double p   ;
    double A   ; // [ A * x ^ 2 + B * x * y + C * y ^ 2 + D * x + E * y + F ]
    double B   ;
    double C   ;
    double D   ; // if not used as
    double E   ; // [ A * x ^ 2 + B * x * y + C * y ^ 2 + D * x + E * y + F ]
    double F   ; // A-F will be used as the best fit line paraments
    double M   ;
    double P   ;
    double R   ;
    double mp  ;

    explicit Parabola        (void);
             Parabola        (const Parabola & parabola) ;
    virtual ~Parabola        (void);

    Parabola & operator =    (const Parabola & parabola) ;

    void       clear         (void) ;
    void       setParameters (double a,double b,double c) ;
    void       Append        (double key,double value) ;
    void       Add           (double key,double value) ;
    void       Epitomize     (void) ;
    double     Equation      (double key) ; // ( a * k * k ) + ( b * k ) + c
    double     Slope         (double key) ; // ( 2 * a * k ) + b
    double     Extreme       (void) ; // -b / 2a
    int        Dissect       (double v,double m = 0.00000000000001f) ; // -1 : ( v < -m ) , 1 : ( v > m ) , 0 : [ -m , m ]
    bool       Degeneration  (double minimum = 0.00000000000001f) ; // |a| < minimum
    bool       Transit       (double minimum = 0.00000000000001f) ; // |b| < minimum
    // Focus ( u , v )
    // Directrix : ax + by + c
    // ( [ ax + by + c ] ^ 2 / ( a ^ 2 + b ^2 ) ) = ( x - u ) ^ 2 + ( y - v ) ^ 2
    void       Determinant   (Matrix & matrix) ;
    QByteArray toByteArray   (void) ;
    void       toByteArray   (QByteArray & data) ;
    void       setByteArray  (QByteArray & data) ;
    void       operator =    (QByteArray & data) ;

};

class Q_GEOMETRY_EXPORT Sphere
{
  public:

    ControlPoint O ; // Center
    ControlPoint X ; // X Vector
    ControlPoint Y ; // Y Vector
    ControlPoint R ; // Radius Vector
    IMAPs        N ; // Sectors

    explicit Sphere     (void) ;
             Sphere     (const Sphere & sphere) ;
    virtual ~Sphere     (void) ;

    Sphere & operator = (const Sphere & sphere) ;

  protected:

  private:

};

class Q_GEOMETRY_EXPORT Cylinder
{
  public:

    IMAPs         sectors ;
    ControlPoints pathes  ;
    Circles       circles ;

    explicit Cylinder     (void) ;
             Cylinder     (const Cylinder & cylinder) ;
    virtual ~Cylinder     (void) ;

    Cylinder & operator = (const Cylinder & cylinder) ;

    void Cone             (ControlPoint & P1   ,
                           ControlPoint & P2   ,
                           ControlPoint & X1   ,
                           ControlPoint & Y1   ,
                           ControlPoint & X2   ,
                           ControlPoint & Y2 ) ;

  protected:

  private:

};

class Q_GEOMETRY_EXPORT Polyhedron
{
  public:

    enum                  {
      Tetrahedron  =  1   ,
      Hexahedron   =  2   ,
      Octahedron   =  3   ,
      Dodecahedron =  4   ,
      Icosahedron  =  5   ,
      Zonohedron   =  6 } ;

    int           type      ;
    ControlPoints points    ;
    VarArgs       arguments ;

    explicit Polyhedron     (void) ;
             Polyhedron     (const Polyhedron & polyhedron) ;
    virtual ~Polyhedron     (void) ;

    Polyhedron & operator = (const Polyhedron & polyhedron) ;

  protected:

  private:

};

class Q_GEOMETRY_EXPORT GlyphManager
{
  public:

    explicit         GlyphManager (void) ;
    virtual         ~GlyphManager (void) ;

    virtual int      count        (void) ;
    virtual bool     contains     (int unicode) ;
    virtual int      codings      (CUIDs & unicodes) ;

    virtual void     list         (QDir & directory,QStringList filelist) ;
    virtual void     list         (QStringList filelist) ;
    virtual void     add          (int index,QString filename) ;
    virtual void     add          (int index,const char * filename) ;
    virtual void     setPixels    (int width,int height) ;

    virtual bool     draw         (int unicode,QImage & image,QColor c) ;
    virtual int      subglyphs    (int unicode) ;
    virtual int      points       (int unicode,QMap<int,QPoint> & points  ) ;
    virtual int      points       (int unicode,ControlPoint shift,ControlPoints & points) ;
    virtual int      types        (int unicode,QMap<int,int   > & types   ) ;
    virtual int      contours     (int unicode,QMap<int,CUIDs > & contours) ;

    virtual int      families     (void) ;
    virtual QStrings Fonts        (void) ;
    virtual QString  path         (QString family) ;

    virtual int      isLoaded     (int unicode) ;
    virtual QRectF   BoundingBox  (int unicode) ;

    virtual bool     isCubic      (int tag) ;
    virtual bool     isConic      (int tag) ;
    virtual bool     isOn         (int tag) ;

    virtual int      Width        (void) ;
    virtual int      Height       (void) ;

  protected:

    QStringList TTFs      ;
    QStringList Families  ;
    KMAPs       Pathes    ;
    EMAPs       Files     ;
    IMAPs       Glyphs    ;
    IMAPs       AtFace    ;
    QSize       Dimension ;
    void      * FtPacket  ;

    virtual void     BuildPathes  (void) ;

  private:

};

}

Q_GEOMETRY_EXPORT N::ControlPoint       interpolate  (N::ControlPoint & v1     , N::ControlPoint & v2 , double t ) ;
Q_GEOMETRY_EXPORT N::ControlPoint       crossProduct (N::ControlPoint & v1     , N::ControlPoint & v2            ) ;
Q_GEOMETRY_EXPORT double                dotProduct   (N::ControlPoint & v1     , N::ControlPoint & v2            ) ;
Q_GEOMETRY_EXPORT N::ControlPoint       Normal       (N::ControlPoint & v1     , N::ControlPoint & v2            ) ;
Q_GEOMETRY_EXPORT N::ControlPoint       Normal       (N::ControlPoint & v1     , N::ControlPoint & v2 , N::ControlPoint & v3 ) ;
Q_GEOMETRY_EXPORT bool                  FuzzyCompare (N::ControlPoint & v1     , N::ControlPoint & v2            ) ;
Q_GEOMETRY_EXPORT bool                  Between      (N::ControlPoint & p      , N::ControlPoint & m1 , N::ControlPoint & m2 ) ;
Q_GEOMETRY_EXPORT bool                  IntersectRectangle       (
                                          N::ControlPoint & P    ,
                                          N::ControlPoint & Z0   ,
                                          N::ControlPoint & Z1   ,
                                          N::ControlPoint & Z3   ,
                                          N::ControlPoint & P1   ,
                                          N::ControlPoint & P2 ) ;

Q_GEOMETRY_EXPORT bool                  operator !=  (N::ControlPoint & v1     , N::ControlPoint & v2            ) ;
Q_GEOMETRY_EXPORT const N::ControlPoint operator *   (double factor            , N::ControlPoint & vector        ) ;
Q_GEOMETRY_EXPORT const N::ControlPoint operator *   (N::ControlPoint & vector , double factor                   ) ;
Q_GEOMETRY_EXPORT const N::ControlPoint operator *   (N::ControlPoint & v1     , N::ControlPoint & v2            ) ;
Q_GEOMETRY_EXPORT const N::ControlPoint operator +   (N::ControlPoint & v1     , N::ControlPoint & v2            ) ;
Q_GEOMETRY_EXPORT const N::ControlPoint operator -   (N::ControlPoint & v1     , N::ControlPoint & v2            ) ;
Q_GEOMETRY_EXPORT const N::ControlPoint operator -   (N::ControlPoint & vector                                   ) ;
Q_GEOMETRY_EXPORT const N::ControlPoint operator /   (N::ControlPoint & vector , double divisor                  ) ;
Q_GEOMETRY_EXPORT bool                  operator ==  (N::ControlPoint & v1     , N::ControlPoint & v2            ) ;

Q_GEOMETRY_EXPORT const N::ControlPoint operator *   (N::Matrix & m,N::ControlPoint & v) ;

Q_DECLARE_METATYPE(N::ControlPoint)
Q_DECLARE_METATYPE(N::Contour)
Q_DECLARE_METATYPE(N::Plane)
Q_DECLARE_METATYPE(N::Circle)
Q_DECLARE_METATYPE(N::Parabola)
Q_DECLARE_METATYPE(N::Sphere)
Q_DECLARE_METATYPE(N::Cylinder)
Q_DECLARE_METATYPE(N::Polyhedron)
Q_DECLARE_METATYPE(N::QColors)

QT_END_NAMESPACE

#endif
