#include "myvtkinteractorstyleimage.h"
#include <QtDebug>



vtkStandardNewMacro(myVtkInteractorStyleImage);

void myVtkInteractorStyleImage::SetImageViewer(ImagePipeLine *imageViewer)
{
    this->ImageViewer = imageViewer;
    this->MinSlice = imageViewer->getSliceMin();
    this->MaxSlice = imageViewer->getSliceMax();
    this->Slice = (this->MinSlice + this->MaxSlice) / 2;
    this->ImageViewer->setSlice(this->Slice);
    this->ImageViewer->render();
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
        qDebug() << x;
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
    int x = this->Interactor->GetEventPosition()[0];
    int y = this->Interactor->GetEventPosition()[1];

    this->FindPokedRenderer(x, y);
    if (this->CurrentRenderer == nullptr)
    {
        return;
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

}
/**
 * @brief myVtkInteractorStyleImage::OnMouseMove
 * 鼠标移动
 */
//void myVtkInteractorStyleImage::OnMouseMove()
//{
//    int* pos = this->Interactor->GetEventPosition();
//}
