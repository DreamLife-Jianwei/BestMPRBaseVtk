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


INCLUDEPATH += ./include/vtk-9.0

LIBS += -L./lib/ -lvtkDICOMParser-9.0
LIBS += -L./lib/ -lvtkDomainsChemistry-9.0
LIBS += -L./lib/ -lvtkDomainsChemistryOpenGL2-9.0
LIBS += -L./lib/ -lvtkdoubleconversion-9.0
LIBS += -L./lib/ -lvtkexodusII-9.0
LIBS += -L./lib/ -lvtkexpat-9.0
LIBS += -L./lib/ -lvtkFiltersAMR-9.0
LIBS += -L./lib/ -lvtkFiltersCore-9.0
LIBS += -L./lib/ -lvtkFiltersExtraction-9.0
LIBS += -L./lib/ -lvtkFiltersFlowPaths-9.0
LIBS += -L./lib/ -lvtkFiltersGeneral-9.0
LIBS += -L./lib/ -lvtkFiltersGeneric-9.0
LIBS += -L./lib/ -lvtkFiltersGeometry-9.0
LIBS += -L./lib/ -lvtkFiltersHybrid-9.0
LIBS += -L./lib/ -lvtkFiltersHyperTree-9.0
LIBS += -L./lib/ -lvtkFiltersImaging-9.0
LIBS += -L./lib/ -lvtkFiltersModeling-9.0
LIBS += -L./lib/ -lvtkFiltersParallel-9.0
LIBS += -L./lib/ -lvtkFiltersParallelImaging-9.0
LIBS += -L./lib/ -lvtkFiltersPoints-9.0
LIBS += -L./lib/ -lvtkFiltersProgrammable-9.0
LIBS += -L./lib/ -lvtkFiltersSelection-9.0
LIBS += -L./lib/ -lvtkFiltersSMP-9.0
LIBS += -L./lib/ -lvtkFiltersSources-9.0
LIBS += -L./lib/ -lvtkFiltersStatistics-9.0
LIBS += -L./lib/ -lvtkFiltersTexture-9.0
LIBS += -L./lib/ -lvtkFiltersTopology-9.0
LIBS += -L./lib/ -lvtkFiltersVerdict-9.0
LIBS += -L./lib/ -lvtkfreetype-9.0
LIBS += -L./lib/ -lvtkGeovisCore-9.0
LIBS += -L./lib/ -lvtkgl2ps-9.0
LIBS += -L./lib/ -lvtkglew-9.0
LIBS += -L./lib/ -lvtkGUISupportQt-9.0
LIBS += -L./lib/ -lvtkGUISupportQtSQL-9.0
LIBS += -L./lib/ -lvtkhdf5_hl-9.0
LIBS += -L./lib/ -lvtkhdf5-9.0
LIBS += -L./lib/ -lvtkImagingColor-9.0
LIBS += -L./lib/ -lvtkImagingCore-9.0
LIBS += -L./lib/ -lvtkImagingFourier-9.0
LIBS += -L./lib/ -lvtkImagingGeneral-9.0
LIBS += -L./lib/ -lvtkImagingHybrid-9.0
LIBS += -L./lib/ -lvtkImagingMath-9.0
LIBS += -L./lib/ -lvtkImagingMorphological-9.0
LIBS += -L./lib/ -lvtkImagingSources-9.0
LIBS += -L./lib/ -lvtkImagingStatistics-9.0
LIBS += -L./lib/ -lvtkImagingStencil-9.0
LIBS += -L./lib/ -lvtkInfovisCore-9.0
LIBS += -L./lib/ -lvtkInfovisLayout-9.0
LIBS += -L./lib/ -lvtkInteractionImage-9.0
LIBS += -L./lib/ -lvtkInteractionStyle-9.0
LIBS += -L./lib/ -lvtkInteractionWidgets-9.0
LIBS += -L./lib/ -lvtkIOAMR-9.0
LIBS += -L./lib/ -lvtkIOAsynchronous-9.0
LIBS += -L./lib/ -lvtkIOCityGML-9.0
LIBS += -L./lib/ -lvtkIOCore-9.0
LIBS += -L./lib/ -lvtkIOEnSight-9.0
LIBS += -L./lib/ -lvtkIOExodus-9.0
LIBS += -L./lib/ -lvtkIOExport-9.0
LIBS += -L./lib/ -lvtkIOExportGL2PS-9.0
LIBS += -L./lib/ -lvtkIOExportPDF-9.0
LIBS += -L./lib/ -lvtkIOGeometry-9.0
LIBS += -L./lib/ -lvtkIOImage-9.0
LIBS += -L./lib/ -lvtkIOImport-9.0
LIBS += -L./lib/ -lvtkIOInfovis-9.0
LIBS += -L./lib/ -lvtkIOLegacy-9.0
LIBS += -L./lib/ -lvtkIOLSDyna-9.0
LIBS += -L./lib/ -lvtkIOMINC-9.0
LIBS += -L./lib/ -lvtkIOMotionFX-9.0
LIBS += -L./lib/ -lvtkIOMovie-9.0
LIBS += -L./lib/ -lvtkIONetCDF-9.0
LIBS += -L./lib/ -lvtkIOOggTheora-9.0
LIBS += -L./lib/ -lvtkIOParallel-9.0
LIBS += -L./lib/ -lvtkIOParallelXML-9.0
LIBS += -L./lib/ -lvtkIOPLY-9.0
LIBS += -L./lib/ -lvtkIOSegY-9.0
LIBS += -L./lib/ -lvtkIOSQL-9.0
LIBS += -L./lib/ -lvtkIOTecplotTable-9.0
LIBS += -L./lib/ -lvtkIOVeraOut-9.0
LIBS += -L./lib/ -lvtkIOVideo-9.0
LIBS += -L./lib/ -lvtkIOXML-9.0
LIBS += -L./lib/ -lvtkIOXMLParser-9.0
LIBS += -L./lib/ -lvtkjpeg-9.0
LIBS += -L./lib/ -lvtkjsoncpp-9.0
LIBS += -L./lib/ -lvtklibharu-9.0
LIBS += -L./lib/ -lvtklibproj-9.0
LIBS += -L./lib/ -lvtklibxml2-9.0
LIBS += -L./lib/ -lvtkloguru-9.0
LIBS += -L./lib/ -lvtklz4-9.0
LIBS += -L./lib/ -lvtklzma-9.0
LIBS += -L./lib/ -lvtkmetaio-9.0
LIBS += -L./lib/ -lvtknetcdf-9.0
LIBS += -L./lib/ -lvtkogg-9.0
LIBS += -L./lib/ -lvtkParallelCore-9.0
LIBS += -L./lib/ -lvtkParallelDIY-9.0
LIBS += -L./lib/ -lvtkpng-9.0
LIBS += -L./lib/ -lvtkpugixml-9.0
LIBS += -L./lib/ -lvtkRenderingAnnotation-9.0
LIBS += -L./lib/ -lvtkRenderingContext2D-9.0
LIBS += -L./lib/ -lvtkRenderingContextOpenGL2-9.0
LIBS += -L./lib/ -lvtkRenderingCore-9.0
LIBS += -L./lib/ -lvtkRenderingFreeType-9.0
LIBS += -L./lib/ -lvtkRenderingGL2PSOpenGL2-9.0
LIBS += -L./lib/ -lvtkRenderingImage-9.0
LIBS += -L./lib/ -lvtkRenderingLabel-9.0
LIBS += -L./lib/ -lvtkRenderingLOD-9.0
LIBS += -L./lib/ -lvtkRenderingOpenGL2-9.0
LIBS += -L./lib/ -lvtkRenderingQt-9.0
LIBS += -L./lib/ -lvtkRenderingSceneGraph-9.0
LIBS += -L./lib/ -lvtkRenderingUI-9.0
LIBS += -L./lib/ -lvtkRenderingVolume-9.0
LIBS += -L./lib/ -lvtkRenderingVolumeOpenGL2-9.0
LIBS += -L./lib/ -lvtkRenderingVtkJS-9.0
LIBS += -L./lib/ -lvtksqlite-9.0
LIBS += -L./lib/ -lvtksys-9.0
LIBS += -L./lib/ -lvtkTestingRendering-9.0
LIBS += -L./lib/ -lvtktheora-9.0
LIBS += -L./lib/ -lvtktiff-9.0
LIBS += -L./lib/ -lvtkverdict-9.0
LIBS += -L./lib/ -lvtkViewsContext2D-9.0
LIBS += -L./lib/ -lvtkViewsCore-9.0
LIBS += -L./lib/ -lvtkViewsInfovis-9.0
LIBS += -L./lib/ -lvtkViewsQt-9.0
LIBS += -L./lib/ -lvtkWrappingTools-9.0
LIBS += -L./lib/ -lvtkzlib-9.0
LIBS += -L./lib/ -lvtkChartsCore-9.0
LIBS += -L./lib/ -lvtkCommonColor-9.0
LIBS += -L./lib/ -lvtkCommonComputationalGeometry-9.0
LIBS += -L./lib/ -lvtkCommonCore-9.0
LIBS += -L./lib/ -lvtkCommonDataModel-9.0
LIBS += -L./lib/ -lvtkCommonExecutionModel-9.0
LIBS += -L./lib/ -lvtkCommonMath-9.0
LIBS += -L./lib/ -lvtkCommonMisc-9.0
LIBS += -L./lib/ -lvtkCommonSystem-9.0
LIBS += -L./lib/ -lvtkCommonTransforms-9.0
LIBS += -L./lib/ -lvtkDICOM-9.0
