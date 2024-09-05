cmake_minimum_required(VERSION 3.25)
project(concurrent_toolkit)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# 设置库的路径
set(BaiduTranslateLib_DIR "lib")

find_library(BaiduTranslateLib NAMES BaiduTranslateLib PATHS ${BaiduTranslateLib_DIR})


# 查找 Qt6 包
find_package(Qt6 COMPONENTS
        Core
        Gui
        Svg
        Widgets
        REQUIRED)

# 添加头文件目录
include_directories(${CMAKE_SOURCE_DIR}/include)

# 添加库目录
#link_directories(${CMAKE_SOURCE_DIR}/lib)

# 指定编译器标志以支持 Objective-C++
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -x objective-c++")

# 添加源文件
set(SOURCES
        main.cpp
        App.cpp
        listener/MouseMotionListener.cpp
        listener/MouseListener.cpp
        listener/KeyListener.cpp
        listener/MouseWheelListener.cpp
        widget/TestRound.cpp
        widget/menu/PopMenu.cpp
        widget/capture/CaptureWidget.cpp
        tool/CaptureTool.cpp
        tool/PublicReference.cpp include/GlobalScreen.h include/GlobalScreen.cpp include/keyboard/dispatcher/KeyEventDispatcher.cpp include/pointer/dispatcher/PointerEventDispatcher.cpp include/pointer/dispatcher/WheelEventDispatcher.cpp widget/testwidget/PolygonWidget.cpp widget/testwidget/PolygonWidget.h widget/capture/FloatImage.cpp widget/capture/FloatImage.h widget/template/UndecorateWidget.cpp widget/template/UndecoratedWidget.h widget/color/ColorIndicator.cpp widget/color/ColorIndicator.h widget/zoom/MagnifySelector.cpp widget/zoom/MagnifySelector.h widget/zoom/MagnifyRes.cpp widget/zoom/MagnifyRes.h widget/zoom/ZoomUpdater.cpp widget/zoom/ZoomUpdater.h widget/zoom/RateTip.cpp widget/zoom/RateTip.h widget/color/ColorReceiver.cpp widget/color/ColorReceiver.h widget/color/ColorTip.cpp widget/template/DraggableWidget.cpp widget/template/DraggableWidget.h widget/template/CloseableWidget.cpp widget/template/CloseableWidget.h widget/ruler/ScreenRuler.cpp widget/ruler/ScreenRuler.h widget/translator/Translator.cpp widget/translator/Translator.h widget/translator/Transer.cpp widget/translator/Transer.h widget/setting/SettingWidget.cpp widget/setting/SettingWidget.h)

# 创建可执行文件
add_executable(concurrent_toolkit ${SOURCES})

# 链接 Qt6 和其他库
target_link_libraries(concurrent_toolkit
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Svg
        ${BaiduTranslateLib}
        )

#设置 macOS 的支持
if (APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fobjc-arc")
    find_library(APPKIT_LIBRARY AppKit)
    target_link_libraries(concurrent_toolkit ${APPKIT_LIBRARY})
    set_target_properties(concurrent_toolkit PROPERTIES
            MACOSX_BUNDLE ON
            )
endif ()
