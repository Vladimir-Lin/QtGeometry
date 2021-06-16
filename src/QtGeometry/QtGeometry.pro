NAME         = QtGeometry
TARGET       = $${NAME}

QT           = core
QT          += gui
QT          += network
QT          += sql
QT          += script
QT          += positioning
QT          += opengl
QT          += QtCUDA
QT          += QtOpenCV
QT          += Essentials
QT          += QtGMP
QT          += QtGSL
QT          += QtAlgebra
QT          += QtDiscrete
QT          += QtFFT
QT          += Mathematics
QT          += QtFuzzy
QT          += QtFLP

load(qt_build_config)
load(qt_module)

INCLUDEPATH += $${PWD}/../../include/$${NAME}

HEADERS     += $${PWD}/../../include/$${NAME}/qtgeometry.h

include ($${PWD}/Linear/Linear.pri)
include ($${PWD}/Geometry/Geometry.pri)

OTHER_FILES += $${PWD}/../../include/$${NAME}/headers.pri

include ($${PWD}/../../doc/Qt/Qt.pri)

TRNAME       = $${NAME}
include ($${PWD}/../../Translations.pri)

win32 {
LIBS        += -lfreetype
LIBS        += -lglu32
LIBS        += -lopengl32
}
