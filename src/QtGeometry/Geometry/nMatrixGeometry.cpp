#include <qtgeometry.h>

typedef struct   {
  int mtype      ;
  int rows       ;
  int columns    ;
  int size       ;
} MatrixDataType ;

/*
    | x^2*(1-c)+c   x*y*(1-c)-z*s x*z*(1-c)+y*s 0 |
R = | y*x*(1-c)+z*s y^2*(1-c)+c   y*z*(1-c)-x*s 0 |
    | x*z*(1-c)-y*s y*z*(1-c)+x*s z^2*(1-c)+c   0 |
    | 0             0             0             1 |
*/

bool N::Rotation(Matrix & matrix,ControlPoint & R)
{
  MatrixDataType * mdt = (MatrixDataType *)matrix.data() ;
  nKickOut ( IsNull(mdt)       , false )                 ;
  nKickOut ( mdt->rows    != 4 , false )                 ;
  nKickOut ( mdt->columns != 4 , false )                 ;
  double * d    = (double *)matrix.array()               ;
  double   s    = N::Math::fastSine  (R.r)               ;
  double   c    = N::Math::fastCosine(R.r)               ;
  double   cm   = 1.0 - c                                ;
  double   x    = R.x                                    ;
  double   y    = R.y                                    ;
  double   z    = R.z                                    ;
  double   xx   = x * x                                  ;
  double   yy   = y * y                                  ;
  double   zz   = z * z                                  ;
  double   xy   = x * y                                  ;
  double   xz   = x * z                                  ;
  double   yz   = y * z                                  ;
  double   xs   = x * s                                  ;
  double   ys   = y * s                                  ;
  double   zs   = z * s                                  ;
  double   xycm = xy * cm                                ;
  double   xzcm = xz * cm                                ;
  double   yzcm = yz * cm                                ;
  #define M(a,b) d[(a*4)+b]
  M(0,0) = ( xx * cm ) + c                               ; // x^2*(1-c)+c
  M(0,1) = xycm - zs                                     ; // x*y*(1-c)-z*s
  M(0,2) = xzcm + ys                                     ; // x*z*(1-c)+y*s
  M(0,3) = 0                                             ; // 0
  M(1,0) = xycm + zs                                     ; // y*x*(1-c)+z*s
  M(1,1) = ( yy * cm ) + c                               ; // y^2*(1-c)+c
  M(1,2) = yzcm - xs                                     ; // y*z*(1-c)-x*s
  M(1,3) = 0                                             ; // 0
  M(2,0) = xzcm + ys                                     ; // x*z*(1-c)-y*s
  M(2,1) = yzcm + xs                                     ; // y*z*(1-c)+x*s
  M(2,2) = ( zz * cm ) + c                               ; // z^2*(1-c)+c
  M(2,3) = 0                                             ; // 0
  M(3,0) = 0                                             ; // 0
  M(3,1) = 0                                             ; // 0
  M(3,2) = 0                                             ; // 0
  M(3,3) = 1                                             ; // 1
  #undef M
  return true                                            ;
}

bool N::Transform(Matrix & matrix,ControlPoint & S,ControlPoint & T)
{
  MatrixDataType * mdt = (MatrixDataType *)matrix.data()  ;
  nKickOut ( IsNull(mdt)       , false )                  ;
  nKickOut ( mdt->rows    != 4 , false )                  ;
  nKickOut ( mdt->columns != 4 , false )                  ;
  double * d    = (double *)matrix.array()                ;
  double   s[4] = { S.x , S.y , S.z , 1.0 }               ;
  double   r[4]                                           ;
  double   t[4]                                           ;
  #define M(a,b) d[(a*4)+b]
  #define L(i)                                     \
    t[0] = M(0,i) ;                                \
    t[1] = M(1,i) ;                                \
    t[2] = M(2,i) ;                                \
    t[3] = M(3,i)
  #define P(p,i) L(i) ; T.p = matrix.multiple(4,r,s,t)    ;
  P(x,0)                                                  ;
  P(y,1)                                                  ;
  P(z,2)                                                  ;
  #undef  P
  #undef  L
  #undef  M
  return true                                             ;
}

bool N::Assign(Matrix & matrix,const QTransform & transform)
{
  matrix.set(Cpp::Double,3,3)           ;
  double * m = (double *)matrix.array() ;
  m[0] = transform . m11 ( )            ;
  m[1] = transform . m12 ( )            ;
  m[2] = transform . m13 ( )            ;
  m[3] = transform . m21 ( )            ;
  m[4] = transform . m22 ( )            ;
  m[5] = transform . m23 ( )            ;
  m[6] = transform . m31 ( )            ;
  m[7] = transform . m32 ( )            ;
  m[8] = transform . m33 ( )            ;
  return true                           ;
}

bool N::toTransform (QTransform & T,Matrix & matrix)
{
  MatrixDataType * mdt = (MatrixDataType *)matrix.data() ;
  double * m = (double *)matrix.array()                  ;
  T.reset()                                              ;
  if (mdt->columns==3 && mdt->rows==3)                   {
    T.setMatrix                                          (
      m[0],m[1],m[2]                                     ,
      m[3],m[4],m[5]                                     ,
      m[6],m[7],m[8]                                   ) ;
  }                                                      ;
  return true                                            ;
}
