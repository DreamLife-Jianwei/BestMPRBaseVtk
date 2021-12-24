#ifndef MYVTKINTERACTORSTYLEIMAGE_H
#define MYVTKINTERACTORSTYLEIMAGE_H

#include "vtkInteractorStyleImage.h"
#include "vtkObjectFactory.h"
#include "vtkInteractorObserver.h"
#include "vtkRenderWindowInteractor.h"
#include "imagepipeline.h"
/**
 * @brief The myVtkInteractorStyleImage class
 * 用户鼠标交互类
 */

class myVtkInteractorStyleImage : public vtkInteractorStyleImage
{
public:

    static myVtkInteractorStyleImage* New();

    vtkTypeMacro(myVtkInteractorStyleImage, vtkInteractorStyleImage);

    void SetImageViewer(ImagePipeLine* imageViewer);                        //设置流水线输入


protected:

    ImagePipeLine* ImageViewer;                                             //流水线
    int Slice;                                                              //当前Slice
    int MinSlice;                                                           //最小Slice范围
    int MaxSlice;                                                           //最大Slice范围


    virtual void OnMouseWheelForward() override;                            //鼠标滚轮向前滚动

    virtual void OnMouseWheelBackward() override;                           //鼠标滚轮向后滚动

    virtual void OnMiddleButtonDown() override;                             //鼠标中键按下

    virtual void OnMiddleButtonUp() override;                               //鼠标中键抬起

    virtual void OnLeftButtonDown() override;                               //鼠标左键按下

    virtual void OnLeftButtonUp() override;                                 //鼠标左键抬起

//    virtual void OnMouseMove() override;                                    //鼠标移动


};

#endif // MYVTKINTERACTORSTYLEIMAGE_H
