RESOURCES = $$PWD/qrgui.qrc

LIBS += -L$$PWD/../bin -lqrrepo -lqrkernel -lqrutils #-lqrmc
LIBS += -L$$PWD/../bin/thirdparty -lqscintilla2

unix:DEFINES   = _TTY_POSIX_
win32:DEFINES  = _TTY_WIN_

# Graphical elements
include(umllib/umllib.pri)

# Dialogs
include(dialogs/dialogs.pri)

# Main window
include(mainwindow/mainwindow.pri)

# Graphical and logical models
include(models/models.pri)

# View
include(view/view.pri)

# Controller
include(controller/controller.pri)

# Built-in generators
include(generators/generators.pri)

# The code from the Internet
include(thirdparty/thirdparty.pri)

# Plugin management
include(pluginManager/pluginManager.pri)

# Interfaces for plugins, used by qrxc and qrmc
include(editorPluginInterface/editorPluginInterface.pri)

# Interfaces for tool plugins, used in handcoded tools
include(toolPluginInterface/toolPluginInterface.pri)

# Text Editor
include(textEditor/textEditor.pri)

# Hot Key Manager
include(hotKeyManager/hotKeyManager.pri)
