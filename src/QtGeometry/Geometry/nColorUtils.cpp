#include <qtgeometry.h>

int N::Graphics::toVector(Colors & colors,QVector<QRgb> & rgb)
{
  int t = colors.count()   ;
  for (int i=0;i<t;i++)    {
    rgb << (QRgb)colors[i] ;
  }                        ;
  return t                 ;
}

int N::Graphics::toByteArray(Colors & colors,QByteArray & blob)
{
  int t = colors.count()                         ;
  int s = t * sizeof(unsigned int)               ;
  ////////////////////////////////////////////////
  if (t<=0)                                      {
    blob.clear()                                 ;
    return 0                                     ;
  }                                              ;
  ////////////////////////////////////////////////
  blob . resize ( s )                            ;
  if (blob.size()!=s)                            {
    blob.clear()                                 ;
    return 0                                     ;
  }                                              ;
  ////////////////////////////////////////////////
  unsigned int * d = (unsigned int *)blob.data() ;
  for (int i=0;i<t;i++) d[i] = colors[i]         ;
  return t                                       ;
}

int N::Graphics::toColors(QImage & image,Colors & colors)
{
  int w = image . width  ( )                    ;
  int h = image . height ( )                    ;
  for (int y=0;y<h;y++) for (int x=0;x<w;x++)   {
    colors << (unsigned int)image.pixel(x,y)    ;
  }                                             ;
  return N::Graphics::Uniqueness(colors)        ;
}

int N::Graphics::addColors(QByteArray & blob,Colors & colors)
{
  int t = blob.size() / sizeof(unsigned int)     ;
  if (t<=0) return colors.count()                ;
  unsigned int * d = (unsigned int *)blob.data() ;
  for (int i=0;i<t;i++) colors << d[i]           ;
  return colors.count()                          ;
}

int N::Graphics::Uniqueness(Colors & colors)
{
  int t = colors.count()   ;
  nKickOut ( t <= 1 , t )  ;
  Colors      C            ;
  unsigned int c           ;
  unsigned int v           ;
  C = colors               ;
  qSort(C.begin(),C.end()) ;
  colors . clear ( )       ;
  c = C[0]                 ;
  colors << c              ;
  for (int i=1;i<t;i++)    {
    v = C[i]               ;
    if (c!=v)              {
      colors << v          ;
      c = v                ;
    }                      ;
  }                        ;
  return colors.count()    ;
}
