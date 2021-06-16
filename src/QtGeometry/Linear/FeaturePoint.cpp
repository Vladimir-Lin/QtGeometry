#include <qtgeometry.h>

typedef struct       {
  int32_t id         ;
  int32_t octave     ;
  float   x          ;
  float   y          ;
  float   size       ;
  float   angle      ;
  float   response   ;
  int32_t extra      ;
} FeaturePointPacket ;

N::FeaturePoint:: FeaturePoint(float X,float Y)
{
  id       = 0 ;
  octave   = 0 ;
  x        = X ;
  y        = Y ;
  size     = 0 ;
  angle    = 0 ;
  response = 0 ;
  extra    = 0 ;
}

N::FeaturePoint:: FeaturePoint (QByteArray Blob)
{
  if (Blob.size()!=sizeof(FeaturePointPacket)) return ;
  FeaturePointPacket * fpp                            ;
  fpp      = (FeaturePointPacket *)Blob.data()        ;
  id       = fpp->id                                  ;
  octave   = fpp->octave                              ;
  x        = fpp->x                                   ;
  y        = fpp->y                                   ;
  size     = fpp->size                                ;
  angle    = fpp->angle                               ;
  response = fpp->response                            ;
  extra    = fpp->extra                               ;
}

N::FeaturePoint:: FeaturePoint(cv::KeyPoint & kp)
{
  id       = kp . class_id ;
  octave   = kp . octave   ;
  x        = kp . pt.x     ;
  y        = kp . pt.y     ;
  size     = kp . size     ;
  angle    = kp . angle    ;
  response = kp . response ;
}

N::FeaturePoint:: FeaturePoint(void)
{
  id       = 0 ;
  octave   = 0 ;
  x        = 0 ;
  y        = 0 ;
  size     = 0 ;
  angle    = 0 ;
  response = 0 ;
  extra    = 0 ;
}

N::FeaturePoint::~FeaturePoint(void)
{
}

int N::FeaturePoint::packetSize(void) const
{
  return sizeof(FeaturePointPacket) ;
}

QByteArray N::FeaturePoint::toByteArray(void)
{
  QByteArray B      ;
  toByteArray ( B ) ;
  return B          ;
}

bool N::FeaturePoint::toByteArray(QByteArray & Blob)
{
  FeaturePointPacket * fpp                     ;
  Blob . resize ( sizeof(FeaturePointPacket) ) ;
  fpp = (FeaturePointPacket *)Blob.data()      ;
  //////////////////////////////////////////////
  fpp -> id       = id                         ;
  fpp -> octave   = octave                     ;
  fpp -> x        = x                          ;
  fpp -> y        = y                          ;
  fpp -> size     = size                       ;
  fpp -> angle    = angle                      ;
  fpp -> response = response                   ;
  fpp -> extra    = extra                      ;
  //////////////////////////////////////////////
  return true                                  ;
}

bool N::FeaturePoint::operator = (QByteArray & Blob)
{
  if (Blob.size()!=sizeof(FeaturePointPacket)) return false ;
  FeaturePointPacket * fpp                                  ;
  fpp      = (FeaturePointPacket *)Blob.data()              ;
  id       = fpp->id                                        ;
  octave   = fpp->octave                                    ;
  x        = fpp->x                                         ;
  y        = fpp->y                                         ;
  size     = fpp->size                                      ;
  angle    = fpp->angle                                     ;
  response = fpp->response                                  ;
  extra    = fpp->extra                                     ;
  return true                                               ;
}

bool N::FeaturePoint::operator = (cv::KeyPoint & kp)
{
  id       = kp . class_id ;
  octave   = kp . octave   ;
  x        = kp . pt.x     ;
  y        = kp . pt.y     ;
  size     = kp . size     ;
  angle    = kp . angle    ;
  response = kp . response ;
  return true              ;
}

bool N::FeaturePoint::toKeyPoint(cv::KeyPoint & keypoint)
{
  keypoint = cv::KeyPoint(x,y,size,angle,response,octave,id) ;
  return true                                                ;
}

cv::KeyPoint N::FeaturePoint::toKeyPoint(void)
{
  return cv::KeyPoint(x,y,size,angle,response,octave,id) ;
}

double N::FeaturePoint::distance(void)
{
  return ( x * x ) + ( y * y ) ;
}

N::FeaturePoint & N::FeaturePoint::operator /=  (QSizeF & s)
{
  x /= s . width  ( ) ;
  y /= s . height ( ) ;
  return ME           ;
}

N::FeaturePoint & N::FeaturePoint::operator /=  (QSize & S)
{
  QSizeF s ( S )      ;
  x /= s . width  ( ) ;
  y /= s . height ( ) ;
  return ME           ;
}
