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
}

void myVtkInteractorStyleImage::SetBPPMPRWidget(BPPMPRWidget *temp)
{
    this->bppWidget = temp;
}
/**
 * @brief myVtkInteractorStyleImage::OnMouseWheelForward
 * 鼠标滚轮向前滚动
 * 切换图层显示
 */
void myVtkInteractorStyleImage::OnMouseWheelForward()
{
    int maxSlice = this->ImageViewer->getSliceMax();
    int currentSlice = this->ImageViewer->getSlice();
    if(currentSlice < maxSlice)
    {
        currentSlice += 1;
        this->ImageViewer->setSlice(currentSlice);
        this->ImageViewer->render();
        bppWidget->emitSliceChangedSignal(currentSlice);            //将切片改变后信息外传
    }
}
/**
 * @brief myVtkInteractorStyleImage::OnMouseWheelBackward
 * 鼠标滚轮向后滚动
 * 切换图层显示
 */
void myVtkInteractorStyleImage::OnMouseWheelBackward()
{
    int minSlice = this->ImageViewer->getSliceMin();
    int currentSlice = this->ImageViewer->getSlice();
    if(currentSlice > minSlice)
    {
        currentSlice -= 1;
        this->ImageViewer->setSlice(currentSlice);
        this->ImageViewer->render();
        bppWidget->emitSliceChangedSignal(currentSlice);            //将切片改变后信息外传
    }
}
/**
 * @brief myVtkInteractorStyleImage::OnMiddleButtonDown
 * 鼠标中键按下
 */
void myVtkInteractorStyleImage::OnMiddleButtonDown()
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

    // The rest of the button + key combinations remain the same

    else
    {
      this->Superclass::OnMiddleButtonDown();
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
       case VTKIS_SLICE:
         this->EndSlice();
         if (this->Interactor)
         {
           this->ReleaseFocus();
         }
         break;
     }


     this->Superclass::OnMiddleButtonUp();
}
/**
 * @brief myVtkInteractorStyleImage::OnLeftButtonDown
 * 鼠标左键按下
 */
void myVtkInteractorStyleImage::OnLeftButtonDown()
{
    int x = this->Interactor->GetEventPosition()[0];
     int y = this->Interactor->GetEventPosition()[1];

     this->FindPokedRenderer(x, y);
     if (this->CurrentRenderer == nullptr)
     {
       return;
     }

     // Redefine this button to handle window/level
//     this->GrabFocus(this->EventCallbackCommand);
     if (!this->Interactor->GetShiftKey() && !this->Interactor->GetControlKey())
     {
       this->WindowLevelStartPosition[0] = x;
       this->WindowLevelStartPosition[1] = y;
       this->StartWindowLevel();
     }

     // If shift is held down, do a rotation
     else if (this->InteractionMode == VTKIS_IMAGE3D && this->Interactor->GetShiftKey())
     {
       this->StartRotate();
     }

     // If ctrl is held down in slicing mode, slice the image
     else if (this->InteractionMode == VTKIS_IMAGE_SLICING && this->Interactor->GetControlKey())
     {
       this->StartSlice();
     }

     // The rest of the button + key combinations remain the same

     else
     {
       this->Superclass::OnLeftButtonDown();
     }
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

      this->Superclass::OnLeftButtonUp();
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
        this->Slice();
        this->InvokeEvent(vtkCommand::InteractionEvent, nullptr);
        break;
    }

    bppWidget->emitPositionChangedSignal(this->Interactor->GetEventPosition());
    this->Superclass::OnMouseMove();
}
/**
 * @brief myVtkInteractorStyleImage::OnRightButtonDown
 * 鼠标右键按下
 */
void myVtkInteractorStyleImage::OnRightButtonDown()
{
    int x = this->Interactor->GetEventPosition()[0];
    int y = this->Interactor->GetEventPosition()[1];

    this->FindPokedRenderer(x, y);
    if (this->CurrentRenderer == nullptr)
    {
      return;
    }

    // Redefine this button + shift to handle pick
//    this->GrabFocus(this->EventCallbackCommand);
    if (this->Interactor->GetShiftKey())
    {
      this->StartPick();
    }

    else if (this->InteractionMode == VTKIS_IMAGE3D && this->Interactor->GetControlKey())
    {
      this->StartSlice();
    }
    else if (this->InteractionMode == VTKIS_IMAGE_SLICING && this->Interactor->GetControlKey())
    {
      this->StartSpin();
    }

    // The rest of the button + key combinations remain the same

    else
    {
      this->Superclass::OnRightButtonDown();
    }
}
/**
 * @brief myVtkInteractorStyleImage::OnRightButtonUp
 * 鼠标右键抬起
 */
void myVtkInteractorStyleImage::OnRightButtonUp()
{
    switch (this->State)
     {
       case VTKIS_PICK:
         this->EndPick();
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

       case VTKIS_SPIN:
         if (this->Interactor)
         {
           this->EndSpin();
         }
         break;
     }

     // Call parent to handle all other states and perform additional work

     this->Superclass::OnRightButtonUp();
}

