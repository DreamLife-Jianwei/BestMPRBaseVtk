<img src="https://img-blog.csdnimg.cn/dbf523d39a0a4b7ea420b98d4802981b.png#pic_center" alt="头图" style="zoom:40%;" />

​		是的，你没有看错，我膨胀了，我已经不满足于在Qt中使用那种控件提升为的方法了，现在我要把VTK的一些并能封装成一个控件。

> > 关于VTK的学习Demo，可以看看这里，我搬运了部分官方的实例到Qt中[Qt&VTK官网实例](https://blog.csdn.net/z609932088/category_11141734.html?spm=1001.2014.3001.5482)；剩下的我写了一个医学的四视图，不过也是一部分功能，可以看下这里[医学四视图](https://blog.csdn.net/z609932088/category_11276724.html?spm=1001.2014.3001.5482)

> 这个项目的就是把上面的那些功能封装到这个控件里面，还会增加一些功能。

---

>[TOC]

# 开发环境

操作系统：win10专业工作站版本

Qt版本：5.14.2  vs2017 64

creator版本：4.15.2 -> 5.0.2 -> 6.0.0

VTK版本：8.2 -> 9.0.3

# 子项目说明

## MPR项目

### 20211220：更新鼠标操作事件

使用Qt鼠标事件来切换Slice

![](https://raw.githubusercontent.com/DreamLife-Jianwei/CSDNResources/master/202112211026273.gif)

### 20211214：更新交互方式

![](https://raw.githubusercontent.com/DreamLife-Jianwei/CSDNResources/master/202112141436612.gif)

### 20211213：增加了3D体渲染

![](https://raw.githubusercontent.com/DreamLife-Jianwei/CSDNResources/master/202112141008290.gif)

### 更新

![](https://raw.githubusercontent.com/DreamLife-Jianwei/CSDNResources/master/202112131349908.gif)



### 初始化项目

功能测试项目，目前已搬运官方代码，效果如下：

![gif6](https://raw.githubusercontent.com/DreamLife-Jianwei/CSDNResources/master/20211104162012.gif)









---

<img src="https://img-blog.csdnimg.cn/e931244fe9284d62854df336584f2ed6.png#pic_center" alt="博客签名2021"  />
