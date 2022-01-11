#ifndef MYVTKINTERACTORSTYLEIMAGE_H
#define MYVTKINTERACTORSTYLEIMAGE_H

#include "vtkInteractorStyleImage.h"
#include "vtkInteractorStyleTrackballCamera.h"
#include "vtkObjectFactory.h"
#include "vtkInteractorObserver.h"
#include "vtkRenderWindowInteractor.h"
#include "imagepipeline.h"
/**
 * @brief The myVtkInteractorStyleImage class
 * 用户鼠标交互类
 */
class BPPMPRWidget;
class vtkPropPicker;
class myVtkInteractorStyleImage : public vtkInteractorStyleImage
{
public:

    static myVtkInteractorStyleImage* New();

    vtkTypeMacro(myVtkInteractorStyleImage, vtkInteractorStyleImage);

    void SetImageViewer(ImagePipeLine* imageViewer);                        //设置流水线输入

    void SetBPPMPRWidget(BPPMPRWidget *temp);                               //设置主窗口

    void SetPicker(vtkPropPicker* picker);                                  //设置拾取器

    void SetRender(vtkRenderer* render);                                    //设置渲染器

protected:

    virtual void OnMouseWheelForward() override;                            //鼠标滚轮向前滚动

    virtual void OnMouseWheelBackward() override;                           //鼠标滚轮向后滚动

    virtual void OnMiddleButtonDown() override;                             //鼠标中键按下

    virtual void OnMiddleButtonUp() override;                               //鼠标中键抬起

    virtual void OnLeftButtonDown() override;                               //鼠标左键按下

    virtual void OnLeftButtonUp() override;                                 //鼠标左键抬起

    virtual void OnMouseMove() override;                                    //鼠标移动

    virtual void OnRightButtonDown() override;                              //鼠标右键按下

    virtual void OnRightButtonUp() override;                                //鼠标右键抬起



private:
    BPPMPRWidget* bppWidget = nullptr;                                      //主窗口
    ImagePipeLine* ImageViewer= nullptr;;                                   //流水线
    vtkPropPicker* Picker= nullptr;;
    vtkRenderer* Render = nullptr;
    vtkImageActor* Actor = nullptr;
    vtkImageData* Image = nullptr;
    vtkRenderer* renderer = nullptr;

    int WindowLevelStartPosition[2];
    int WindowLevelCurrentPosition[2];
    double WindowLevelInitial[2];
    vtkImageProperty* CurrentImageProperty;
    int CurrentImageNumber;

    int InteractionMode;
    double XViewRightVector[3];
    double XViewUpVector[3];
    double YViewRightVector[3];
    double YViewUpVector[3];
    double ZViewRightVector[3];
    double ZViewUpVector[3];




    /********************/

    double pos[3] = {0.0};
    double bounds[6] = {0.0};
    int axis;


};

#endif // MYVTKINTERACTORSTYLEIMAGE_H
