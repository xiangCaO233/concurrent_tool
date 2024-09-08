//
// Created by 2333 xiang on 2024/8/29.
//

#include "PopMenu.h"

using namespace std;


vector<string> PopMenu::functions = {"color", "zoom", "ruler", "capture", "translate", "start", "more"};
string PopMenu::runningFunc;

PopMenu::PopMenu(int x, int y) : UndecoratedWidget() {
    move(x, y);
    //启用鼠标追踪
    setMouseTracking(true);
    resize(pubRef::menuSize);
    generatePainterPath();

    //polygonWidget.show();
    polygonWidget.setPath(path);
}

double PopMenu::getProgress() const {
    return progress;
}

void PopMenu::setProgress(double val) {
    if (val < 0)progress = 0; else if (val > 1)progress = 1; else progress = val;
}

void PopMenu::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    QRect wRect = rect();
    //长宽分别缩小40px
    wRect.adjust(20, 20, -20, -20);

    painter.setBrush(pubRef::dBack);
//    painter.setPen(pubRef::pink);
    painter.setPen(Qt::NoPen);
    painter.drawPath(path);
    //绘制功能键内容
    paintFuncs(painter, wRect);
}

void PopMenu::paintFuncs(QPainter &p, QRect rect) {
    //rect = displayPath.boundingRect().toRect();

    //小半径
    double lR = pubRef::gold / 2 * rect.width();
    //大半径
    double bR = rect.width() / 2.0;
    //半径差
    double dR = (bR - lR);
    //中心半径
    double cR = lR + dR / 2;

    //绘制全部功能键
    for (const string &fName: functions) {
        try {
            QString svg = pubRef::svgs.at(fName);
            //生成图像
            QSize iconSize = QSize((int) ((1 - pow(pubRef::gold, 2)) * dR), (int) ((1 - pow(pubRef::gold, 2)) * dR));
            if (hoveredFunc[fName]) {
                iconSize.setWidth(iconSize.width() + 10);
                iconSize.setHeight(iconSize.height() + 10);
            }
            auto image = CaptureTool::generateImage(svg, iconSize, pubRef::pink);
            //旋转图像
            //获得位置
            int index = (int) (spanAngle / 30.0 / 16.0) - 1 - (int) std::distance(
                    functions.begin(),
                    std::find(functions.begin(), functions.end(), fName)
            );
            //角度位置
            qreal posAngel = 90 - (30 * (index) + (startAngle / 16.0) + 15) -
                             (progress * ((int) functions.size() - (int) (spanAngle / 30.0 / 16.0)) * 30);
            //转化弧度制
            double rad = (posAngel / 180) * M_PI;
            //按角度旋转(并扭正放大镜)
//            if (std::equal(fName.begin(), fName.end(), "zoom")) CaptureTool::rotateImage(image, posAngel + 45);
//            else CaptureTool::rotateImage(image, posAngel);
            //计算图片位置

            double x = rect.x() + (rect.width() / 2.0) + cR * sin(rad) - (image.width() / 2.0);
            double y = rect.y() + (rect.height() / 2.0) - cR * cos(rad) - (image.height() / 2.0);

            QRect imageRect = QRect((int) x, (int) y, image.width(), image.height());
            // 创建一个监测矩形
            QRect detectRect = imageRect;

            // 计算新的宽度和高度（缩小到pow(pubRef::gold,1.5)倍）
            int newWidth = static_cast<int>(imageRect.width() * pow(pubRef::gold, 1.5));
            int newHeight = static_cast<int>(imageRect.height() * pow(pubRef::gold, 1.5));

            // 设置新的宽度和高度
            detectRect.setWidth(newWidth);
            detectRect.setHeight(newHeight);

            // 将矩形中心移动到原始中心位置
            detectRect.moveCenter(imageRect.center());

            //判断此图片是否包含在绘制区域内
            if (path.contains(detectRect)) {
//                p.setPen(Qt::red);
//                p.drawRect(detectRect);
                p.drawImage((int) x, (int) y, image);
                funcRecs[fName] = imageRect;
            } else funcRecs.erase(fName);
        } catch (const std::out_of_range &e) {
            cout << e.what() << endl;
        }
    }
}

void PopMenu::wheelEvent(QWheelEvent *event) {
    //设置滚动进度
    setProgress(getProgress() + (-event->pixelDelta().y() / (4000.0 / pubRef::displayCount)));
    //悬浮监测
    hoverDetect();
    repaint();
}

void PopMenu::mouseMoveEvent(QMouseEvent *event) {
    //更新鼠标位置
    current = event->pos();
    //悬浮监测
    hoverDetect();
    repaint();
}

void PopMenu::mousePressEvent(QMouseEvent *event) {
    cout << event->button() << endl;
    for (auto &pair: hoveredFunc) {
        if (hoveredFunc[pair.first]) {
            if (event->button() == 1) {//左键
//                cout << pair.first << "->left click" << endl;
                if (pair.first == "capture") {
                    //截图
                    captureWidget.display();
                    //隐藏本体
                    hide();
                }
                if (pair.first == "color") {
                    //颜色工具
                    cout << "show color" << endl;
                    capColor();
                    colorIndicator->updateColor(Qt::black, event->pos() + this->pos());
                    colorIndicator->displayColor();
                    //隐藏本体
                    hide();
                }
                if (pair.first == "zoom") {
                    //放大镜工具
                    //显示一个放大镜选择框
                    QPoint here = event->pos() + this->pos();
                    auto r = QRect(here.x(), here.y(), 100, 100);
                    delete magWidget;
                    magWidget = new MagnifySelector(r);
                    magWidget->show();
                    magWidget->showZoom();
                    //隐藏本体
                    hide();
                }
                if (pair.first == "ruler") {
                    //标尺工具
                    ruler = new ScreenRuler;
                    ruler->move(
                            QPoint((pubRef::poiWidth - ruler->width()) / 2, (pubRef::poiHeight - ruler->height()) / 2));
                    ruler->show();
                    //隐藏本体
                    hide();
                }
                if (pair.first == "translate") {
                    //翻译工具
                    translator = new Translator;
                    translator->move(event->pos());
                    translator->show();
                    //隐藏本体
                    hide();
                }
                if (pair.first == "start") {
                    //启动工具
                    const char *url = "https://www.yuanshen.com";
                    std::string command = "open " + std::string(url);
                    system(command.c_str());
                    //隐藏本体
                    hide();
                }
                if (pair.first == "more") {
                    //其他

                    //隐藏本体
                    hide();
                }
                runningFunc = pair.first;
                hoveredFunc[pair.first] = false;
            } else if (event->button() == 2) {//右键
                cout << pair.first << "->right click" << endl;
            }
        }
    }
}

void PopMenu::generatePainterPath() {
    QRect rect = this->rect().adjusted(20, 20, -20, -20);


    //大圆圆心坐标(rect宽=高=大圆半径)
    double x = rect.x();
    double y = rect.y();
    double rWidth = rect.width();
    double rHeight = rect.width();

    //小圆直径
    double r = (1 - pubRef::gold) * ((double) rect.width() / 2.0);

    //小圆心距离大圆心(大半径+小半径)/2
    double l = (1 + pubRef::gold) * ((double) rect.width() / 4.0);
    //计算左侧小圆矩形位置
    //矩形坐标位置
    double x1 =
            x + (rWidth / 2.0) - l * cos((180 - ((startAngle + spanAngle) / 16.0)) / 180.0 * M_PI) -
            (r / 2.0);
    double y1 =
            y + (rHeight / 2.0) - l * sin((180 - ((startAngle + spanAngle) / 16.0)) / 180.0 * M_PI) -
            (r / 2.0);
    ellipse1 = QRectF(x1, y1, r, r);

    //计算右侧小圆矩形位置
    //矩形坐标位置
    double x2 = x + (rWidth / 2.0) + l * cos(startAngle / 16.0 / 180.0 * M_PI) - (r / 2.0);
    double y2 = y + (rHeight / 2.0) - l * sin(startAngle / 16.0 / 180.0 * M_PI) - (r / 2.0);
    ellipse2 = QRectF(x2, y2, r, r);

    //左侧圆路径
    QPainterPath e1;
    e1.addEllipse(ellipse1);
    //右侧圆路径
    QPainterPath e2;
    e2.addEllipse(ellipse2);

    // 扇形区域
    QPainterPath bgPath;
    bgPath.moveTo(rect.center());  // 移动到扇形的中心
    bgPath.arcTo(rect, startAngle / 16.0, spanAngle / 16.0);   // 定义扇形弧度
    bgPath.lineTo(rect.center());//复原
    bgPath.closeSubpath();//闭合路径

    //遮罩边长变化
    int dw = (int) (rect.width() * (1 - pubRef::gold));
    int dh = (int) (rect.height() * (1 - pubRef::gold));
    //遮罩路径
    rect.adjust(dw / 2 - 1, dh / 2 - 1, -dw / 2 + 1, -dh / 2 + 1);
    QPainterPath maskPath;
    maskPath.addEllipse(rect);
    //合并路径
    path = bgPath.united(e1).united(e2).subtracted(maskPath);
    //  计算绘制部分
    // 获取路径的边界矩形
    QRectF boundingRect = path.boundingRect();

    // 计算路径的中心点
    QPointF pathCenter = boundingRect.center();

    // 创建一个变换对象
    QTransform transform;

    // 平移变换: 将路径的中心点移到原点
    transform.translate(pathCenter.x(), pathCenter.y());

    // 缩放变换: 相对于原点进行缩放
    transform.scale(pubRef::gold, pubRef::gold);

    // 平移变换: 将路径移回到原来的中心位置
    transform.translate(-pathCenter.x(), -pathCenter.y());

    // 应用变换到路径
    displayPath = transform.map(path);
}

void PopMenu::hoverDetect() {
    //更改悬浮标识
    for (auto &pair: funcRecs) hoveredFunc[pair.first] = pair.second.contains(current);
}

PopMenu::~PopMenu() {
    std::cout << "release mainMenu" << std::endl;
    delete magWidget;
    delete colorIndicator;
    delete floatIndicator;
    delete translator;
}

void PopMenu::capColor() {
    delete floatIndicator;
    if (colorIndicator) delete colorIndicator->receiver;
    floatIndicator = colorIndicator;
    colorIndicator = new ColorIndicator;
}

