/* Copyright 2007-2015 QReal Research Group
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License. */

#include "detectorToVariableGenerator.h"

#include <generatorBase/generatorCustomizer.h>

using namespace trik::simple;
using namespace generatorBase::simple;

DetectorToVariableGenerator::DetectorToVariableGenerator(const qrRepo::RepoApi &repo
		, generatorBase::GeneratorCustomizer &customizer
		, const qReal::Id &id
		, QObject *parent)
	: BindingGenerator(repo, customizer, id, "function.t"
			, { Binding::createStaticConverting("@@BODY@@"
					, repo.property(id, "Variable").toString().isEmpty()
							// For more comprehensible error reporting we pass an empty string if there is empty
							// property in a repository, otherwise parser will be complaining about "= lineSensorX",
							// but that string is not even seen by user.
							? ""
							: repo.property(id, "Variable").toString() + "= lineSensor[0]"
					, customizer.factory()->functionBlockConverter(id, "Variable"))
			}, parent)
{
}
