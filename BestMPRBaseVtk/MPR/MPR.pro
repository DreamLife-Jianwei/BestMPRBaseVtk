QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    bppmprwidget.cpp \
    imagepipeline.cpp \
    main.cpp \
    mainwindow.cpp \
    myimagereslicewindow.cpp

HEADERS += \
    bppmprwidget.h \
    imagepipeline.h \
    mainwindow.h \
    myimagereslicewindow.h

FORMS += \
    mainwindow.ui \
    myimagereslicewindow.ui


INCLUDEPATH += ./include/vtk-9.0


RESOURCES += \
    resources.qrc



CONFIG += debug_and_release
CONFIG(debug,debug|release) {

LIBS += -L./lib/debug/ -lvtkChartsCore-9.0d
LIBS += -L./lib/debug/ -lvtkCommonColor-9.0d
LIBS += -L./lib/debug/ -lvtkCommonComputationalGeometry-9.0d
LIBS += -L./lib/debug/ -lvtkCommonCore-9.0d
LIBS += -L./lib/debug/ -lvtkCommonDataModel-9.0d
LIBS += -L./lib/debug/ -lvtkCommonExecutionModel-9.0d
LIBS += -L./lib/debug/ -lvtkCommonMath-9.0d
LIBS += -L./lib/debug/ -lvtkCommonMisc-9.0d
LIBS += -L./lib/debug/ -lvtkCommonSystem-9.0d
LIBS += -L./lib/debug/ -lvtkCommonTransforms-9.0d
LIBS += -L./lib/debug/ -lvtkDICOM-9.0d
LIBS += -L./lib/debug/ -lvtkDICOMParser-9.0d
LIBS += -L./lib/debug/ -lvtkDomainsChemistry-9.0d
LIBS += -L./lib/debug/ -lvtkDomainsChemistryOpenGL2-9.0d
LIBS += -L./lib/debug/ -lvtkdoubleconversion-9.0d
LIBS += -L./lib/debug/ -lvtkexodusII-9.0d
LIBS += -L./lib/debug/ -lvtkexpat-9.0d
LIBS += -L./lib/debug/ -lvtkFiltersAMR-9.0d
LIBS += -L./lib/debug/ -lvtkFiltersCore-9.0d
LIBS += -L./lib/debug/ -lvtkFiltersExtraction-9.0d
LIBS += -L./lib/debug/ -lvtkFiltersFlowPaths-9.0d
LIBS += -L./lib/debug/ -lvtkFiltersGeneral-9.0d
LIBS += -L./lib/debug/ -lvtkFiltersGeneric-9.0d
LIBS += -L./lib/debug/ -lvtkFiltersGeometry-9.0d
LIBS += -L./lib/debug/ -lvtkFiltersHybrid-9.0d
LIBS += -L./lib/debug/ -lvtkFiltersHyperTree-9.0d
LIBS += -L./lib/debug/ -lvtkFiltersImaging-9.0d
LIBS += -L./lib/debug/ -lvtkFiltersModeling-9.0d
LIBS += -L./lib/debug/ -lvtkFiltersParallel-9.0d
LIBS += -L./lib/debug/ -lvtkFiltersParallelImaging-9.0d
LIBS += -L./lib/debug/ -lvtkFiltersPoints-9.0d
LIBS += -L./lib/debug/ -lvtkFiltersProgrammable-9.0d
LIBS += -L./lib/debug/ -lvtkFiltersSelection-9.0d
LIBS += -L./lib/debug/ -lvtkFiltersSMP-9.0d
LIBS += -L./lib/debug/ -lvtkFiltersSources-9.0d
LIBS += -L./lib/debug/ -lvtkFiltersStatistics-9.0d
LIBS += -L./lib/debug/ -lvtkFiltersTexture-9.0d
LIBS += -L./lib/debug/ -lvtkFiltersTopology-9.0d
LIBS += -L./lib/debug/ -lvtkFiltersVerdict-9.0d
LIBS += -L./lib/debug/ -lvtkfreetype-9.0d
LIBS += -L./lib/debug/ -lvtkGeovisCore-9.0d
LIBS += -L./lib/debug/ -lvtkgl2ps-9.0d
LIBS += -L./lib/debug/ -lvtkglew-9.0d
LIBS += -L./lib/debug/ -lvtkGUISupportQt-9.0d
LIBS += -L./lib/debug/ -lvtkGUISupportQtSQL-9.0d
LIBS += -L./lib/debug/ -lvtkhdf5_hl-9.0d
LIBS += -L./lib/debug/ -lvtkhdf5-9.0d
LIBS += -L./lib/debug/ -lvtkImagingColor-9.0d
LIBS += -L./lib/debug/ -lvtkImagingCore-9.0d
LIBS += -L./lib/debug/ -lvtkImagingFourier-9.0d
LIBS += -L./lib/debug/ -lvtkImagingGeneral-9.0d
LIBS += -L./lib/debug/ -lvtkImagingHybrid-9.0d
LIBS += -L./lib/debug/ -lvtkImagingMath-9.0d
LIBS += -L./lib/debug/ -lvtkImagingMorphological-9.0d
LIBS += -L./lib/debug/ -lvtkImagingSources-9.0d
LIBS += -L./lib/debug/ -lvtkImagingStatistics-9.0d
LIBS += -L./lib/debug/ -lvtkImagingStencil-9.0d
LIBS += -L./lib/debug/ -lvtkInfovisCore-9.0d
LIBS += -L./lib/debug/ -lvtkInfovisLayout-9.0d
LIBS += -L./lib/debug/ -lvtkInteractionImage-9.0d
LIBS += -L./lib/debug/ -lvtkInteractionStyle-9.0d
LIBS += -L./lib/debug/ -lvtkInteractionWidgets-9.0d
LIBS += -L./lib/debug/ -lvtkIOAMR-9.0d
LIBS += -L./lib/debug/ -lvtkIOAsynchronous-9.0d
LIBS += -L./lib/debug/ -lvtkIOCityGML-9.0d
LIBS += -L./lib/debug/ -lvtkIOCore-9.0d
LIBS += -L./lib/debug/ -lvtkIOEnSight-9.0d
LIBS += -L./lib/debug/ -lvtkIOExodus-9.0d
LIBS += -L./lib/debug/ -lvtkIOExport-9.0d
LIBS += -L./lib/debug/ -lvtkIOExportGL2PS-9.0d
LIBS += -L./lib/debug/ -lvtkIOExportPDF-9.0d
LIBS += -L./lib/debug/ -lvtkIOGeometry-9.0d
LIBS += -L./lib/debug/ -lvtkIOImage-9.0d
LIBS += -L./lib/debug/ -lvtkIOImport-9.0d
LIBS += -L./lib/debug/ -lvtkIOInfovis-9.0d
LIBS += -L./lib/debug/ -lvtkIOLegacy-9.0d
LIBS += -L./lib/debug/ -lvtkIOLSDyna-9.0d
LIBS += -L./lib/debug/ -lvtkIOMINC-9.0d
LIBS += -L./lib/debug/ -lvtkIOMotionFX-9.0d
LIBS += -L./lib/debug/ -lvtkIOMovie-9.0d
LIBS += -L./lib/debug/ -lvtkIONetCDF-9.0d
LIBS += -L./lib/debug/ -lvtkIOOggTheora-9.0d
LIBS += -L./lib/debug/ -lvtkIOParallel-9.0d
LIBS += -L./lib/debug/ -lvtkIOParallelXML-9.0d
LIBS += -L./lib/debug/ -lvtkIOPLY-9.0d
LIBS += -L./lib/debug/ -lvtkIOSegY-9.0d
LIBS += -L./lib/debug/ -lvtkIOSQL-9.0d
LIBS += -L./lib/debug/ -lvtkIOTecplotTable-9.0d
LIBS += -L./lib/debug/ -lvtkIOVeraOut-9.0d
LIBS += -L./lib/debug/ -lvtkIOVideo-9.0d
LIBS += -L./lib/debug/ -lvtkIOXML-9.0d
LIBS += -L./lib/debug/ -lvtkIOXMLParser-9.0d
LIBS += -L./lib/debug/ -lvtkjpeg-9.0d
LIBS += -L./lib/debug/ -lvtkjsoncpp-9.0d
LIBS += -L./lib/debug/ -lvtklibharu-9.0d
LIBS += -L./lib/debug/ -lvtklibproj-9.0d
LIBS += -L./lib/debug/ -lvtklibxml2-9.0d
LIBS += -L./lib/debug/ -lvtkloguru-9.0d
LIBS += -L./lib/debug/ -lvtklz4-9.0d
LIBS += -L./lib/debug/ -lvtklzma-9.0d
LIBS += -L./lib/debug/ -lvtkmetaio-9.0d
LIBS += -L./lib/debug/ -lvtknetcdf-9.0d
LIBS += -L./lib/debug/ -lvtkogg-9.0d
LIBS += -L./lib/debug/ -lvtkParallelCore-9.0d
LIBS += -L./lib/debug/ -lvtkParallelDIY-9.0d
LIBS += -L./lib/debug/ -lvtkpng-9.0d
LIBS += -L./lib/debug/ -lvtkpugixml-9.0d
LIBS += -L./lib/debug/ -lvtkRenderingAnnotation-9.0d
LIBS += -L./lib/debug/ -lvtkRenderingContext2D-9.0d
LIBS += -L./lib/debug/ -lvtkRenderingContextOpenGL2-9.0d
LIBS += -L./lib/debug/ -lvtkRenderingCore-9.0d
LIBS += -L./lib/debug/ -lvtkRenderingFreeType-9.0d
LIBS += -L./lib/debug/ -lvtkRenderingGL2PSOpenGL2-9.0d
LIBS += -L./lib/debug/ -lvtkRenderingImage-9.0d
LIBS += -L./lib/debug/ -lvtkRenderingLabel-9.0d
LIBS += -L./lib/debug/ -lvtkRenderingLOD-9.0d
LIBS += -L./lib/debug/ -lvtkRenderingOpenGL2-9.0d
LIBS += -L./lib/debug/ -lvtkRenderingQt-9.0d
LIBS += -L./lib/debug/ -lvtkRenderingSceneGraph-9.0d
LIBS += -L./lib/debug/ -lvtkRenderingUI-9.0d
LIBS += -L./lib/debug/ -lvtkRenderingVolume-9.0d
LIBS += -L./lib/debug/ -lvtkRenderingVolumeOpenGL2-9.0d
LIBS += -L./lib/debug/ -lvtkRenderingVtkJS-9.0d
LIBS += -L./lib/debug/ -lvtksqlite-9.0d
LIBS += -L./lib/debug/ -lvtksys-9.0d
LIBS += -L./lib/debug/ -lvtkTestingRendering-9.0d
LIBS += -L./lib/debug/ -lvtktheora-9.0d
LIBS += -L./lib/debug/ -lvtktiff-9.0d
LIBS += -L./lib/debug/ -lvtkverdict-9.0d
LIBS += -L./lib/debug/ -lvtkViewsContext2D-9.0d
LIBS += -L./lib/debug/ -lvtkViewsCore-9.0d
LIBS += -L./lib/debug/ -lvtkViewsInfovis-9.0d
LIBS += -L./lib/debug/ -lvtkViewsQt-9.0d
LIBS += -L./lib/debug/ -lvtkWrappingTools-9.0d
LIBS += -L./lib/debug/ -lvtkzlib-9.0d


}else{
LIBS += -L./lib/release/ -lvtkDICOMParser-9.0
LIBS += -L./lib/release/ -lvtkDomainsChemistry-9.0
LIBS += -L./lib/release/ -lvtkDomainsChemistryOpenGL2-9.0
LIBS += -L./lib/release/ -lvtkdoubleconversion-9.0
LIBS += -L./lib/release/ -lvtkexodusII-9.0
LIBS += -L./lib/release/ -lvtkexpat-9.0
LIBS += -L./lib/release/ -lvtkFiltersAMR-9.0
LIBS += -L./lib/release/ -lvtkFiltersCore-9.0
LIBS += -L./lib/release/ -lvtkFiltersExtraction-9.0
LIBS += -L./lib/release/ -lvtkFiltersFlowPaths-9.0
LIBS += -L./lib/release/ -lvtkFiltersGeneral-9.0
LIBS += -L./lib/release/ -lvtkFiltersGeneric-9.0
LIBS += -L./lib/release/ -lvtkFiltersGeometry-9.0
LIBS += -L./lib/release/ -lvtkFiltersHybrid-9.0
LIBS += -L./lib/release/ -lvtkFiltersHyperTree-9.0
LIBS += -L./lib/release/ -lvtkFiltersImaging-9.0
LIBS += -L./lib/release/ -lvtkFiltersModeling-9.0
LIBS += -L./lib/release/ -lvtkFiltersParallel-9.0
LIBS += -L./lib/release/ -lvtkFiltersParallelImaging-9.0
LIBS += -L./lib/release/ -lvtkFiltersPoints-9.0
LIBS += -L./lib/release/ -lvtkFiltersProgrammable-9.0
LIBS += -L./lib/release/ -lvtkFiltersSelection-9.0
LIBS += -L./lib/release/ -lvtkFiltersSMP-9.0
LIBS += -L./lib/release/ -lvtkFiltersSources-9.0
LIBS += -L./lib/release/ -lvtkFiltersStatistics-9.0
LIBS += -L./lib/release/ -lvtkFiltersTexture-9.0
LIBS += -L./lib/release/ -lvtkFiltersTopology-9.0
LIBS += -L./lib/release/ -lvtkFiltersVerdict-9.0
LIBS += -L./lib/release/ -lvtkfreetype-9.0
LIBS += -L./lib/release/ -lvtkGeovisCore-9.0
LIBS += -L./lib/release/ -lvtkgl2ps-9.0
LIBS += -L./lib/release/ -lvtkglew-9.0
LIBS += -L./lib/release/ -lvtkGUISupportQt-9.0
LIBS += -L./lib/release/ -lvtkGUISupportQtSQL-9.0
LIBS += -L./lib/release/ -lvtkhdf5_hl-9.0
LIBS += -L./lib/release/ -lvtkhdf5-9.0
LIBS += -L./lib/release/ -lvtkImagingColor-9.0
LIBS += -L./lib/release/ -lvtkImagingCore-9.0
LIBS += -L./lib/release/ -lvtkImagingFourier-9.0
LIBS += -L./lib/release/ -lvtkImagingGeneral-9.0
LIBS += -L./lib/release/ -lvtkImagingHybrid-9.0
LIBS += -L./lib/release/ -lvtkImagingMath-9.0
LIBS += -L./lib/release/ -lvtkImagingMorphological-9.0
LIBS += -L./lib/release/ -lvtkImagingSources-9.0
LIBS += -L./lib/release/ -lvtkImagingStatistics-9.0
LIBS += -L./lib/release/ -lvtkImagingStencil-9.0
LIBS += -L./lib/release/ -lvtkInfovisCore-9.0
LIBS += -L./lib/release/ -lvtkInfovisLayout-9.0
LIBS += -L./lib/release/ -lvtkInteractionImage-9.0
LIBS += -L./lib/release/ -lvtkInteractionStyle-9.0
LIBS += -L./lib/release/ -lvtkInteractionWidgets-9.0
LIBS += -L./lib/release/ -lvtkIOAMR-9.0
LIBS += -L./lib/release/ -lvtkIOAsynchronous-9.0
LIBS += -L./lib/release/ -lvtkIOCityGML-9.0
LIBS += -L./lib/release/ -lvtkIOCore-9.0
LIBS += -L./lib/release/ -lvtkIOEnSight-9.0
LIBS += -L./lib/release/ -lvtkIOExodus-9.0
LIBS += -L./lib/release/ -lvtkIOExport-9.0
LIBS += -L./lib/release/ -lvtkIOExportGL2PS-9.0
LIBS += -L./lib/release/ -lvtkIOExportPDF-9.0
LIBS += -L./lib/release/ -lvtkIOGeometry-9.0
LIBS += -L./lib/release/ -lvtkIOImage-9.0
LIBS += -L./lib/release/ -lvtkIOImport-9.0
LIBS += -L./lib/release/ -lvtkIOInfovis-9.0
LIBS += -L./lib/release/ -lvtkIOLegacy-9.0
LIBS += -L./lib/release/ -lvtkIOLSDyna-9.0
LIBS += -L./lib/release/ -lvtkIOMINC-9.0
LIBS += -L./lib/release/ -lvtkIOMotionFX-9.0
LIBS += -L./lib/release/ -lvtkIOMovie-9.0
LIBS += -L./lib/release/ -lvtkIONetCDF-9.0
LIBS += -L./lib/release/ -lvtkIOOggTheora-9.0
LIBS += -L./lib/release/ -lvtkIOParallel-9.0
LIBS += -L./lib/release/ -lvtkIOParallelXML-9.0
LIBS += -L./lib/release/ -lvtkIOPLY-9.0
LIBS += -L./lib/release/ -lvtkIOSegY-9.0
LIBS += -L./lib/release/ -lvtkIOSQL-9.0
LIBS += -L./lib/release/ -lvtkIOTecplotTable-9.0
LIBS += -L./lib/release/ -lvtkIOVeraOut-9.0
LIBS += -L./lib/release/ -lvtkIOVideo-9.0
LIBS += -L./lib/release/ -lvtkIOXML-9.0
LIBS += -L./lib/release/ -lvtkIOXMLParser-9.0
LIBS += -L./lib/release/ -lvtkjpeg-9.0
LIBS += -L./lib/release/ -lvtkjsoncpp-9.0
LIBS += -L./lib/release/ -lvtklibharu-9.0
LIBS += -L./lib/release/ -lvtklibproj-9.0
LIBS += -L./lib/release/ -lvtklibxml2-9.0
LIBS += -L./lib/release/ -lvtkloguru-9.0
LIBS += -L./lib/release/ -lvtklz4-9.0
LIBS += -L./lib/release/ -lvtklzma-9.0
LIBS += -L./lib/release/ -lvtkmetaio-9.0
LIBS += -L./lib/release/ -lvtknetcdf-9.0
LIBS += -L./lib/release/ -lvtkogg-9.0
LIBS += -L./lib/release/ -lvtkParallelCore-9.0
LIBS += -L./lib/release/ -lvtkParallelDIY-9.0
LIBS += -L./lib/release/ -lvtkpng-9.0
LIBS += -L./lib/release/ -lvtkpugixml-9.0
LIBS += -L./lib/release/ -lvtkRenderingAnnotation-9.0
LIBS += -L./lib/release/ -lvtkRenderingContext2D-9.0
LIBS += -L./lib/release/ -lvtkRenderingContextOpenGL2-9.0
LIBS += -L./lib/release/ -lvtkRenderingCore-9.0
LIBS += -L./lib/release/ -lvtkRenderingFreeType-9.0
LIBS += -L./lib/release/ -lvtkRenderingGL2PSOpenGL2-9.0
LIBS += -L./lib/release/ -lvtkRenderingImage-9.0
LIBS += -L./lib/release/ -lvtkRenderingLabel-9.0
LIBS += -L./lib/release/ -lvtkRenderingLOD-9.0
LIBS += -L./lib/release/ -lvtkRenderingOpenGL2-9.0
LIBS += -L./lib/release/ -lvtkRenderingQt-9.0
LIBS += -L./lib/release/ -lvtkRenderingSceneGraph-9.0
LIBS += -L./lib/release/ -lvtkRenderingUI-9.0
LIBS += -L./lib/release/ -lvtkRenderingVolume-9.0
LIBS += -L./lib/release/ -lvtkRenderingVolumeOpenGL2-9.0
LIBS += -L./lib/release/ -lvtkRenderingVtkJS-9.0
LIBS += -L./lib/release/ -lvtksqlite-9.0
LIBS += -L./lib/release/ -lvtksys-9.0
LIBS += -L./lib/release/ -lvtkTestingRendering-9.0
LIBS += -L./lib/release/ -lvtktheora-9.0
LIBS += -L./lib/release/ -lvtktiff-9.0
LIBS += -L./lib/release/ -lvtkverdict-9.0
LIBS += -L./lib/release/ -lvtkViewsContext2D-9.0
LIBS += -L./lib/release/ -lvtkViewsCore-9.0
LIBS += -L./lib/release/ -lvtkViewsInfovis-9.0
LIBS += -L./lib/release/ -lvtkViewsQt-9.0
LIBS += -L./lib/release/ -lvtkWrappingTools-9.0
LIBS += -L./lib/release/ -lvtkzlib-9.0
LIBS += -L./lib/release/ -lvtkChartsCore-9.0
LIBS += -L./lib/release/ -lvtkCommonColor-9.0
LIBS += -L./lib/release/ -lvtkCommonComputationalGeometry-9.0
LIBS += -L./lib/release/ -lvtkCommonCore-9.0
LIBS += -L./lib/release/ -lvtkCommonDataModel-9.0
LIBS += -L./lib/release/ -lvtkCommonExecutionModel-9.0
LIBS += -L./lib/release/ -lvtkCommonMath-9.0
LIBS += -L./lib/release/ -lvtkCommonMisc-9.0
LIBS += -L./lib/release/ -lvtkCommonSystem-9.0
LIBS += -L./lib/release/ -lvtkCommonTransforms-9.0
LIBS += -L./lib/release/ -lvtkDICOM-9.0
}
