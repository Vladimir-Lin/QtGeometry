#include <qtgeometry.h>

N::Sphere:: Sphere(void)
{
}

N::Sphere:: Sphere(const Sphere & sphere)
{
  ME = sphere ;
}

N::Sphere::~Sphere(void)
{
}

N::Sphere & N::Sphere::operator = (const Sphere & sphere)
{
  nMemberCopy ( sphere , O ) ;
  nMemberCopy ( sphere , X ) ;
  nMemberCopy ( sphere , Y ) ;
  nMemberCopy ( sphere , R ) ;
  nMemberCopy ( sphere , N ) ;
  return ME                  ;
}
