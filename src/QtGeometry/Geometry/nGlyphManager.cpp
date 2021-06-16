#include <qtgeometry.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_FREETYPE_H
#include FT_GLYPH_H
#include FT_OUTLINE_H
#include FT_TRIGONOMETRY_H

typedef struct                     {
  FT_Library        Glyph          ;
  QMap<int,FT_Face> Faces          ;
  BMAPs             Loaded         ;
}                   FreeTypePacket ;

#define FT(IT) (((FreeTypePacket *)FtPacket)->IT)

N::GlyphManager:: GlyphManager ( void                   )
                : FtPacket     ( new FreeTypePacket ( ) )
{
  BuildPathes        (            ) ;
  ::FT_Init_FreeType ( &FT(Glyph) ) ;
}

N::GlyphManager::~GlyphManager (void)
{
  CUIDs IDs = FT(Faces).keys()            ;
  int   id                                ;
  foreach ( id , IDs )                    {
    ::FT_Done_Face   ( FT(Faces) [ id ] ) ;
  }                                       ;
  ::FT_Done_FreeType ( FT(Glyph)        ) ;
  delete FtPacket                         ;
  FtPacket = NULL                         ;
}

void N::GlyphManager::BuildPathes(void)
{
  #ifdef Q_OS_WIN
  QStringList environments = QProcess::systemEnvironment()                   ;
  QString     SystemRoot   = ""                                              ;
  QString     key  = "HKEY_LOCAL_MACHINE\\Software\\Microsoft\\Windows NT\\CurrentVersion\\Fonts" ;
  QSettings   settings ( key , QSettings::NativeFormat )                     ;
  QStringList L    = settings . allKeys ( )                                  ;
  QString     S                                                              ;
  ////////////////////////////////////////////////////////////////////////////
  foreach ( S , environments ) if ( S . contains ( "SystemRoot=" ) )         {
    SystemRoot = S                                                           ;
    SystemRoot = SystemRoot . replace ( "SystemRoot=" , "" )                 ;
  }                                                                          ;
  if ( SystemRoot . length ( ) <= 0 ) return                                 ;
  ////////////////////////////////////////////////////////////////////////////
  QDir W ( SystemRoot )                                                      ;
  foreach ( S , L )                                                          {
    QString     text = settings . value ( S ) . toString ( )                 ;
    QStringList keys                                                         ;
    int         idx                                                          ;
    idx  = S . indexOf ( " (" )                                              ;
    if ( idx >= 0 ) S = S . left ( idx )                                     ;
    idx  = S . indexOf ( "(" )                                               ;
    if ( idx >= 0 ) S = S . left ( idx )                                     ;
    keys = S . split ( " & " )                                               ;
    if ( keys . count ( ) > 0 )                                              {
      QString p = text                                                       ;
      QString f = QString ( "Fonts/%1" ) . arg ( text )                      ;
      f = W . absoluteFilePath ( f )                                         ;
      QFileInfo FI ( f )                                                     ;
      if ( FI . exists ( ) ) p = f ; else                                    {
        QFileInfo FX ( p )                                                   ;
        if ( ! FX . exists ( ) ) p = ""                                      ;
      }                                                                      ;
      if ( p . length ( ) > 0 )                                              {
        QFileInfo FP ( p )                                                   ;
        QString   suffix  = FP . suffix ( )                                  ;
        bool      correct = false                                            ;
        suffix = suffix . toLower ( )                                        ;
        if ( "ttf" == suffix ) correct = true                                ;
        if ( "ttc" == suffix ) correct = true                                ;
        if ( correct )                                                       {
          foreach ( f , keys )                                               {
            f = f . simplified ( )                                           ;
            if ( ! Families . contains ( f ) ) Families << f                 ;
            if ( ! TTFs     . contains ( p ) ) TTFs     << p                 ;
            Pathes [ f ] = p                                                 ;
          }                                                                  ;
        }                                                                    ;
      }                                                                      ;
    }                                                                        ;
  }
  #endif
}

int N::GlyphManager::families(void)
{
  return Families . count ( ) ;
}

QStrings N::GlyphManager::Fonts(void)
{
  return Families ;
}

QString N::GlyphManager::path(QString family)
{
  if ( ! Pathes . contains ( family ) ) return "" ;
  return Pathes [ family ]                        ;
}

int N::GlyphManager::Width(void)
{
  return Dimension . width ( ) ;
}

int N::GlyphManager::Height(void)
{
  return Dimension . height ( ) ;
}

bool N::GlyphManager::isCubic(int tag)
{
  return ( FT_CURVE_TAG_CUBIC == tag ) ;
}

bool N::GlyphManager::isConic(int tag)
{
  return ( FT_CURVE_TAG_CONIC == tag ) ;
}

bool N::GlyphManager::isOn(int tag)
{
  return ( FT_CURVE_TAG_ON == tag ) ;
}

void N::GlyphManager::list(QDir & directory,QStringList f)
{
  QString filename                           ;
  QString s                                  ;
  foreach ( s , f )                          {
    filename = directory.absoluteFilePath(s) ;
    add ( Files.count() , filename )         ;
  }                                          ;
}

void N::GlyphManager::list(QStringList f)
{
  QString s                                   ;
  foreach ( s , f ) add ( Files.count() , s ) ;
}

void N::GlyphManager::add(int index,QString filename)
{
  QFileInfo  FI ( filename )                       ;
  if ( ! FI . exists ( ) ) return                  ;
  QByteArray body                                  ;
  Files [ index ] = filename                       ;
  body            = N::File::toNative ( filename ) ;
  add ( index , (const char *) body . data ( ) )   ;
}

void N::GlyphManager::add(int index,const char * filename)
{
  FT_Face face                                                 ;
  int     error                                                ;
  error   = ::FT_New_Face ( FT(Glyph) , filename , 0 , &face ) ;
  if ( 0 != error ) return                                     ;
  ::FT_Set_Char_Size ( face , 0 , 256 * 64 , 0 , 72 )          ;
  FT(Faces) [ index ] = face                                   ;
  for (int i=0;i<0x110000;i++)                                 {
    FT_UInt  glyph_index                                       ;
    glyph_index = ::FT_Get_Char_Index( face , i )              ;
    if ( glyph_index != 0 )                                    {
      Glyphs     [ i                  ] = (int) glyph_index    ;
      AtFace     [ i                  ] = index                ;
      FT(Loaded) [ (int ) glyph_index ] = false                ;
    }                                                          ;
  }                                                            ;
}

void N::GlyphManager::setPixels (int width,int height)
{
  CUIDs IDs = FT(Faces) . keys ( )     ;
  int   id                             ;
  Dimension = QSize ( width , height ) ;
  foreach ( id , IDs )                 {
    ::FT_Set_Char_Size                 (
        FT(Faces) [ id ]               ,
        width  * 64                    ,
        height * 64                    ,
        72                             ,
        72                           ) ;
  }                                    ;
}

int N::GlyphManager::subglyphs(int unicode)
{
  if ( ! Glyphs . contains ( unicode ) ) return 0            ;
  int face = isLoaded ( unicode )                            ;
  if ( face < 0 ) return 0                                   ;
  return FT(Faces) [ face ] -> glyph -> outline . n_contours ;
}

int N::GlyphManager::points(int unicode,QMap<int,QPoint> & p)
{
  if ( ! Glyphs . contains ( unicode ) ) return 0        ;
  int face  = isLoaded ( unicode )                       ;
  if ( face < 0 ) return  0                              ;
  FT_Outline * outline                                   ;
  FT_Bitmap  * bitmap                                    ;
  bitmap  = & FT(Faces) [ face ] -> glyph -> bitmap      ;
  outline = & FT(Faces) [ face ] -> glyph -> outline     ;
  int bl = FT(Faces)    [ face ] -> glyph -> bitmap_left ;
  int bt = FT(Faces)    [ face ] -> glyph -> bitmap_top  ;
  int w  = bitmap -> width                               ;
  int h  = bitmap -> rows                                ;
  int W  = Dimension . width  ( )                        ;
  int H  = Dimension . height ( )                        ;
  int R  = H - 1                                         ;
  int sx = ( W - w ) / 2 - bl                            ;
  int sy = ( H - h ) / 2 - bt + h                        ;
  for (int i=0;i<outline->n_points;i++)                  {
    QPoint z (     sx + ( outline->points[i].x >> 6 )    ,
               R - sy - ( outline->points[i].y >> 6 )  ) ;
    p [ i ] = z                                          ;
  }                                                      ;
  return p . count ( )                                   ;
}

int N::GlyphManager::points(int unicode,ControlPoint shift,ControlPoints & p)
{
  if ( ! Glyphs . contains ( unicode ) ) return 0        ;
  int face  = isLoaded ( unicode )                       ;
  if ( face < 0 ) return  0                              ;
  FT_Outline * outline                                   ;
  outline = & FT(Faces) [ face ] -> glyph -> outline     ;
  for (int i=0;i<outline->n_points;i++)                  {
    char tag = FT_CURVE_TAG ( outline->tags[i] )         ;
    ControlPoint P                                       ;
    P . x  = outline -> points [ i ] . x                 ;
    P . y  = outline -> points [ i ] . y                 ;
    P . x /= 64.0                                        ;
    P . y /= 64.0                                        ;
    P . z  = 0                                           ;
    P . Type = Graphics::Plane                           ;
    P . x += shift.x                                     ;
    P . y += shift.y                                     ;
    P . z += shift.z                                     ;
    if ( isCubic ( tag ) )                               {
      P . Type |= Graphics::Cubic                        ;
    } else
    if ( isConic ( tag ) )                               {
      P . Type |= Graphics::Quadratic                    ;
    } else
    if ( isOn    ( tag ) )                               {
      P . Type |= Graphics::Flat                         ;
    } else                                               {
      P . Type |= Graphics::End                          ;
    }                                                    ;
    p [ i ] = P                                          ;
  }                                                      ;
  return p . count ( )                                   ;
}

int N::GlyphManager::types(int unicode,QMap<int,int> & t)
{
  if ( ! Glyphs . contains ( unicode ) ) return 0    ;
  int face  = isLoaded ( unicode )                   ;
  if ( face < 0 ) return  0                          ;
  FT_Outline * outline                               ;
  outline = & FT(Faces) [ face ] -> glyph -> outline ;
  for (int i=0;i<outline->n_points;i++)              {
    char tag = FT_CURVE_TAG ( outline->tags[i] )     ;
    t [ i ] = (int)((unsigned char)tag)              ;
  }                                                  ;
  return t.count()                                   ;
}

int N::GlyphManager::contours(int unicode,QMap<int,CUIDs > & c)
{
  if ( ! Glyphs . contains ( unicode ) ) return 0        ;
  int face  = isLoaded ( unicode )                       ;
  if ( face < 0 ) return  0                              ;
  FT_Outline * outline                                   ;
  outline = & FT(Faces) [ face ] -> glyph -> outline     ;
  for (int i=0;i<outline->n_contours;i++)                {
    int s = ( i > 0 ) ? outline->contours[i-1] + 1 : 0   ;
    int e =             outline->contours[i  ]           ;
    for (int j=s;j<=e;j++) c [ i ] << j                  ;
  }                                                      ;
  return c . count ( )                                   ;
}

int N::GlyphManager::count(void)
{
  return Glyphs . count ( ) ;
}

bool N::GlyphManager::contains(int unicode)
{
  return Glyphs . contains ( unicode ) ;
}

int N::GlyphManager::codings(CUIDs & unicodes)
{
  unicodes = Glyphs.keys()                            ;
  qSort ( unicodes . begin ( ) , unicodes . end ( ) ) ;
  return unicodes  . count ( )                        ;
}

int N::GlyphManager::isLoaded(int unicode)
{
  if ( ! Glyphs . contains ( unicode ) ) return -1 ;
  int error                                        ;
  int idx  = Glyphs [ unicode ]                    ;
  int face = AtFace [ unicode ]                    ;
  error = ::FT_Load_Glyph                          (
              FT(Faces) [ face ]                   ,
              idx                                  ,
               FT_LOAD_DEFAULT                   ) ;
  if ( 0 != error ) return -1                      ;
  FT(Loaded)[idx] = true                           ;
  return face                                      ;
}

QRectF N::GlyphManager::BoundingBox(int unicode)
{
  QRectF Z ( 0 , 0 , 0 , 0 )                         ;
  int face = isLoaded ( unicode )                    ;
  if ( face < 0 ) return Z                           ;
  FT_Glyph     glyph                                 ;
  FT_BBox      box                                   ;
  FT_Outline * outline                               ;
  double       left   = 0                            ;
  double       right  = 0                            ;
  double       top    = 0                            ;
  double       bottom = 0                            ;
  ::FT_Get_Glyph     ( FT(Faces)[face]->glyph        ,
                       &glyph                      ) ;
  ::FT_Glyph_Get_CBox( glyph                         ,
                       FT_GLYPH_BBOX_UNSCALED        ,
                       &box                        ) ;
  left    = box . xMin                               ;
  right   = box . xMax                               ;
  top     = box . yMin                               ;
  bottom  = box . yMax                               ;
  ::FT_Done_Glyph ( glyph )                          ;
  outline = & FT(Faces) [ face ] -> glyph -> outline ;
  for (int i=0;i<outline->n_points;i++)              {
    int X = outline -> points [ i ] . x              ;
    int Y = outline -> points [ i ] . y              ;
    if ( left   > X ) left   = X                     ;
    if ( right  < X ) right  = X                     ;
    if ( top    > Y ) top    = Y                     ;
    if ( bottom < Y ) bottom = Y                     ;
  }                                                  ;
  left   /= 64.0                                     ;
  right  /= 64.0                                     ;
  top    /= 64.0                                     ;
  bottom /= 64.0                                     ;
  Z . setLeft   ( left   )                           ;
  Z . setRight  ( right  )                           ;
  Z . setTop    ( top    )                           ;
  Z . setBottom ( bottom )                           ;
  return Z                                           ;
}

bool N::GlyphManager::draw(int unicode,QImage & image,QColor C)
{
  if ( ! Glyphs . contains ( unicode ) ) return false ;
  int error                                           ;
  int face  = isLoaded ( unicode )                    ;
  if ( face < 0 ) return false                        ;
  error = ::FT_Render_Glyph                           (
              FT(Faces) [ face ] -> glyph             ,
              FT_RENDER_MODE_NORMAL                 ) ;
  if ( 0 != error ) return false                      ;
  FT_Bitmap * bitmap                                  ;
  bitmap = & FT(Faces)[face] -> glyph -> bitmap       ;
  int w  = bitmap -> width                            ;
  int h  = bitmap -> rows                             ;
  int W  = image   . width  ( )                       ;
  int H  = image   . height ( )                       ;
  int sx = ( W - w ) / 2                              ;
  int sy = ( H - h ) / 2                              ;
  for (int y=0;y<h;y++) for (int x=0;x<w;x++)         {
    int           a = ( y * w ) + x                   ;
    unsigned char c = 255 - bitmap->buffer[a]         ;
    unsigned char r = c                               ;
    unsigned char g = c                               ;
    unsigned char b = c                               ;
    int           z                                   ;
    z  = 256 - C . red   ( )                          ;
    z *= r                                            ;
    z /= 256                                          ;
    z += C . red   ( )                                ;
    r  = (unsigned char)z                             ;
    z  = 256 - C . green ( )                          ;
    z *= g                                            ;
    z /= 256                                          ;
    z += C . green ( )                                ;
    g  = (unsigned char)z                             ;
    z  = 256 - C . blue  ( )                          ;
    z *= b                                            ;
    z /= 256                                          ;
    z += C . blue  ( )                                ;
    b  = (unsigned char)z                             ;
    QColor        p ( r , g , b       )               ;
    QPoint        l ( x + sx , y + sy )               ;
    image . setPixel( l , p.rgba()    )               ;
  }                                                   ;
  return true                                         ;
}
