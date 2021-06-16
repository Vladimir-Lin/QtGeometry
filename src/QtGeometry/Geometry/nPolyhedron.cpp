#include <qtgeometry.h>

N::Polyhedron:: Polyhedron(void)
{
}

N::Polyhedron:: Polyhedron(const Polyhedron & polyhedron)
{
  ME = polyhedron ;
}

N::Polyhedron::~Polyhedron(void)
{
}

N::Polyhedron & N::Polyhedron::operator = (const Polyhedron & polyhedron)
{
  nMemberCopy ( polyhedron , type      ) ;
  nMemberCopy ( polyhedron , points    ) ;
  nMemberCopy ( polyhedron , arguments ) ;
  return ME                              ;
}
