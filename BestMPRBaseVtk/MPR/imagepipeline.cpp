#include "imagepipeline.h"

#include "vtkCamera.h"
#include "vtkCommand.h"
#include "vtkImageActor.h"
#include "vtkImageData.h"
#include "vtkImageMapToWindowLevelColors.h"
#include "vtkImageMapper3D.h"
#include "vtkInformation.h"
#include "vtkInteractorStyleImage.h"
#include "vtkObjectFactory.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h"
#include "vtkStreamingDemandDrivenPipeline.h"

#include <QtDebug>


/**
 * @brief The ImagePipeLineCallback class
 * 回调类
 * 这部分需要将来更具功能需要重写
 */
class ImagePipeLineCallback : public vtkCommand
{

public:
    static ImagePipeLineCallback* New()
    {
        return new ImagePipeLineCallback;
    }

    void Execute(vtkObject* caller,unsigned long event,void* vtkNotUsed(callData)) override
    {
        if(this->IV->getInput() == nullptr)
        {
            return;
        }

        if(event == vtkCommand::ResetWindowLevelEvent)
        {
            this->IV->getInputAlgorithm()->UpdateWholeExtent();
            double* range = this->IV->getInput()->GetScalarRange();
            this->IV->setColorWindow(range[1] - range[0]);
            this->IV->setColorLevel(0.5 * (range[1] + range[0]));
            this->IV->render();
            return;
        }

        if(event == vtkCommand::StartWindowLevelEvent)
        {
            this->InitialWindow = this->IV->getColorWindow();
            this->InitialLevel = this->IV->getColorLevel();
            return;
        }

        vtkInteractorStyleImage* isi = static_cast<vtkInteractorStyleImage*>(caller);

        const int* size = this->IV->getRenderWindow()->GetSize();

        double window = this->InitialWindow;
        double level = this->InitialLevel;

        double dx = 4.0 * (isi->GetWindowLevelCurrentPosition()[0] - isi->GetWindowLevelStartPosition()[0]) / size[0];
        double dy = 4.0 * (isi->GetWindowLevelStartPosition()[1] - isi->GetWindowLevelCurrentPosition()[1]) / size[1];

        if(fabs(window) > 0.01)
            dx = dx * window;
        else
            dx = dx * (window < 0 ? -0.01 : 0.01);

        if(fabs(level) > 0.01)
            dy = dy * level;
        else
            dy = dy * (level < 0 ? -0.01 : 0.01);

        if(window < 0.01)
            dx = -1 * dx;

        if(level < 0.01)
            dy = -1 * dy;

        double newWindow = dx + window;
        double newLevel = level -dy;

        if(fabs(newWindow) < 0.01)
            newWindow = 0.01 * (newWindow < 0 ? -1 :1);

        if(fabs(newLevel) < 0.01)
            newLevel = 0.01 * (newLevel < 0 ? -1 : 1);

        this->IV->setColorWindow(newWindow);
        this->IV->setColorLevel(newLevel);
        this->IV->render();
    }

    ImagePipeLine* IV;
    double InitialWindow;
    double InitialLevel;
};

//vtkStandardNewMacro(ImagePipeLine);
/**
 * @brief ImagePipeLine::New
 * @return
 * New 函数
 */
ImagePipeLine* ImagePipeLine::New()
{
    auto result = new ImagePipeLine;
    result->InitializeObjectBase();
    return result;
}

/**
 * @brief getWindowName
 * @return
 * 获取窗口名称
 */
const char *ImagePipeLine::getWindowName()
{
    return this->RenderWindow->GetWindowName();
}
/**
 * @brief Render
 * 开始渲染图像
 */
void ImagePipeLine::render()
{
    if(this->FirstRender)
    {
        vtkAlgorithm* input = this->getInputAlgorithm();
        if(input)
        {
            input->UpdateInformation();
            int* w_ext = this->getInputInformation()->Get(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT());
            int xs = 0,ys = 0;

            switch (this->SliceOrientation){
            case ImagePipeLine::SLICE_ORIENTATION_XY:
            default:
                xs = w_ext[1] - w_ext[0] + 1;
                ys = w_ext[3] - w_ext[2] +1;
                break;

            case ImagePipeLine::SLICE_ORIENTATION_XZ:
                xs = w_ext[1] - w_ext[0] + 1;
                ys = w_ext[5] - w_ext[4] +1;
                break;

            case ImagePipeLine::SLICE_ORIENTATION_YZ:
                xs = w_ext[3] - w_ext[2] + 1;
                ys = w_ext[5] - w_ext[4] +1;
                break;
            }
            /*
             * 如果图像尺寸小于150*100，那么强制把图像尺寸设置为150*100
             */
            if(this->RenderWindow->GetSize()[0] == 0)
            {
                this->RenderWindow->SetSize(xs < 150 ? 150 : xs, ys < 100 ? 100 : ys);
            }

            if(this->Renderer)
            {
                this->Renderer->ResetCamera();
                this->Renderer->GetActiveCamera()->SetParallelScale(xs < 150 ? 75 : (xs - 1) / 2.0);
            }
            this->FirstRender = 0;
        }
    }
    if(this->getInput())
    {
        this->RenderWindow->Render();
    }
}
/**
 * @brief getInput
 * @return
 * 获取输入数据
 */
vtkImageData *ImagePipeLine::getInput()
{
    return vtkImageData::SafeDownCast(this->WindowLevel->GetInput());
}
/**
 * @brief setInputData
 * @param in
 * 设置输入数据
 */
void ImagePipeLine::setInputData(vtkImageData *in)
{
    this->WindowLevel->SetInputData(in);
    this->updateDisplayExtent();
}
/**
 * @brief setInputConnection
 * @param input
 * 设置输入数据
 */
void ImagePipeLine::setInputConnection(vtkAlgorithmOutput *input)
{
    this->WindowLevel->SetInputConnection(input);
    this->updateDisplayExtent();
}

int ImagePipeLine::getSliceOrientation()
{
    return SliceOrientation;
}
/**
 * @brief ImagePipeLine::setSliceOrientation
 * @param orientation
 * 设置切片方向
 */
void ImagePipeLine::setSliceOrientation(int orientation)
{
    if(orientation < ImagePipeLine::SLICE_ORIENTATION_YZ || orientation > ImagePipeLine::SLICE_ORIENTATION_XY)
        return;

    if(this->SliceOrientation == orientation)
        return;

    this->SliceOrientation = orientation;

    int* range = this->getSliceRange();
    if(range)
        this->Slice = static_cast<int>((range[0] + range[1]) * 0.5);

    this->updateOrientation();
    this->updateDisplayExtent();

    if(this->Renderer && this->getInput())
    {
        double scale = this->Renderer->GetActiveCamera()->GetParallelScale();
        this->Renderer->ResetCamera();
        this->Renderer->GetActiveCamera()->SetParallelScale(scale);

    }
    this->render();
}
/**
 * @brief ImagePipeLine::setSliceOrientationToXY
 * 设置切片方向
 */
void ImagePipeLine::setSliceOrientationToXY()
{
    this->setSliceOrientation(ImagePipeLine::SLICE_ORIENTATION_XY);
}
/**
 * @brief ImagePipeLine::setSliceOrientationToYZ
 * 设置切片方向
 */
void ImagePipeLine::setSliceOrientationToYZ()
{
    this->setSliceOrientation(ImagePipeLine::SLICE_ORIENTATION_YZ);
}
/**
 * @brief ImagePipeLine::setSliceOrientationToXZ
 * 设置切片方向
 */
void ImagePipeLine::setSliceOrientationToXZ()
{
    this->setSliceOrientation(ImagePipeLine::SLICE_ORIENTATION_XZ);
}
/**
 * @brief ImagePipeLine::getSlice
 * @return
 * 获取图像序列
 */
int ImagePipeLine::getSlice()
{
    return this->Slice;
}
/**
 * @brief ImagePipeLine::setSlice
 * @param s
 * 设置图像序列
 */
void ImagePipeLine::setSlice(int s)
{
    int* range = this->getSliceRange();
    if(range)
    {
        if(s < range[0])
            s = range[0];
        else if(s > range[1])
            s = range[1];
    }

    if(this->Slice == s)
        return;

    this->Slice = s;
    this->Modified();
    this->updateDisplayExtent();
    this->render();
}

void ImagePipeLine::updateDisplayExtent()
{

    vtkAlgorithm* input = this->getInputAlgorithm();
    if(!input || !this->ImageActor)
        return;

    input->UpdateInformation();
    vtkInformation* outInfo = input->GetOutputInformation(0);
    int* w_ext = outInfo->Get(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT());
    /*
     * 判断切片是否在范围之内，如果不在，则修复
     */
    int slice_min = w_ext[this->SliceOrientation *2];
    int slice_max = w_ext[this->SliceOrientation *2 + 1];
    if(this->Slice < slice_min || this->Slice > slice_max)
        this->Slice = static_cast<int>((slice_min + slice_max) * 0.5);

    /*
     * 设置图像Actor
     */
    switch (this->SliceOrientation) {
    case ImagePipeLine::SLICE_ORIENTATION_XY:
        this->ImageActor->SetDisplayExtent(w_ext[0],w_ext[1],w_ext[2],w_ext[3],this->Slice,this->Slice);
        break;

    case ImagePipeLine::SLICE_ORIENTATION_XZ:
        this->ImageActor->SetDisplayExtent(w_ext[0],w_ext[1],this->Slice,this->Slice,w_ext[4],w_ext[5]);
        break;

    case ImagePipeLine::SLICE_ORIENTATION_YZ:
        this->ImageActor->SetDisplayExtent(this->Slice,this->Slice,w_ext[2],w_ext[3],w_ext[4],w_ext[5]);
        break;
    }

    /*
     * 找出正确的裁剪范围
     */
    if(this->Renderer)
    {
        if(this->InteractorStyle && this->InteractorStyle->GetAutoAdjustCameraClippingRange())
        {
            this->Renderer->ResetCameraClippingRange();
        }
        else
        {
            vtkCamera* cam = this->Renderer->GetActiveCamera();
            if(cam)
            {
                double bounds[6];
                this->ImageActor->GetBounds(bounds);
                double spos = bounds[this->SliceOrientation * 2];
                double cpos = cam->GetPosition()[this->SliceOrientation];
                double range = fabs(spos - cpos);
                double* spacing = outInfo->Get(vtkDataObject::SPACING());
                double avg_spacing = (spacing[0] + spacing[1] + spacing[2]) / 3.0;
                cam->SetClippingRange(range - avg_spacing * 3.0,range + avg_spacing * 3.0);
            }
        }
    }
}

int ImagePipeLine::getSliceMin()
{
    int* range = this->getSliceRange();
    if(range)
    {
        return range[0];
    }

    return 0;
}

int ImagePipeLine::getSliceMax()
{
    int* range = this->getSliceRange();
    if(range)
    {
        return range[1];
    }

    return 0;
}

void ImagePipeLine::getSliceRange(int range[])
{
    this->getSliceRange(range[0], range[1]);
}

void ImagePipeLine::getSliceRange(int &min, int &max)
{
    vtkAlgorithm* input = this->getInputAlgorithm();
    if(input)
    {
        input->UpdateInformation();
        int* w_ext = input->GetOutputInformation(0)->Get(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT());
        min = w_ext[this->SliceOrientation * 2];
        max = w_ext[this->SliceOrientation *  2 +1];
    }
}

int *ImagePipeLine::getSliceRange()
{
    vtkAlgorithm* input = this->getInputAlgorithm();
    if (input)
    {
        input->UpdateInformation();
        return input->GetOutputInformation(0)->Get(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT()) + this->SliceOrientation * 2;
    }
    return nullptr;
}

double ImagePipeLine::getColorWindow()
{
    return this->WindowLevel->GetWindow();
}

double ImagePipeLine::getColorLevel()
{
    return this->WindowLevel->GetLevel();
}

void ImagePipeLine::setColorWindow(double s)
{
    if(this->WindowLevel)
        WindowLevel->SetWindow(s);
}

void ImagePipeLine::setColorLevel(double s)
{
    if(this->WindowLevel)
        WindowLevel->SetLevel(s);
}

void ImagePipeLine::setDisplayId(void *a)
{
    this->RenderWindow->SetDisplayId(a);
}

void ImagePipeLine::setWindowId(void *a)
{
    this->RenderWindow->SetWindowId(a);
}

void ImagePipeLine::setParentId(void *a)
{
    this->RenderWindow->SetParentId(a);
}

int *ImagePipeLine::getPosition()
{
    return this->RenderWindow->GetPosition();
}

void ImagePipeLine::setPosition(int x, int y)
{
    this->RenderWindow->SetPosition(x,y);
}

void ImagePipeLine::setPosition(int a[])
{
    this->setPosition(a[0],a[1]);
}

int *ImagePipeLine::getSize()
{
    return this->RenderWindow->GetSize();
}

void ImagePipeLine::setSize(int width, int height)
{
    this->RenderWindow->SetSize(width,height);
}

void ImagePipeLine::setSize(int a[])
{
    this->setSize(a[0],a[1]);
}
/**
 * @brief ImagePipeLine::setRenderWindow
 * @param arg
 * 设置渲染窗口
 */
void ImagePipeLine::setRenderWindow(vtkRenderWindow *arg)
{
    if(this->RenderWindow == arg)
    {
        return;
    }

    this->unInstallPipeline();

    if(this->RenderWindow)
    {
        this->RenderWindow->UnRegister(this);
    }

    this->RenderWindow = arg;
    if(this->RenderWindow)
    {
        this->RenderWindow->Register(this);
    }

    this->installPipeline();
}
/**
 * @brief ImagePipeLine::setRenderer
 * @param arg
 * 设置渲染器
 */
void ImagePipeLine::setRenderer(vtkRenderer *arg)
{
    if(Renderer == arg)
    {
        return;
    }

    this->unInstallPipeline();

    if(this->Renderer)
    {
        Renderer->UnRegister(this);
    }

    Renderer = arg;

    if(this->Renderer)
    {
        this->Renderer->Register(this);
    }

    this->installPipeline();
    this->updateOrientation();

}
/**
 * @brief getRenderWindow
 * @return
 * 获取渲染窗口
 */
vtkRenderWindow *ImagePipeLine::getRenderWindow()
{
    return this->RenderWindow;
}

vtkRenderer *ImagePipeLine::getRenderer()
{
    return this->Renderer;
}

vtkImageActor *ImagePipeLine::getImageActor()
{
    return this->ImageActor;
}

vtkImageMapToWindowLevelColors *ImagePipeLine::getWindowLevel()
{
    return this->WindowLevel;
}

vtkInteractorStyleImage *ImagePipeLine::getInteratorStyle()
{
    return this->InteractorStyle;
}

void ImagePipeLine::setupInteractor(vtkRenderWindowInteractor *arg)
{
    if(this->Interactor == arg)
        return;

    this->unInstallPipeline();

    if(this->Interactor)
        this->Interactor->UnRegister(this);

    this->Interactor = arg;
    if(this->Interactor)
        this->Interactor->Register(this);

    this->installPipeline();

    if(this->Renderer)
        this->Renderer->GetActiveCamera()->ParallelProjectionOn();
}

void ImagePipeLine::setOffScreenRendering(vtkTypeBool i)
{
    this->RenderWindow->SetOffScreenRendering(i);
}

vtkTypeBool ImagePipeLine::getOffScreenRendering()
{
    return this->RenderWindow->GetOffScreenRendering();
}

void ImagePipeLine::offScreenRenderingOn()
{
    this->setOffScreenRendering(static_cast<vtkTypeBool>(1));
}

void ImagePipeLine::offScreenRenderingOff()
{
    this->setOffScreenRendering(static_cast<vtkTypeBool>(0));
}
/**
 * @brief ImagePipeLine::ImagePipeLine
 * 构造函数
 */
ImagePipeLine::ImagePipeLine()
{
    this->RenderWindow = nullptr;
    this->Renderer = nullptr;
    this->ImageActor = vtkImageActor::New();
    this->WindowLevel = vtkImageMapToWindowLevelColors::New();
    this->Interactor = nullptr;
    this->InteractorStyle = nullptr;

    this->Slice = 0;
    this->FirstRender = 1;
    this->SliceOrientation = ImagePipeLine::SLICE_ORIENTATION_XY;

    /*
     * 设置流水线
     */

    vtkRenderWindow* renwin = vtkRenderWindow::New();
    this->setRenderWindow(renwin);
    renwin->Delete();

    vtkRenderer* ren = vtkRenderer::New();
    this->setRenderer(ren);
    ren->Delete();

    this->installPipeline();
}
/**
 * @brief ImagePipeLine::~ImagePipeLine
 * 析构函数
 */
ImagePipeLine::~ImagePipeLine()
{
    if(this->WindowLevel)
    {
        this->WindowLevel->Delete();
        this->WindowLevel = nullptr;
    }

    if(this->ImageActor)
    {
        this->ImageActor->Delete();
        this->ImageActor = nullptr;
    }

    if(this->Renderer)
    {
        this->Renderer->Delete();
        this->Renderer = nullptr;
    }

    if(this->RenderWindow)
    {
        this->RenderWindow->Delete();
        this->RenderWindow = nullptr;
    }

    if(this->Interactor)
    {
        this->Interactor->Delete();
        this->Interactor = nullptr;
    }

    if(this->InteractorStyle)
    {
        this->InteractorStyle->Delete();
        this->InteractorStyle = nullptr;
    }
}
/**
 * @brief ImagePipeLine::updateOrientation
 * 设置相机位置
 */
void ImagePipeLine::updateOrientation()
{
    vtkCamera* cam = this->Renderer ? this->Renderer->GetActiveCamera() : nullptr;
    if(cam)
    {
        switch (this->SliceOrientation) {
        case ImagePipeLine::SLICE_ORIENTATION_XY:
            cam->SetFocalPoint(0,0,0);
            cam->SetPosition(0,0,1);
            cam->SetViewUp(0,1,0);
            break;
        case ImagePipeLine::SLICE_ORIENTATION_XZ:
            cam->SetFocalPoint(0,0,0);
            cam->SetPosition(0,-1,0);
            cam->SetViewUp(0,0,1);
            break;
        case ImagePipeLine::SLICE_ORIENTATION_YZ:
            cam->SetFocalPoint(0,0,0);
            cam->SetPosition(1,0,0);
            cam->SetViewUp(0,0,1);
            break;
        }
    }
}

vtkAlgorithm *ImagePipeLine::getInputAlgorithm()
{
    return this->WindowLevel->GetInputAlgorithm();
}

vtkInformation *ImagePipeLine::getInputInformation()
{
    return this->WindowLevel->GetInputInformation();
}
/**
 * @brief installPipeline
 * 安装流水线
 */
void ImagePipeLine::installPipeline()
{
    if(this->RenderWindow && this->Renderer)
    {
        this->RenderWindow->AddRenderer(this->Renderer);
    }

    if(this->Interactor)
    {
        if(!this->InteractorStyle)
        {
            this->InteractorStyle = vtkInteractorStyleImage::New();
            ImagePipeLineCallback* cbk = ImagePipeLineCallback::New();
            cbk->IV = this;
            this->InteractorStyle->AddObserver(vtkCommand::WindowLevelEvent,cbk);
            this->InteractorStyle->AddObserver(vtkCommand::StartWindowLevelEvent,cbk);
            this->InteractorStyle->AddObserver(vtkCommand::ResetWindowLevelEvent,cbk);
            cbk->Delete();
        }

        this->Interactor->SetInteractorStyle(this->InteractorStyle);
        this->Interactor->SetRenderWindow(this->RenderWindow);
    }

    if(this->Renderer && this->ImageActor)
        this->Renderer->AddViewProp(this->ImageActor);

    if(this->ImageActor && this->WindowLevel)
        this->ImageActor->GetMapper()->SetInputConnection(this->WindowLevel->GetOutputPort());
}
/**
 * @brief unInstallPipeline
 * 卸载流水线
 */
void ImagePipeLine::unInstallPipeline()
{
    if(this->ImageActor)
        this->ImageActor->GetMapper()->SetInputConnection(nullptr);

    if(this->Renderer && this->ImageActor)
        this->Renderer->RemoveViewProp(this->ImageActor);

    if(this->RenderWindow && this->Renderer)
        this->RenderWindow->RemoveRenderer(this->Renderer);

    if(this->Interactor)
    {
        this->Interactor->SetInteractorStyle(nullptr);
        this->Interactor->SetRenderWindow(nullptr);
    }
}


