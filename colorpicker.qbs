import qbs 1.0
import qbs.FileInfo

QtcPlugin {
    name: "ColorPicker"

    Depends { name: "Qt"; submodules: ["widgets"] }
    Depends { name: "Core" }
    Depends { name: "TextEditor" }

    cpp.cxxFlags: "-std=c++11"
    cpp.cxxLanguageVersion: "c++11"

    files: [
        "colormodifier.cpp",
        "colormodifier.h",
        "colorpicker_global.h",
        "colorpickerconstants.h",
        "colorpickeroptionspage.cpp",
        "colorpickeroptionspage.h",
        "colorpickerplugin.cpp",
        "colorpickerplugin.h",
        "colorwatcher.cpp",
        "colorwatcher.h",
        "langcontexts/ilangcontext.cpp",
        "langcontexts/ilangcontext.h",
        "widgets/advancedslider.cpp",
        "widgets/advancedslider.h",
        "widgets/colorpicker.cpp",
        "widgets/colorpicker.h",
        "widgets/colorpickersettingswidget.cpp",
        "widgets/colorpickersettingswidget.h",
        "widgets/hueslider.cpp",
        "widgets/hueslider.h",
        "langcontexts/qsslangcontext.cpp",
        "langcontexts/qsslangcontext.h",
        "widgets/opacityslider.cpp",
        "widgets/opacityslider.h",
        "widgets/colordialog.cpp",
        "widgets/colordialog.h",
    ]

    Group {
        name: "Tests"
        condition: project.testsEnabled

        files: [
            "replacecolor_test.cpp",
            "widgets_test.cpp"
        ]

        cpp.defines: outer.concat(['SRCDIR="' + FileInfo.path(filePath) + '"'])
    }
}
