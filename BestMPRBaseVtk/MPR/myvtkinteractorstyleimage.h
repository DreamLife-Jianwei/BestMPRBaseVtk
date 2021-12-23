#ifndef MYVTKINTERACTORSTYLEIMAGE_H
#define MYVTKINTERACTORSTYLEIMAGE_H

#include "vtkInteractorStyleImage.h"
#include "vtkObjectFactory.h"

/**
 * @brief The myVtkInteractorStyleImage class
 * 用户鼠标交互类
 */
class myVtkInteractorStyleImage : public vtkInteractorStyleImage
{
public:
    static myVtkInteractorStyleImage* New();
    vtkTypeMacro(myVtkInteractorStyleImage, vtkInteractorStyleImage);
};

#endif // MYVTKINTERACTORSTYLEIMAGE_H
