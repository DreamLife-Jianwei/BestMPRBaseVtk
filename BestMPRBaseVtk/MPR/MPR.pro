QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    main.cpp \
    bppmprwidget.cpp \
    mprpipeline.cpp

HEADERS += \
    bppmprwidget.h \
    mprpipeline.h

FORMS += \
    bppmprwidget.ui


INCLUDEPATH += ./include/vtk-8.2
LIBS += -L./lib/ -lvtkChartsCore-8.2
LIBS += -L./lib/ -lvtkCommonColor-8.2
LIBS += -L./lib/ -lvtkCommonComputationalGeometry-8.2
LIBS += -L./lib/ -lvtkCommonCore-8.2
LIBS += -L./lib/ -lvtkCommonDataModel-8.2
LIBS += -L./lib/ -lvtkCommonExecutionModel-8.2
LIBS += -L./lib/ -lvtkCommonMath-8.2
LIBS += -L./lib/ -lvtkCommonMisc-8.2
LIBS += -L./lib/ -lvtkCommonSystem-8.2
LIBS += -L./lib/ -lvtkCommonTransforms-8.2
LIBS += -L./lib/ -lvtkDICOMParser-8.2
LIBS += -L./lib/ -lvtkDomainsChemistry-8.2
LIBS += -L./lib/ -lvtkDomainsChemistryOpenGL2-8.2
LIBS += -L./lib/ -lvtkdoubleconversion-8.2
LIBS += -L./lib/ -lvtkexodusII-8.2
LIBS += -L./lib/ -lvtkexpat-8.2
LIBS += -L./lib/ -lvtkFiltersAMR-8.2
LIBS += -L./lib/ -lvtkFiltersCore-8.2
LIBS += -L./lib/ -lvtkFiltersExtraction-8.2
LIBS += -L./lib/ -lvtkFiltersFlowPaths-8.2
LIBS += -L./lib/ -lvtkFiltersGeneral-8.2
LIBS += -L./lib/ -lvtkFiltersGeneric-8.2
LIBS += -L./lib/ -lvtkFiltersGeometry-8.2
LIBS += -L./lib/ -lvtkFiltersHybrid-8.2
LIBS += -L./lib/ -lvtkFiltersHyperTree-8.2
LIBS += -L./lib/ -lvtkFiltersImaging-8.2
LIBS += -L./lib/ -lvtkFiltersModeling-8.2
LIBS += -L./lib/ -lvtkFiltersParallel-8.2
LIBS += -L./lib/ -lvtkFiltersParallelImaging-8.2
LIBS += -L./lib/ -lvtkFiltersPoints-8.2
LIBS += -L./lib/ -lvtkFiltersProgrammable-8.2
LIBS += -L./lib/ -lvtkFiltersSelection-8.2
LIBS += -L./lib/ -lvtkFiltersSMP-8.2
LIBS += -L./lib/ -lvtkFiltersSources-8.2
LIBS += -L./lib/ -lvtkFiltersStatistics-8.2
LIBS += -L./lib/ -lvtkFiltersTexture-8.2
LIBS += -L./lib/ -lvtkFiltersTopology-8.2
LIBS += -L./lib/ -lvtkFiltersVerdict-8.2
LIBS += -L./lib/ -lvtkfreetype-8.2
LIBS += -L./lib/ -lvtkGeovisCore-8.2
LIBS += -L./lib/ -lvtkgl2ps-8.2
LIBS += -L./lib/ -lvtkglew-8.2
LIBS += -L./lib/ -lvtkGUISupportQt-8.2
LIBS += -L./lib/ -lvtkGUISupportQtSQL-8.2
LIBS += -L./lib/ -lvtkhdf5_hl-8.2
LIBS += -L./lib/ -lvtkhdf5-8.2
LIBS += -L./lib/ -lvtkImagingColor-8.2
LIBS += -L./lib/ -lvtkImagingCore-8.2
LIBS += -L./lib/ -lvtkImagingFourier-8.2
LIBS += -L./lib/ -lvtkImagingGeneral-8.2
LIBS += -L./lib/ -lvtkImagingHybrid-8.2
LIBS += -L./lib/ -lvtkImagingMath-8.2
LIBS += -L./lib/ -lvtkImagingMorphological-8.2
LIBS += -L./lib/ -lvtkImagingSources-8.2
LIBS += -L./lib/ -lvtkImagingStatistics-8.2
LIBS += -L./lib/ -lvtkImagingStencil-8.2
LIBS += -L./lib/ -lvtkInfovisCore-8.2
LIBS += -L./lib/ -lvtkInfovisLayout-8.2
LIBS += -L./lib/ -lvtkInteractionImage-8.2
LIBS += -L./lib/ -lvtkInteractionStyle-8.2
LIBS += -L./lib/ -lvtkInteractionWidgets-8.2
LIBS += -L./lib/ -lvtkIOAMR-8.2
LIBS += -L./lib/ -lvtkIOAsynchronous-8.2
LIBS += -L./lib/ -lvtkIOCityGML-8.2
LIBS += -L./lib/ -lvtkIOCore-8.2
LIBS += -L./lib/ -lvtkIOEnSight-8.2
LIBS += -L./lib/ -lvtkIOExodus-8.2
LIBS += -L./lib/ -lvtkIOExport-8.2
LIBS += -L./lib/ -lvtkIOExportOpenGL2-8.2
LIBS += -L./lib/ -lvtkIOExportPDF-8.2
LIBS += -L./lib/ -lvtkIOGeometry-8.2
LIBS += -L./lib/ -lvtkIOImage-8.2
LIBS += -L./lib/ -lvtkIOImport-8.2
LIBS += -L./lib/ -lvtkIOInfovis-8.2
LIBS += -L./lib/ -lvtkIOLegacy-8.2
LIBS += -L./lib/ -lvtkIOLSDyna-8.2
LIBS += -L./lib/ -lvtkIOMINC-8.2
LIBS += -L./lib/ -lvtkIOMovie-8.2
LIBS += -L./lib/ -lvtkIONetCDF-8.2
LIBS += -L./lib/ -lvtkIOParallel-8.2
LIBS += -L./lib/ -lvtkIOParallelXML-8.2
LIBS += -L./lib/ -lvtkIOPLY-8.2
LIBS += -L./lib/ -lvtkIOSegY-8.2
LIBS += -L./lib/ -lvtkIOSQL-8.2
LIBS += -L./lib/ -lvtkIOTecplotTable-8.2
LIBS += -L./lib/ -lvtkIOVeraOut-8.2
LIBS += -L./lib/ -lvtkIOVideo-8.2
LIBS += -L./lib/ -lvtkIOXML-8.2
LIBS += -L./lib/ -lvtkIOXMLParser-8.2
LIBS += -L./lib/ -lvtkjpeg-8.2
LIBS += -L./lib/ -lvtkjsoncpp-8.2
LIBS += -L./lib/ -lvtklibharu-8.2
LIBS += -L./lib/ -lvtklibxml2-8.2
LIBS += -L./lib/ -lvtkLocalExample-8.2
LIBS += -L./lib/ -lvtklz4-8.2
LIBS += -L./lib/ -lvtklzma-8.2
LIBS += -L./lib/ -lvtkmetaio-8.2
LIBS += -L./lib/ -lvtkNetCDF-8.2
LIBS += -L./lib/ -lvtkogg-8.2
LIBS += -L./lib/ -lvtkParallelCore-8.2
LIBS += -L./lib/ -lvtkpng-8.2
LIBS += -L./lib/ -lvtkproj-8.2
LIBS += -L./lib/ -lvtkpugixml-8.2
LIBS += -L./lib/ -lvtkRenderingAnnotation-8.2
LIBS += -L./lib/ -lvtkRenderingContext2D-8.2
LIBS += -L./lib/ -lvtkRenderingContextOpenGL2-8.2
LIBS += -L./lib/ -lvtkRenderingCore-8.2
LIBS += -L./lib/ -lvtkRenderingFreeType-8.2
LIBS += -L./lib/ -lvtkRenderingGL2PSOpenGL2-8.2
LIBS += -L./lib/ -lvtkRenderingImage-8.2
LIBS += -L./lib/ -lvtkRenderingLabel-8.2
LIBS += -L./lib/ -lvtkRenderingLOD-8.2
LIBS += -L./lib/ -lvtkRenderingOpenGL2-8.2
LIBS += -L./lib/ -lvtkRenderingQt-8.2
LIBS += -L./lib/ -lvtkRenderingVolume-8.2
LIBS += -L./lib/ -lvtkRenderingVolumeOpenGL2-8.2
LIBS += -L./lib/ -lvtksqlite-8.2
LIBS += -L./lib/ -lvtksys-8.2
LIBS += -L./lib/ -lvtktheora-8.2
LIBS += -L./lib/ -lvtktiff-8.2
LIBS += -L./lib/ -lvtkverdict-8.2
LIBS += -L./lib/ -lvtkViewsContext2D-8.2
LIBS += -L./lib/ -lvtkViewsCore-8.2
LIBS += -L./lib/ -lvtkViewsInfovis-8.2
LIBS += -L./lib/ -lvtkViewsQt-8.2
LIBS += -L./lib/ -lvtkzlib-8.2




