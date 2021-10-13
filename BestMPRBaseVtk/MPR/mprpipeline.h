#ifndef MPRPIPELINE_H
#define MPRPIPELINE_H

#include <QObject>



enum showType
{
    TRA,
    SAG,
    COR
};


class mprPipeline
{
public:

    showType showMode = showType::COR;          //显示模式

    /**
     * @brief render
     * 开始渲染
     */
    void render();
    /**
     * @brief addActor
     * 添加子控件
     */
    void addActor();
    /**
     * @brief removeActor
     * 删除子控件
     */
    void removeActor();
    /**
     * @brief removeAllActors
     * 删除所有控件
     */
    void removeAllActors();

    mprPipeline();
    ~mprPipeline();
};

#endif // MPRPIPELINE_H
