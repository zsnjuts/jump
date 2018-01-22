# 微信跳一跳手动外挂

## 可执行文件使用

从[微信跳一跳手动外挂](http://65.49.202.67/jump.zip)下载zip压缩包，解压后点击压缩包中的jump.exe即可运行。

**注意**：运行之前需要先把手机连到电脑上，开启开发者选项和USB调试。小米手机需要允许通过USB模拟点击

## 依赖环境

* Android手机（连接电脑，开启开发者选项，开启USB调试，允许通过USB调试模拟点击）
* Windows需要安装adb(可执行文件中已经有了,不需要额外安装)



## 数学原理

因为物体从远到近大小没有发生变化，所以认定投影方式为平行投影，那么视平面与实际水平面仅在一个方向上有夹角，经过MATLAB测量，估算两平面夹角的余弦值为0.5771，即：实际y偏移量为手机屏幕y偏移量的0.5771倍

根据测试，估计按压时间与跳跃距离的比值参数为cof，即每按压cof毫秒跳一个单位长度

不同手机cof值不一样，小米4的cof=3.4，华为mate7的cof=3.25



## 换算

* 实际x位移=屏幕x位移
* 实际y位移=屏幕y位移*0.5771
* 实际距离=sqrt(实际x位移的平方+实际y位移的平方)
* 按压时间=实际距离*cof


其中位移单位为像素，按压时间单位为毫秒


## 注意事项

* 跳一跳有干扰机制，跳的过程中会偶尔出现略微偏离参数的情况，这种情况一般持续3跳左右，之后参数会恢复正常。偏离的时候就根据偏离情况作适当调整