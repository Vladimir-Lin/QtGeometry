#include <qtgeometry.h>

N::Circle:: Circle(void)
{
}

N::Circle:: Circle(const Circle & circle)
{
  ME = circle ;
}

N::Circle::~Circle(void)
{
}

N::Circle & N::Circle::operator = (const Circle & circle)
{
  nMemberCopy ( circle , O ) ;
  nMemberCopy ( circle , X ) ;
  nMemberCopy ( circle , Y ) ;
  nMemberCopy ( circle , N ) ;
  return ME                  ;
}

bool N::Circle::Angle(double angle,ControlPoint & P)
{
  ControlPoint C                       ;
  double sin = Math::fastSine  (angle) ;
  double cos = Math::fastCosine(angle) ;
  P          = O                       ;
  C          = X                       ;
  C         *= cos                     ;
  P         += C                       ;
  C          = Y                       ;
  C         *= sin                     ;
  P         += C                       ;
  return true                          ;
}
