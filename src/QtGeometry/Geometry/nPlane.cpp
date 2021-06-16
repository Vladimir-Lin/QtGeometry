#include <qtgeometry.h>

N::Plane:: Plane (void )
         : A     (false)
{
}

N::Plane:: Plane (const Plane & plane)
{
  ME = plane ;
}

N::Plane::~Plane(void)
{
}

N::Plane & N::Plane::operator = (const Plane & plane)
{
  nMemberCopy ( plane , O ) ;
  nMemberCopy ( plane , X ) ;
  nMemberCopy ( plane , Y ) ;
  nMemberCopy ( plane , T ) ;
  nMemberCopy ( plane , N ) ;
  nMemberCopy ( plane , W ) ;
  nMemberCopy ( plane , H ) ;
  nMemberCopy ( plane , A ) ;
  return ME                 ;
}

bool N::Plane      :: Upon   (
       ControlPoint & At     ,
       ControlPoint & Base   ,
       ControlPoint & Vector ,
       double         detail )
{
  double d   = dotProduct(N,Vector) ;
  double vn  = d                    ;
  if (d<0) d = -d                   ;
  nKickOut ( d < detail , false )   ;
  double s   = 0                    ;
  double obn = 0                    ;
  ControlPoint OB                   ;
  OB  = O                           ;
  OB -= Base                        ;
  obn = dotProduct(OB,N)            ;
  s   = obn / vn                    ;
  OB  = Vector                      ;
  OB *= s                           ;
  At  = Base                        ;
  At += OB                          ;
  return true                       ;
}

QPointF N::Plane::Axis(ControlPoint & At)
{
  ControlPoint D             ;
  QPointF      P             ;
  D  = At                    ;
  D -= O                     ;
  P  . setX(dotProduct(D,X)) ;
  P  . setY(dotProduct(D,Y)) ;
  return P                   ;
}
