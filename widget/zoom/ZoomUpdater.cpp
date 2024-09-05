//
// Created by 2333 xiang on 2024/9/2.
//  放大镜图片更新器
//

#include "ZoomUpdater.h"
#include "../../tool/CaptureTool.h"

void ZoomUpdater::zoom() {
    while (run) {
        usleep(1000000 / 30);//30fps
        //执行截图并绘图
        auto srcImage = CaptureTool::captureRect(zoomRegion);
        if (scaleRate != 1) {
            //线性放大
            CaptureTool::scaleImageSizeByCenter(srcImage, scaleRate, false);
            //非线性平滑放大
            //CaptureTool::scaleImageSizeByCenter(srcImage, scaleRate, true);

        }
        //发送绘制信号
        emit callRender(srcImage);
    }
}

void ZoomUpdater::stop() {
    run = false;
}

