//
// Created by 2333 xiang on 2024/9/4.
//

#include "Translator.h"

Translator::Translator() : CloseableWidget() {
    rootLayout = new QVBoxLayout;

    textWidget = new QWidget;
    tLayout = new QHBoxLayout;

    leftChildWidget = new QWidget;
    leftLangLayout = new QVBoxLayout;

    rightChildWidget = new QWidget;
    rightLangLayout = new QVBoxLayout;

    title = new QLabel("翻译");
    apiSelection = new QComboBox;
    apiSelection->addItem("百度翻译");

    srcText = new QTextEdit;
    desText = new QTextEdit;
    leftLangSelection = new QComboBox;
    rightLangSelection = new QComboBox;
    initLangSelector(leftLangSelection);
    initLangSelector(rightLangSelection);

    leftLangSelection->setCurrentText("自动检测");
    rightLangSelection->setCurrentText("中文");


    switchSide = new QPushButton(
            QIcon(
                    CaptureTool::generateIcon(pubRef::svgs["switch"],
                                              QSize(30, 30))),
            "");
    perform = new QPushButton("➡");
    connect(switchSide,&QPushButton::clicked,[this](){
        QString temp = leftLangSelection->currentText();
        leftLangSelection->setCurrentText(rightLangSelection->currentText());
        rightLangSelection->setCurrentText(temp);
    });

    //分离线程访问百度翻译使用信号与槽回调

    connect(perform, &QPushButton::clicked, this, [=]() {
        performTranslate();
    });


    leftLangLayout->setSpacing(4);
    leftLangLayout->setContentsMargins(1, 1, 1, 1);
    leftLangLayout->addWidget(leftLangSelection);
    leftLangLayout->addWidget(srcText);
    leftChildWidget->setLayout(leftLangLayout);

    rightLangLayout->setSpacing(4);
    rightLangLayout->setContentsMargins(1, 1, 1, 1);
    rightLangLayout->addWidget(rightLangSelection);
    rightLangLayout->addWidget(desText);
    rightChildWidget->setLayout(rightLangLayout);

    tLayout->addWidget(leftChildWidget);
    tLayout->addWidget(switchSide);
    tLayout->addWidget(rightChildWidget);
    textWidget->setLayout(tLayout);

    rootLayout->setSpacing(2);
    rootLayout->setContentsMargins(1, 1, 1, 1);

    rootLayout->addWidget(title, 0, Qt::AlignCenter);
    rootLayout->addWidget(apiSelection);
    rootLayout->addWidget(textWidget);
    rootLayout->addWidget(perform);

    setLayout(rootLayout);
    QClipboard *clipboard = QApplication::clipboard();
    // 获取剪贴板中的 MIME 数据
    const QMimeData *mimeData = clipboard->mimeData();
    // 检查 MIME 数据是否包含纯文本
    if (mimeData->hasText()) {
        // 获取文本内容
        QString text = mimeData->text();
        srcText->setText(text);
    }
    performTranslate();
}

void Translator::paintEvent(QPaintEvent *event) {
    QPainter p(this);
    p.setBrush(pubRef::dBack);
    p.setPen(QPen(pubRef::pink, 2));
    p.drawRect(rect());
}

void Translator::contextMenuEvent(QContextMenuEvent *event) {
    QMenu menu(this);
    // 添加动作到菜单
    QAction *close = menu.addAction(CaptureTool::generateIcon(pubRef::svgs["close"], QSize(24, 24)), "关闭");
    connect(close, &QAction::triggered, this, [this]() {
        destroy();
    });

    // 显示菜单
    menu.exec(event->globalPos());
}

void Translator::updateDes(const QString &desStr) {
    this->desText->setText(desStr);
    repaint();
}

void Translator::initLangSelector(QComboBox *comboBox) {
    for (const auto &pair: BaiduTranslator::reverseMap) {
        comboBox->addItem(QString::fromStdString(pair.first));
    }
}

void Translator::performTranslate() {
    transer = new Transer;
    connect(transer, &Transer::done, this, &Translator::updateDes);
    auto *transerThread = new QThread;
    transer->moveToThread(transerThread);
    QMetaObject::invokeMethod(transer, "doTranslate", Qt::QueuedConnection,
                              Q_ARG(QString, leftLangSelection->currentText()),
                              Q_ARG(QString, rightLangSelection->currentText()),
                              Q_ARG(QString, srcText->toPlainText()));
    //翻译完成销毁此线程（即用即毁）
    connect(transerThread, &QThread::finished, transerThread, &QObject::deleteLater);
    connect(transerThread, &QThread::finished, transer, &Transer::deleteLater);
    transerThread->start();
}

