# Copyright 2017 QReal Research Group
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

TARGET = robots-pioneer-lua-generator

include(../../../../../global.pri)

QT += widgets

TEMPLATE = lib
CONFIG += plugin

DESTDIR = $$DESTDIR/plugins/tools/kitPlugins/

includes( \
		plugins/robots/generators/generatorBase \
		plugins/robots/common/kitBase \
		plugins/robots/common/pioneerKit \
		plugins/robots/utils \
		qrtext \
)

links(qrkernel qslog qrutils qrrepo qscintilla2 qrgui-text-editor qrtext robots-kit-base \
		robots-generator-base robots-pioneer-kit robots-utils)

TRANSLATIONS = $$PWD/../../../../../qrtranslations/ru/plugins/robots/pioneerLuaGenerator_ru.ts

HEADERS += \
	$$PWD/pioneerLuaGeneratorCustomizer.h \
	$$PWD/pioneerLuaGeneratorFactory.h \
	$$PWD/pioneerLuaGeneratorPlugin.h \
	$$PWD/pioneerLuaMasterGenerator.h \

SOURCES += \
	$$PWD/pioneerLuaGeneratorCustomizer.cpp \
	$$PWD/pioneerLuaGeneratorFactory.cpp \
	$$PWD/pioneerLuaGeneratorPlugin.cpp \
	$$PWD/pioneerLuaMasterGenerator.cpp \

RESOURCES += \
	$$PWD/pioneerLuaGenerator.qrc \
	$$PWD/templates.qrc \
