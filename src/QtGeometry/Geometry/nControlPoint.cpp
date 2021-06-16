#include <qtgeometry.h>

N::ControlPoint:: ControlPoint ( void                )
                : uuid         ( 0                   )
                , Type         ( Graphics::Linear    |
                                 Graphics::None      )
                , DOF          ( DofNone             )
                , Unit         ( Physics::Centimeter )
                , Flag         ( 0                   )
                , x            ( 0                   )
                , y            ( 0                   )
                , z            ( 0                   )
                , t            ( 0                   )
                , r            ( 0                   )
                , f            ( 1                   )
{
}

N::ControlPoint:: ControlPoint ( double X,double Y,double Z )
                : uuid         ( 0                          )
                , Type         ( Graphics::Linear           |
                                 Graphics::None             )
                , DOF          ( DofNone                    )
                , Unit         ( Physics::Centimeter        )
                , Flag         ( 0                          )
                , x            ( X                          )
                , y            ( Y                          )
                , z            ( Z                          )
                , t            ( 0                          )
                , r            ( 0                          )
                , f            ( 1                          )
{
}

N::ControlPoint:: ControlPoint ( double X,double Y,double Z,double R )
                : uuid         ( 0                                   )
                , Type         ( Graphics::Linear | Graphics::None   )
                , DOF          ( DofNone                             )
                , Unit         ( Physics::Centimeter                 )
                , Flag         ( 0                                   )
                , x            ( X                                   )
                , y            ( Y                                   )
                , z            ( Z                                   )
                , t            ( R                                   )
                , r            ( R                                   )
                , f            ( 1                                   )
{
}

N::ControlPoint:: ControlPoint ( QPoint P            )
                : uuid         ( 0                   )
                , Type         ( Graphics::Linear    |
                                 Graphics::None      )
                , DOF          ( DofNone             )
                , Unit         ( Physics::Centimeter )
                , Flag         ( 0                   )
                , x            ( P.x()               )
                , y            ( P.y()               )
                , z            ( 0                   )
                , t            ( 0                   )
                , r            ( 0                   )
                , f            ( 1                   )
{
}

N::ControlPoint:: ControlPoint ( QPointF P           )
                : uuid         ( 0                   )
                , Type         ( Graphics::Linear    |
                                 Graphics::None      )
                , DOF          ( DofNone             )
                , Unit         ( Physics::Centimeter )
                , Flag         ( 0                   )
                , x            ( P.x()               )
                , y            ( P.y()               )
                , z            ( 0                   )
                , t            ( 0                   )
                , r            ( 0                   )
                , f            ( 1                   )
{
}

N::ControlPoint:: ControlPoint ( QVector3D V         )
                : uuid         ( 0                   )
                , Type         ( Graphics::Linear    |
                                 Graphics::None      )
                , DOF          ( DofNone             )
                , Unit         ( Physics::Centimeter )
                , Flag         ( 0                   )
                , x            ( V.x()               )
                , y            ( V.y()               )
                , z            ( V.z()               )
                , t            ( 0                   )
                , r            ( 0                   )
                , f            ( 1                   )
{
}

N::ControlPoint:: ControlPoint ( QColor C            )
                : uuid         ( 0                   )
                , Type         ( Graphics::Linear    |
                                 Graphics::None      )
                , DOF          ( DofNone             )
                , Unit         ( Physics::Centimeter )
                , Flag         ( 0                   )
                , x            ( C.redF   ()         )
                , y            ( C.greenF ()         )
                , z            ( C.blueF  ()         )
                , t            ( C.alphaF ()         )
                , r            ( 0                   )
                , f            ( 1                   )
{
}

N::ControlPoint:: ControlPoint (const ControlPoint & point)
{
  ME = point ;
}

N::ControlPoint:: ControlPoint ( const PackedPoint & p )
                : uuid         ( 0                     )
                , Type         ( Graphics::Linear      |
                                 Graphics::None        )
                , DOF          ( DofNone               )
                , Unit         ( Physics::Centimeter   )
                , Flag         ( 0                     )
                , x            ( p . x                 )
                , y            ( p . y                 )
                , z            ( p . z                 )
                , t            ( p . t                 )
                , r            ( 0                     )
                , f            ( 1                     )
{
}

N::ControlPoint:: ControlPoint ( const PackedControlPoint & p )
                : uuid         ( p . uuid                     )
                , Type         ( p . Type                     )
                , DOF          ( p . DOF                      )
                , Unit         ( p . Unit                     )
                , Flag         ( p . Flag                     )
                , x            ( p . x                        )
                , y            ( p . y                        )
                , z            ( p . z                        )
                , t            ( p . t                        )
                , r            ( p . r                        )
                , f            ( p . f                        )
{
}

N::ControlPoint::~ControlPoint(void)
{
}

int N::ControlPoint::Control(void)
{
  return (int)( Type & 0xFFFF ) ;
}

QPointF N::ControlPoint::Point(void)
{
  return QPointF ( x , y ) ;
}

QPointF N::ControlPoint::Point(int DPI)
{
  double X = x ; X *= DPI ; X *=100 ; X /= 254 ;
  double Y = y ; Y *= DPI ; Y *=100 ; Y /= 254 ;
  return QPointF ( X , Y )                     ;
}

QVector3D N::ControlPoint::Vertex(void)
{
  return QVector3D ( x , y , z ) ;
}

QColor N::ControlPoint::Color(void)
{
  QColor C            ;
  C . setRedF   ( x ) ;
  C . setGreenF ( y ) ;
  C . setBlueF  ( z ) ;
  C . setAlphaF ( t ) ;
  return C            ;
}

bool N::ControlPoint::toPacked(PackedPoint & p)
{
  p . x = x   ;
  p . y = y   ;
  p . z = z   ;
  p . t = t   ;
  return true ;
}

bool N::ControlPoint::toPacked(PackedControlPoint & p)
{
  p . uuid = uuid ;
  p . Type = Type ;
  p . DOF  = DOF  ;
  p . Unit = Unit ;
  p . Flag = Flag ;
  p . x    = x    ;
  p . y    = y    ;
  p . z    = z    ;
  p . t    = t    ;
  p . r    = r    ;
  p . f    = f    ;
  return true     ;
}

bool N::ControlPoint::Within(QPointF & p,double R2)
{
  double dx = x - p . x ( ) ; dx *= dx ;
  double dy = y - p . y ( ) ; dy *= dy ;
  return ( ( dx + dy ) < R2 )          ;
}

double N::ControlPoint::length(void) const
{
  return ::sqrt ( lengthSquared ( ) ) ;
}

double N::ControlPoint::lengthSquared(void) const
{
  return ( x * x ) + ( y * y ) + ( z * z ) ;
}

void N::ControlPoint::normalize(void)
{
  double L = length ( ) ;
  if ( L <= VerySmall ) {
    x = 0               ;
    y = 0               ;
    z = 0               ;
    return              ;
  }                     ;
  x /= L                ;
  y /= L                ;
  z /= L                ;
}

N::ControlPoint N::ControlPoint::normalized(void) const
{
  N::ControlPoint p ;
  p . uuid = uuid   ;
  p . Type = Type   ;
  p . Unit = Unit   ;
  p . x    = x      ;
  p . y    = y      ;
  p . z    = z      ;
  p . r    = r      ;
  p . t    = t      ;
  p . f    = f      ;
  p . normalize ( ) ;
  return p          ;
}

double N::ControlPoint::distanceToLine (
         ControlPoint & point          ,
         ControlPoint & direction      ) const
{
  QVector3D v(x,y,z)                  ;
  QVector3D p                         ;
  QVector3D d                         ;
  p = point     . Vertex ( )          ;
  d = direction . Vertex ( )          ;
  return v . distanceToLine ( p , d ) ;
}

double N::ControlPoint::distanceToPlane (
         ControlPoint & plane           ,
         ControlPoint & normalx         ) const
{
  QVector3D v(x,y,z)                   ;
  QVector3D p                          ;
  QVector3D n                          ;
  p = plane   . Vertex ( )             ;
  n = normalx . Vertex ( )             ;
  return v . distanceToPlane ( p , n ) ;
}

double N::ControlPoint::distanceToPlane (
         ControlPoint & plane1          ,
         ControlPoint & plane2          ,
         ControlPoint & plane3          ) const
{
   QVector3D v(x,y,z)                          ;
   QVector3D p1                                ;
   QVector3D p2                                ;
   QVector3D p3                                ;
   p1 = plane1.Vertex()                        ;
   p2 = plane2.Vertex()                        ;
   p3 = plane3.Vertex()                        ;
   return v . distanceToPlane ( p1 , p2 , p3 ) ;
}

N::ControlPoint & N::ControlPoint::operator = (const N::ControlPoint & p)
{
  uuid = p . uuid ;
  Type = p . Type ;
  Unit = p . Unit ;
  DOF  = p . DOF  ;
  x    = p . x    ;
  y    = p . y    ;
  z    = p . z    ;
  r    = p . r    ;
  t    = p . t    ;
  f    = p . f    ;
  return (*this)  ;
}

N::ControlPoint & N::ControlPoint::operator = (const QPointF & p)
{
  x = p . x ( )  ;
  y = p . y ( )  ;
  return (*this) ;
}

N::ControlPoint & N::ControlPoint::operator = (const QVector3D & p)
{
  x = p . x ( )  ;
  y = p . y ( )  ;
  z = p . z ( )  ;
  return (*this) ;
}

N::ControlPoint & N::ControlPoint::operator = (const QColor & c)
{
  x = c . redF   ( ) ;
  y = c . greenF ( ) ;
  z = c . blueF  ( ) ;
  t = c . alphaF ( ) ;
  return (*this)     ;
}

N::ControlPoint & N::ControlPoint::operator *= (double factor)
{
  x *= factor    ;
  y *= factor    ;
  z *= factor    ;
  return (*this) ;
}

N::ControlPoint & N::ControlPoint::operator *= (const N::ControlPoint & vector)
{
  x *= vector . x ;
  y *= vector . y ;
  z *= vector . z ;
  return (*this)  ;
}

N::ControlPoint & N::ControlPoint::operator += (const N::ControlPoint & vector)
{
  x += vector . x ;
  y += vector . y ;
  z += vector . z ;
  return (*this)  ;
}

N::ControlPoint & N::ControlPoint::operator -= (const N::ControlPoint & vector)
{
  x -= vector . x ;
  y -= vector . y ;
  z -= vector . z ;
  return (*this)  ;
}

N::ControlPoint & N::ControlPoint::operator /= (double divisor)
{
  x /= divisor   ;
  y /= divisor   ;
  z /= divisor   ;
  return (*this) ;
}

void N::ControlPoint::Light(GLenum light,GLenum pname)
{
  GLfloat f [ 4 ] = { x , y , z , t } ;
  QtGL::Lightfv ( light , pname , f ) ;
}

void N::ControlPoint::Material(GLenum face,GLenum pname)
{
  GLfloat f [ 4 ] = { x , y , z , t }       ;
  QtGL::Materialfv ( face , pname , 4 , f ) ;
}

void N::ControlPoint::Vertex3f(void)
{
  #if defined(Q_OS_ANDROID)
  GLfloat F[3] = { x , y , z } ;
  QtGL::VertexPointer(3,GL_FLOAT,0,F);
  #elif defined(Q_OS_IOS)
  GLfloat F[3] = { x , y , z } ;
  QtGL::VertexPointer(3,GL_FLOAT,0,F);
  #else
  QtGL::Vertex3f ( x , y , z ) ;
  #endif
}

void N::ControlPoint::Vertex3d(void)
{
  #if defined(Q_OS_ANDROID)
  GLdouble F[3] = { x , y , z } ;
  QtGL::VertexPointer(3,GL_DOUBLE,0,F);
  #elif defined(Q_OS_IOS)
  GLfloat F[3] = { x , y , z } ;
  QtGL::VertexPointer(3,GL_FLOAT,0,F);
  #else
  QtGL::Vertex3dv ( &x ) ;
  #endif
}

void N::ControlPoint::Normal3f(void)
{
  QtGL::Normal3f ( x , y , z ) ;
}

void N::ControlPoint::Normal3d(void)
{
  QtGL::Normal3dv ( &x ) ;
}

void N::ControlPoint::Translatef(void)
{
  QtGL::Translatef ( x , y , z ) ;
}

void N::ControlPoint::Translate(void)
{
  QtGL::Translatedv ( &x ) ;
}

void N::ControlPoint::Rotatef(void)
{
  QtGL::Rotatef ( r , x , y , z ) ;
}

void N::ControlPoint::Rotate(void)
{
  #if defined(Q_OS_ANDROID)
  QtGL::Rotatef ( r , x , y , z ) ;
  #elif defined(Q_OS_IOS)
  QtGL::Rotatef ( r , x , y , z ) ;
  #else
  QtGL::Rotated ( r , x , y , z ) ;
  #endif
}

void N::ControlPoint::Scalef(void)
{
  QtGL::Scalef ( x , y , z ) ;
}

void N::ControlPoint::Scale(void)
{
  #if defined(Q_OS_ANDROID)
  QtGL::Scalef ( x , y , z ) ;
  #elif defined(Q_OS_IOS)
  QtGL::Scalef ( x , y , z ) ;
  #else
  QtGL::Scaled ( x , y , z ) ;
  #endif
}

void N::ControlPoint::Color3f(void)
{
  #if defined(Q_OS_ANDROID)
  QtGL::Color4f ( x , y , z , 1 ) ;
  #elif defined(Q_OS_IOS)
  QtGL::Color4f ( x , y , z , 1 ) ;
  #else
  QtGL::Color3f ( x , y , z ) ;
  #endif
}

void N::ControlPoint::Color4f(void)
{
  QtGL::Color4f  (  x , y , z , t ) ;
}

void N::ControlPoint::Color3d(void)
{
  QtGL::Color3dv ( &x ) ;
}

void N::ControlPoint::Color4d(void)
{
  QtGL::Color4dv ( &x ) ;
}

N::ControlPoint interpolate (N::ControlPoint & v1,N::ControlPoint & v2,double t)
{ // this is a faster algorithm, only 3 multiply and 6 additions
  N::ControlPoint u ;
  N::ControlPoint v ;
  u  = v2           ;
  u -= v1           ;
  u *= t            ;
  v  = v1           ;
  v += u            ;
  return v          ;
}

N::ControlPoint crossProduct (N::ControlPoint & v1,N::ControlPoint & v2)
{
  N::ControlPoint cp                                 ;
  cp . x = ( v1 . y * v2 . z ) - ( v1 . z * v2 . y ) ;
  cp . y = ( v1 . z * v2 . x ) - ( v1 . x * v2 . z ) ;
  cp . z = ( v1 . x * v2 . y ) - ( v1 . y * v2 . x ) ;
  cp . t = 1                                         ;
  return cp                                          ;
}

double dotProduct (N::ControlPoint & v1,N::ControlPoint & v2)
{
  QVector3D p1                             ;
  QVector3D p2                             ;
  p1 = v1.Vertex()                         ;
  p2 = v2.Vertex()                         ;
  return QVector3D::dotProduct ( p1 , p2 ) ;
}

N::ControlPoint Normal (N::ControlPoint & v1,N::ControlPoint & v2)
{
  N::ControlPoint cp            ;
  QVector3D       vp            ;
  QVector3D       p1            ;
  QVector3D       p2            ;
  p1 = v1.Vertex()              ;
  p2 = v2.Vertex()              ;
  vp = QVector3D::normal(p1,p2) ;
  cp = vp                       ;
  return cp                     ;
}

N::ControlPoint Normal (N::ControlPoint & v1,N::ControlPoint & v2,N::ControlPoint & v3)
{
  N::ControlPoint cp               ;
  QVector3D       vp               ;
  QVector3D       p1               ;
  QVector3D       p2               ;
  QVector3D       p3               ;
  p1 = v1.Vertex()                 ;
  p2 = v2.Vertex()                 ;
  p3 = v3.Vertex()                 ;
  vp = QVector3D::normal(p1,p2,p3) ;
  cp = vp                          ;
  return cp                        ;
}

bool FuzzyCompare(N::ControlPoint & v1,N::ControlPoint & v2)
{
  QVector3D p1                ;
  QVector3D p2                ;
  p1 = v1.Vertex()            ;
  p2 = v2.Vertex()            ;
  return qFuzzyCompare(p1,p2) ;
}

bool operator != (N::ControlPoint & v1,N::ControlPoint & v2)
{
  QVector3D p1     ;
  QVector3D p2     ;
  p1 = v1.Vertex() ;
  p2 = v2.Vertex() ;
  return p1 != p2  ;
}

const N::ControlPoint operator * (double factor,N::ControlPoint & vector)
{
  N::ControlPoint cp ;
  cp  = vector       ;
  cp *= factor       ;
  cp  . uuid = 0     ;
  return cp          ;
}

const N::ControlPoint operator * (N::ControlPoint & vector,double factor)
{
  N::ControlPoint cp ;
  cp  = vector       ;
  cp *= factor       ;
  cp  . uuid = 0     ;
  return cp          ;
}

const N::ControlPoint operator * (N::ControlPoint & v1,N::ControlPoint & v2)
{
  N::ControlPoint cp ;
  cp  = v1           ;
  cp *= v2           ;
  cp  . uuid = 0     ;
  return cp          ;
}

const N::ControlPoint operator + (N::ControlPoint & v1,N::ControlPoint & v2)
{
  N::ControlPoint cp ;
  cp         = v1    ;
  cp        += v2    ;
  cp  . uuid = 0     ;
  return cp          ;
}

const N::ControlPoint operator - (N::ControlPoint & v1,N::ControlPoint & v2)
{
  N::ControlPoint cp ;
  cp         = v1    ;
  cp        -= v2    ;
  cp  . uuid = 0     ;
  return cp          ;
}

const N::ControlPoint operator - (N::ControlPoint & vector)
{
  N::ControlPoint cp  ;
  cp        = vector  ;
  cp . x    = -cp . x ;
  cp . y    = -cp . y ;
  cp . z    = -cp . z ;
  cp . uuid = 0       ;
  return cp           ;
}

const N::ControlPoint operator / (N::ControlPoint & vector,double divisor)
{
  N::ControlPoint cp ;
  cp  = vector       ;
  cp /= divisor      ;
  cp  . uuid = 0     ;
  return cp          ;
}

bool operator == (N::ControlPoint & v1,N::ControlPoint & v2)
{
  QVector3D p1     ;
  QVector3D p2     ;
  p1 = v1.Vertex() ;
  p2 = v2.Vertex() ;
  return p1 == p2  ;
}

const N::ControlPoint operator * (N::Matrix & m,N::ControlPoint & v)
{
  N::ControlPoint p                                            ;
  p = v                                                        ;
  if (m.Rows   ()!=4) return  p                                ;
  if (m.Columns()!=4) return  p                                ;
  double * d = (double *) m . array ( )                             ;
  #define EX(it,id) ( v . it * d [ id ] )
  p . x  = EX ( x , 0 ) + (v.y*d[ 4]) + (v.z*d[ 8]) + (v.t*d[12]) ;
  p . y  = ( v.x*d[ 1]) + (v.y*d[ 5]) + (v.z*d[ 9]) + (v.t*d[13]) ;
  p . z  = ( v.x*d[ 2]) + (v.y*d[ 6]) + (v.z*d[10]) + (v.t*d[14]) ;
  p . t  = ( v.x*d[ 3]) + (v.y*d[ 7]) + (v.z*d[11]) + (v.t*d[15]) ;
  #undef  EX
  return p                                                     ;
}

void N::OpenGL::Vertices(CUIDs Index,N::ControlPoints Points)
{
  if (Index .count()<=0) return ;
  if (Points.count()<=0) return ;
  CUID id                       ;
  foreach (id,Index)            {
    Points[id] . Vertex3f ( )   ;
  }                             ;
}

bool Between(N::ControlPoint & p,N::ControlPoint & pmin,N::ControlPoint & pmax)
{
  if ( p . x < pmin . x ) return false ;
  if ( p . y < pmin . y ) return false ;
  if ( p . z < pmin . z ) return false ;
  if ( p . x > pmax . x ) return false ;
  if ( p . y > pmax . y ) return false ;
  if ( p . z > pmax . z ) return false ;
  return true                          ;
}

bool IntersectRectangle     (
       N::ControlPoint & P  ,
       N::ControlPoint & Z0 ,
       N::ControlPoint & Z1 ,
       N::ControlPoint & Z3 ,
       N::ControlPoint & P1 ,
       N::ControlPoint & P2 )
{
  N::ControlPoint Vx                                                         ;
  N::ControlPoint Vy                                                         ;
  N::ControlPoint Np                                                         ;
  N::ControlPoint Vp                                                         ;
  N::ControlPoint Wp                                                         ;
  N::ControlPoint Sp                                                         ;
  double          t                                                          ;
  double          v                                                          ;
  double          pv                                                         ;
  double          dx                                                         ;
  double          dy                                                         ;
  double          fx                                                         ;
  double          fy                                                         ;
  ////////////////////////////////////////////////////////////////////////////
  // Vx = Z1 - Z0
  Vx . x = Z1 . x - Z0 . x                                                   ;
  Vx . y = Z1 . y - Z0 . y                                                   ;
  Vx . z = Z1 . z - Z0 . z                                                   ;
  ////////////////////////////////////////////////////////////////////////////
  // Vy = Z3 - Z0
  Vy . x = Z3 . x - Z0 . x                                                   ;
  Vy . y = Z3 . y - Z0 . y                                                   ;
  Vy . z = Z3 . z - Z0 . z                                                   ;
  ////////////////////////////////////////////////////////////////////////////
  // Vp = P2  - P1
  Vp . x = P2 . x - P1 . x                                                   ;
  Vp . y = P2 . y - P1 . y                                                   ;
  Vp . z = P2 . z - P1 . z                                                   ;
  ////////////////////////////////////////////////////////////////////////////
  // Wp = Z0 - P1
  Wp . x = Z0 . x - P1 . x                                                   ;
  Wp . y = Z0 . y - P1 . y                                                   ;
  Wp . z = Z0 . z - P1 . z                                                   ;
  ////////////////////////////////////////////////////////////////////////////
  // Np = Vx x Vy
  Np . x = ( Vx . y * Vy . z ) - ( Vx . z * Vy . y )                         ;
  Np . y = ( Vx . z * Vy . x ) - ( Vx . x * Vy . z )                         ;
  Np . z = ( Vx . x * Vy . y ) - ( Vx . y * Vy . x )                         ;
  ////////////////////////////////////////////////////////////////////////////
  // v = Np * Vp
  v      = ( Np . x * Vp . x ) + ( Np . y * Vp . y ) + ( Np . z * Vp . z )   ;
  pv     = v                                                                 ;
  if ( pv < 0         ) pv = -pv                                             ;
  if ( pv < VerySmall ) return false                                         ;
  ////////////////////////////////////////////////////////////////////////////
  // t = Np * Wp / Np * Vp
  t      = ( Np . x * Wp . x ) + ( Np . y * Wp . y ) + ( Np . z * Wp . z )   ;
  t     /= v                                                                 ;
  if ( t < 0          ) return false                                         ;
  ////////////////////////////////////////////////////////////////////////////
  // P =P1 + tVp
  P . x  = P1 . x + ( t * Vp . x )                                           ;
  P . y  = P1 . y + ( t * Vp . y )                                           ;
  P . z  = P1 . z + ( t * Vp . z )                                           ;
  P . t  = 1                                                                 ;
  ////////////////////////////////////////////////////////////////////////////
  // Sp = P - Z0
  Sp . x = P . x - Z0 . x                                                    ;
  Sp . y = P . y - Z0 . y                                                    ;
  Sp . z = P . z - Z0 . z                                                    ;
  ////////////////////////////////////////////////////////////////////////////
  dx     = ( Vx . x * Vx . x ) + ( Vx . y * Vx . y ) + ( Vx . z * Vx . z )   ;
  pv     = dx                                                                ;
  if ( pv < 0         ) pv = -pv                                             ;
  if ( pv < VerySmall ) return false                                         ;
  ////////////////////////////////////////////////////////////////////////////
  dy     = ( Vy . x * Vy . x ) + ( Vy . y * Vy . y ) + ( Vy . z * Vy . z )   ;
  pv     = dy                                                                ;
  if ( pv < 0         ) pv = -pv                                             ;
  if ( pv < VerySmall ) return false                                         ;
  ////////////////////////////////////////////////////////////////////////////
  fx     = ( Sp . x * Vx . x ) + ( Sp . y * Vx . y ) + ( Sp . z * Vx . z )   ;
  fy     = ( Sp . x * Vy . x ) + ( Sp . y * Vy . y ) + ( Sp . z * Vy . z )   ;
  fx    /= dx                                                                ;
  fy    /= dy                                                                ;
  ////////////////////////////////////////////////////////////////////////////
  if ( fx < 0.0 ) return false                                               ;
  if ( fy < 0.0 ) return false                                               ;
  if ( fx > 1.0 ) return false                                               ;
  if ( fy > 1.0 ) return false                                               ;
  ////////////////////////////////////////////////////////////////////////////
  return true                                                                ;
}
