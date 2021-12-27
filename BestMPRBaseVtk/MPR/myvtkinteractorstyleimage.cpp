#include "myvtkinteractorstyleimage.h"
#include <QtDebug>
#include <bppmprwidget.h>


vtkStandardNewMacro(myVtkInteractorStyleImage);                             //标准类生成宏
/**
 * @brief myVtkInteractorStyleImage::SetImageViewer
 * @param imageViewer
 * 设置图像接口
 */
void myVtkInteractorStyleImage::SetImageViewer(ImagePipeLine *imageViewer)
{
    this->ImageViewer = imageViewer;
    this->MinSlice = imageViewer->getSliceMin();
    this->MaxSlice = imageViewer->getSliceMax();
    this->Slice = (this->MinSlice + this->MaxSlice) / 2;
    this->ImageViewer->setSlice(this->Slice);
    this->ImageViewer->render();
}

void myVtkInteractorStyleImage::SetBPPMPRWidget(BPPMPRWidget *temp)
{
    this->bppWidget = temp;
}
/**
 * @brief myVtkInteractorStyleImage::OnMouseWheelForward
 * 鼠标滚轮向前滚动
 */
void myVtkInteractorStyleImage::OnMouseWheelForward()
{

}
/**
 * @brief myVtkInteractorStyleImage::OnMouseWheelBackward
 * 鼠标滚轮向后滚动
 */
void myVtkInteractorStyleImage::OnMouseWheelBackward()
{

}
/**
 * @brief myVtkInteractorStyleImage::OnMiddleButtonDown
 * 鼠标中键按下
 */
void myVtkInteractorStyleImage::OnMiddleButtonDown()
{
    int x = this->Interactor->GetEventPosition()[0];
    int y = this->Interactor->GetEventPosition()[1];

    this->FindPokedRenderer(x, y);
    if (this->CurrentRenderer == nullptr)
    {
        return;
    }
    //        this->GrabFocus(this->EventCallbackCommand);
    if (!this->Interactor->GetShiftKey() && !this->Interactor->GetControlKey())
    {
        this->WindowLevelStartPosition[0] = x;
        this->WindowLevelStartPosition[1] = y;
        this->StartWindowLevel();
    }


}
/**
 * @brief myVtkInteractorStyleImage::OnMiddleButtonUp
 * 鼠标中键抬起
 */
void myVtkInteractorStyleImage::OnMiddleButtonUp()
{
    switch (this->State)
    {
    case VTKIS_WINDOW_LEVEL:
    {
        this->EndWindowLevel();
        if (this->Interactor)
        {
            this->ReleaseFocus();
        }
        break;
    }
    case VTKIS_SLICE:
    {
        this->EndSlice();
        if (this->Interactor)
        {
            this->ReleaseFocus();
        }
        break;
    }
    }

    this->Superclass::OnMiddleButtonUp();
}
/**
 * @brief myVtkInteractorStyleImage::OnLeftButtonDown
 * 鼠标左键按下
 */
void myVtkInteractorStyleImage::OnLeftButtonDown()
{
    this->FindPokedRenderer(
      this->Interactor->GetEventPosition()[0], this->Interactor->GetEventPosition()[1]);
    if (this->CurrentRenderer == nullptr)
    {
      return;
    }

    // If shift is held down, change the slice
    if ((this->InteractionMode == VTKIS_IMAGE3D || this->InteractionMode == VTKIS_IMAGE_SLICING) &&
      this->Interactor->GetShiftKey())
    {
      this->StartSlice();
    }

    this->Superclass::OnMiddleButtonDown();
}
/**
 * @brief myVtkInteractorStyleImage::OnLeftButtonUp
 * 鼠标左键抬起
 */
void myVtkInteractorStyleImage::OnLeftButtonUp()
{
    switch (this->State)
    {
    case VTKIS_WINDOW_LEVEL:
        this->EndWindowLevel();
        if (this->Interactor)
        {
            this->ReleaseFocus();
        }
        break;

    case VTKIS_SLICE:
        this->EndSlice();
        if (this->Interactor)
        {
            this->ReleaseFocus();
        }
        break;
    }

}
/**
 * @brief myVtkInteractorStyleImage::OnMouseMove
 * 鼠标移动
 */
void myVtkInteractorStyleImage::OnMouseMove()
{
    int x = this->Interactor->GetEventPosition()[0];
    int y = this->Interactor->GetEventPosition()[1];

    switch (this->State)
    {
      case VTKIS_WINDOW_LEVEL:
        this->FindPokedRenderer(x, y);
        this->WindowLevel();
        this->InvokeEvent(vtkCommand::InteractionEvent, nullptr);
        break;

      case VTKIS_PICK:
        this->FindPokedRenderer(x, y);
        this->Pick();
        this->InvokeEvent(vtkCommand::InteractionEvent, nullptr);
        break;

      case VTKIS_SLICE:
        this->FindPokedRenderer(x, y);
//        this->Slice();
        this->InvokeEvent(vtkCommand::InteractionEvent, nullptr);
        break;
    }


    bppWidget->emitPositionSignal(this->Interactor->GetEventPosition());
}
/**
 * @brief myVtkInteractorStyleImage::OnRightButtonDown
 * 鼠标右键按下
 */
void myVtkInteractorStyleImage::OnRightButtonDown()
{

}
/**
 * @brief myVtkInteractorStyleImage::OnRightButtonUp
 * 鼠标右键抬起
 */
void myVtkInteractorStyleImage::OnRightButtonUp()
{

}

