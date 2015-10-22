ColorPickerPlugin for QtCreator
===============================

A color picker plugin to easily insert and modify colors in QtCreator's text documents.

![Overview](readme_resources/overview.png)

Features
-----------------

- Supports the following color formats : `rgb`, `hsv`, `hsl`, `QML`, `GLSL` and `hex`.

Settings
-----------------

- Available formats can only be those supported by the current text editor. For example, the dialog only proposes `Qt.rgba` and `Qt.hsla` formats if you're editing a `QML` file.

Build the plugin
-----------------
Put all files in `<QtCreatorSourcesDir>/src/plugins/colorpicker`.

Now open `<QtCreatorSourcesDir>/src/plugins.qbs` with your favorite text editor and add the project file to the reference list (something like `"colorpicker/colorpicker.qbs"`).

Build QtCreator. That's it.

Please note
-----------------
- This plugin is developed for QtCreator >= 3.5.0. I will not test it with earlier versions.

- I use Qbs rather than QMake. It seems that there's currently no way to develop a plugin without having the whole QtCreator project opened.

- WIP !
