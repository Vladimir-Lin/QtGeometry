#include <qtgeometry.h>

N::FeaturePoints:: FeaturePoints         (QByteArray & Blob)
                 : QList<FeaturePoint *> (                 )
{
  fromByteArray ( Blob ) ;
}

N::FeaturePoints:: FeaturePoints         (void)
                 : QList<FeaturePoint *> (    )
{
}

N::FeaturePoints::~FeaturePoints (void)
{
}

int N::FeaturePoints::fromByteArray (QByteArray & Blob)
{
  FeaturePoint FP                                 ;
  int          ps    = FP   . packetSize ( )      ;
  int          total = Blob . size       ( ) / ps ;
  if (total<=0) return count ( )                  ;
  for (int i=0;i<total;i++)                       {
    QByteArray   B = Blob . mid ( i * ps , ps )   ;
    FeaturePoint * X                              ;
    X = new FeaturePoint ( B )                    ;
    append               ( X )                    ;
  }                                               ;
  return count ( )                                ;
}

QByteArray N::FeaturePoints::toByteArray(void)
{
  QByteArray B      ;
  toByteArray ( B ) ;
  return B          ;
}

bool N::FeaturePoints::toByteArray(QByteArray & Blob)
{
  for (int i=0;i<count();i++) {
    QByteArray B              ;
    B = ME[i]->toByteArray()  ;
    Blob . append ( B )       ;
  }                           ;
  return ( Blob.size() > 0 )  ;
}

bool N::FeaturePoints::operator = (QByteArray & Blob)
{
  clear         (      ) ;
  fromByteArray ( Blob ) ;
  return ( count() > 0 ) ;
}

bool N::FeaturePoints::operator << (QByteArray & Blob)
{
  fromByteArray ( Blob ) ;
  return ( count() > 0 ) ;
}

bool N::FeaturePoints::operator = (std::vector<cv::KeyPoint> & keypoints)
{
  clear  (             ) ;
  ME << keypoints        ;
  return ( count() > 0 ) ;
}

bool N::FeaturePoints::operator << (std::vector<cv::KeyPoint> & kps)
{
  for (int i=0;i<kps.size();i++)    {
    FeaturePoint * X                ;
    X = new FeaturePoint ( kps[i] ) ;
    append               ( X      ) ;
  }                                 ;
  return ( count() > 0 )            ;
}

bool N::FeaturePoints::toKeyPoints(std::vector<cv::KeyPoint> & keypoints)
{
  for (int i=0;i<count();i++)                         {
    keypoints . push_back ( ME[i] -> toKeyPoint ( ) ) ;
  }                                                   ;
  return ( keypoints . size ( ) > 0 )                 ;
}

std::vector<cv::KeyPoint> N::FeaturePoints::toKeyPoints(void)
{
  std::vector<cv::KeyPoint> KTs ;
  toKeyPoints ( KTs )           ;
  return KTs                    ;
}

double N::FeaturePoints::distance(void)
{
  if (count()<=0) return 0    ;
  int    a = count()          ;
  double t = 0                ;
  for (int i=0;i<a;i++)       {
    t += ME[i]->distance()    ;
  }                           ;
  return t / a                ;
}

double N::FeaturePoints::x(void)
{
  if (count()<=0) return 0    ;
  int    a = count()          ;
  double t = 0                ;
  for (int i=0;i<a;i++)       {
    t += ME[i]->x             ;
  }                           ;
  return t / a                ;
}

double N::FeaturePoints::y(void)
{
  if (count()<=0) return 0    ;
  int    a = count()          ;
  double t = 0                ;
  for (int i=0;i<a;i++)       {
    t += ME[i]->y             ;
  }                           ;
  return t / a                ;
}

QRectF N::FeaturePoints::Range(void)
{
  if (count()<=0) return QRectF(0,0,0,0) ;
  int    a = count()                     ;
  double l = 1000000000.0                ;
  double r = -1                          ;
  double t = 1000000000.0                ;
  double b = -1                          ;
  for (int i=0;i<a;i++)                  {
    double X = ME[i]->x                  ;
    double Y = ME[i]->y                  ;
    if (X<l) l = X                       ;
    if (X>r) r = X                       ;
    if (Y<t) t = Y                       ;
    if (Y>b) b = Y                       ;
  }                                      ;
  return QRectF ( l , t , r-l , b-t )    ;
}

N::FeaturePoints & N::FeaturePoints::operator /= (QSizeF & s)
{
  for (int i=0;i<count();i++) {
    *(ME[i]) /= s             ;
  }                           ;
  return ME                   ;
}

N::FeaturePoints & N::FeaturePoints::operator /= (QSize & S)
{
  QSizeF s ( S )              ;
  for (int i=0;i<count();i++) {
    *(ME[i]) /= s             ;
  }                           ;
  return ME                   ;
}
