# Copyright 2018 Cybertech Labs Ltd.
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

TEMPLATE = subdirs

include(../../../../global.pri)

win32 {
	copyToDestdir(python36.dll, NOW)
}

# todo check and add appropriate libs!!!
#macx {
#}
#
#linux {
#}

CONFIG(clang) {
	QMAKE_CXXFLAGS += -Wno-error=zero-length-array -Wno-error=vla-extension
}
