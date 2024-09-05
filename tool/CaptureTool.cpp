//
// Created by 2333 xiang on 2024/8/29.
//

#include <QScreen>
#include "CaptureTool.h"
#include "PublicReferences.h"
#include "iostream"
#include "cmath"
#include "string"


QImage CaptureTool::CGImageToQImage(CGImageRef cgImage) {
    if (!cgImage) {
        return QImage();  // 返回一个空的QImage
    }

    // 获取图像的宽度和高度
    size_t width = CGImageGetWidth(cgImage);
    size_t height = CGImageGetHeight(cgImage);

    // 获取位图信息
    size_t bitsPerComponent = CGImageGetBitsPerComponent(cgImage);
    size_t bitsPerPixel = CGImageGetBitsPerPixel(cgImage);
    size_t bytesPerRow = CGImageGetBytesPerRow(cgImage);

    // 获取颜色空间和位图数据
    CGColorSpaceRef colorSpace = CGImageGetColorSpace(cgImage);
    CGBitmapInfo bitmapInfo = CGImageGetBitmapInfo(cgImage);

    // 创建 CFDataRef
    CFDataRef dataRef = CGDataProviderCopyData(CGImageGetDataProvider(cgImage));
    const void *data = CFDataGetBytePtr(dataRef);

    // 根据颜色空间和位图信息判断像素格式
    QImage::Format format;
    if (bitsPerComponent == 8 && bitsPerPixel == 32) {
        format = QImage::Format_ARGB32;
    } else if (bitsPerComponent == 8 && bitsPerPixel == 24) {
        format = QImage::Format_RGB888;
    } else {
        // 添加更多格式处理，如有必要
        CFRelease(dataRef); // 在返回之前释放 CFDataRef
        return QImage();  // 目前不支持的格式
    }

    // 创建QImage并拷贝数据
    QImage image(reinterpret_cast<const uchar *>(data), width, height, bytesPerRow, format);

    // 深拷贝 QImage
    QImage result = image.copy();

    // 释放 CFDataRef
    CFRelease(dataRef);

    return result;
}


CGImageRef CaptureTool::getCaptureFromRect(int x, int y, int w, int h) {
    CGRect rect = CGRectMake(x, y, w, h);
    return getCaptureFromRect(rect);
}

CGImageRef CaptureTool::getCaptureFromRect(QRect &srcRect) {
    return getCaptureFromRect(srcRect.x(), srcRect.y(), srcRect.width(), srcRect.height());
}

CGImageRef CaptureTool::getCaptureFromPoint(int x, int y) {
    CGRect rect = CGRectMake(x, y, 1, 1);
    return getCaptureFromRect(rect);
}

CGImageRef CaptureTool::getCaptureFromPoint(QPoint &srcPoint) {
    return getCaptureFromPoint(srcPoint.x(), srcPoint.y());
}

CGImageRef CaptureTool::getCapture() {
    return getCaptureFromRect(pubRef::displayBounds);
}

CGImageRef CaptureTool::getCaptureFromRect(CGRect &rect) {
    // 获取主显示器的 ID
    CGDirectDisplayID displayID = CGMainDisplayID();
    // 捕获指定区域的屏幕图像
    CGImageRef image = CGDisplayCreateImageForRect(displayID, rect);
    return image;
}

QColor CaptureTool::getColorAtPoint(int x, int y) {
    CGImageRef image = getCaptureFromPoint(x, y);
    // 获取图像数据
    CGContextRef context = CGBitmapContextCreate(nullptr, 1, 1, 8, 4, CGColorSpaceCreateDeviceRGB(),
                                                 kCGImageAlphaPremultipliedLast);
    CGContextDrawImage(context, CGRectMake(0, 0, 1, 1), image);
    CGImageRelease(image);
    auto *data = (unsigned char *) CGBitmapContextGetData(context);
    auto *color = new QColor(data[0], data[1], data[2], data[3]);


    return *color;
}


QColor CaptureTool::getScreenPixelColor(const QPoint &point) {
    // 截取一个像素点的大小
    return {QGuiApplication::primaryScreen()->grabWindow(0, point.x(), point.y(), 1, 1).toImage().pixel(0, 0)};
}

QImage CaptureTool::creatImage(int x, int y) {
    auto size = QSize(x, y);
    return creatImage(size);
}

QImage CaptureTool::creatImage(QSize &size) {
    // 创建一个空的 QImage，指定大小和格式
    QImage image(size, QImage::Format_ARGB32_Premultiplied);
    image.fill(Qt::transparent);  // 填充透明背景
    return image;
}


QImage CaptureTool::rotateByCenter(QImage &image, qreal rotation) {
    //QRectF bounds = getRotatedImageBounds(image, rotation);
    double w = image.width();
    double h = image.height();
    double rad = rotation / (double) 180 * M_PI;

    double desW = 2 * ((h / (2 * abs(sin(rad)))) + (w / 2 - (h / (2 * abs(tan(rad))))) * abs(cos(rad)));
    double desH = 2 * abs(sin(rad)) * ((w / 2) + (h / (2 * abs(tan(rad)))));

    QImage tempImage(
    QSize((int) desW + 1, (int) desH + 1),
            QImage::Format_ARGB32);

    tempImage.fill(Qt::transparent);  // 填充透明背景
    // 创建 QPainter 对象在 QImage 上绘图
    QPainter painter(&tempImage);
    // 设置转换矩阵以调整大小、角度和位置
    QTransform transform;
    // 平移原点到图像中心
    transform.translate(desW / 2.0, desH / 2.0);
    // 旋转角度
    transform.rotate(rotation);
    //移回原位
    transform.translate(-w / 2, -h / 2);

    //应用变换
    painter.setTransform(transform);
    //绘入缓存
    painter.drawImage(0, 0, image);

    painter.drawRect(image.rect());
    //写入原图
    image = tempImage;

    return image;
}

QImage CaptureTool::moveImageContents(QImage &image, double dx, double dy) {
    auto size = image.size();
    auto tempImage = creatImage(size);

    // 创建 QPainter 对象在 QImage 上绘图
    QPainter painter(&tempImage);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // 设置转换矩阵以调整大小、角度和位置
    QTransform transform;
    transform.translate(dx, dy);
    painter.setTransform(transform);

    //画入缓存image
    painter.drawImage(0, 0, image);
    image = tempImage;

    return image;
}

QImage CaptureTool::moveImageContents(QImage &image, int dx, int dy) {
    return moveImageContents(image, (double) dx, (double) dy);
}

QImage CaptureTool::generateImage(const QString &svg, const QSize &size, const QColor &color) {
//    //计算放大倍率
//    int srcW = size.width();
//    int srcH = size.height();
//    int minEdge = std::min(srcW, srcH);
//    int maxEdge = std::max(srcW, srcH);
//    double scale = 1.0;
//    if (minEdge <= 2 && maxEdge >= 100) {}
//    else if (minEdge < 720) {
//        //最小边<720px
//        if (srcW < srcH) {
//            //宽< 高，以宽为基准放大到720，高一样按照此倍率直接放大
//            scale = 1024.0 / srcW;
//        } else {
//            //高 <= 宽
//            scale = 1024.0 / srcH;
//        }
//    }
//    int renderW = (int) (srcW * scale);
//    int renderH = (int) (srcH * scale);
    //创建图像
    auto image = creatImage(size.width(), size.height());
    {
        //绘图器
        QPainter painter(&image);
        qreal devicePixelRatio = painter.device()->devicePixelRatio();
        painter.setWorldTransform(QTransform::fromScale(devicePixelRatio, devicePixelRatio));
        //抗锯齿，顺滑
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setRenderHint(QPainter::SmoothPixmapTransform);
        painter.setRenderHint(QPainter::TextAntialiasing);

        QString colorName = color.name();
        //读取svg，修改colorFill
        QXmlStreamReader xmlReader(svg);
        QString modifiedSvgContent;
        QXmlStreamWriter xmlWriter(&modifiedSvgContent);
        xmlWriter.setAutoFormatting(true);

        // 逐个读取并修改 XML 元素
        while (!xmlReader.atEnd()) {
            xmlReader.readNext();
            if (xmlReader.isStartElement()) {
                xmlWriter.writeStartElement(xmlReader.name().toString());
                // 修改 fill 属性
                QXmlStreamAttributes attributes = xmlReader.attributes();
                bool fillReplaced = false;
                for (qsizetype i = 0; i < attributes.size(); ++i) {
                    if (attributes[i].name().toString() == "fill") {
                        attributes.replace(i, QXmlStreamAttribute("fill", colorName));
                        fillReplaced = true;
                        break;
                    }
                }
                if (!fillReplaced) {
                    attributes.append("fill", colorName);
                }

                for (const QXmlStreamAttribute &attr: attributes) {
                    xmlWriter.writeAttribute(attr.name().toString(), attr.value().toString());
                }
            } else if (xmlReader.isEndElement()) {
                xmlWriter.writeEndElement();
            } else if (xmlReader.isCharacters()) {
                xmlWriter.writeCharacters(xmlReader.text().toString());
            }
        }
        //渲染svg图像
        QSvgRenderer renderer(modifiedSvgContent.toUtf8());
        renderer.render(&painter);
    }
    return image;
}

QImage CaptureTool::adjustImageSize(QImage &image, int dx, int dy) {
    QSize size = image.size();
    size.setWidth(size.width() + dx);
    size.setHeight(size.height() + dy);
    auto tempImage = creatImage(size);
    QPainter painter(&tempImage);
    painter.drawImage(0, 0, image);
    image = tempImage;
    painter.end();

    return image;
}

QImage CaptureTool::adjustImageSizeByCenter(QImage &image, int dx, int dy) {
    if (dx < 0 && dy < 0) {
        // 从原图像中裁剪出指定区域
        QPixmap croppedPixmap = QPixmap::fromImage(image).copy(
                QRect(-dx / 2, -dy / 2, image.width() + dx, image.height() + dy));
        image = croppedPixmap.toImage();
        return image;
    }
    QSize size = image.size();
    size.setWidth(size.width() + dx);
    size.setHeight(size.height() + dy);
    auto tempImage = creatImage(size);
    QPainter painter(&tempImage);
    painter.drawImage(dx / 2, dy / 2, image);
    image = tempImage;

    return image;
}

QImage CaptureTool::scaleImageSizeByCenter(QImage &image, double scale, bool isSmooth) {
    QPixmap pixmap(QPixmap::fromImage(image));
    // 计算新的尺寸
    QSize newSize = image.size() * scale;
    // 设置变换中心为图像的中心
    QTransform transform;
    transform.translate(newSize.width() / 2.0, newSize.height() / 2.0);
    transform.scale(scale, scale);
    transform.translate(-image.width() / 2.0, -image.height() / 2.0);

    // 应用变换并绘制原始图像
    QPixmap resizedImage;
    if (!isSmooth)
        resizedImage = pixmap.transformed(transform, Qt::FastTransformation);
    else
        resizedImage = pixmap.transformed(transform, Qt::SmoothTransformation);

    image = resizedImage.toImage();

    return image;
}

QImage CaptureTool::rotateImage(QImage &image, qreal rotation) {
    QPixmap pixmap(QPixmap::fromImage(image));
    // 创建一个 QTransform 对象用于旋转
    QTransform transform;
    if (rotation != 0.0) {
        transform.rotate(rotation);  // 旋转
    }
    QPixmap rotatedPixmap = pixmap.transformed(transform, Qt::SmoothTransformation);
    image = rotatedPixmap.toImage();
    return image;

}

QIcon CaptureTool::generateIcon(QString &svg, QSize size) {
    // 使用 QSvgRenderer 渲染 SVG 字符串
    QSvgRenderer svgRenderer(svg.toUtf8());

    // 创建 QPixmap 用于显示图标
    QPixmap pixmap(size);
    pixmap.fill(Qt::transparent); // 填充透明背景

    QPainter painter(&pixmap);
    svgRenderer.render(&painter);
    painter.end();

    // 创建 QIcon 并设置图标
    return {pixmap};
}

QImage CaptureTool::captureRect(QRectF &rect) {
    // 截取屏幕区域
    return QGuiApplication::primaryScreen()->grabWindow(
            0, (int) (rect.x()), (int) (rect.y()), (int) (rect.width()), (int) (rect.height())
    ).toImage();
}



