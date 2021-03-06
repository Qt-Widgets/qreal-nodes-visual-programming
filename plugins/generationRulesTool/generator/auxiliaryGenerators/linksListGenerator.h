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

#pragma once

#include <QtCore/QString>
#include <QtCore/QSharedPointer>

#include <qrgui/plugins/toolPluginInterface/usedInterfaces/logicalModelAssistInterface.h>

#include "ast/identifier.h"

#include "generator/commonInfo/variablesTable.h"
#include "generator/commonInfo/currentScope.h"

namespace generationRules {
namespace generator {

/// Class that generates list of links of given type.
class LinksListGenerator
{
public:
	/// Returns list of links ids by type.
	/// @param linksIdentifierNode - first part (for example, identName in identName.links(SpecificType)).
	/// @param linksTypeNode - second part (SpecificType in previous example).
	/// @param logicalModelInterface - information about model.
	/// @param variablesTable - table of variables.
	/// @param currentScope - information about current scope.
	static qReal::IdList generatedList(const QSharedPointer<simpleParser::ast::Node> &linksIdentifierNode
			, const QSharedPointer<simpleParser::ast::Identifier> &linksTypeNode
			, qReal::LogicalModelAssistInterface *logicalModelInterface
			, VariablesTable &variablesTable
			, const CurrentScope &currentScope
			);

	/// Returns id of current element.
	/// @param linksIdentifierNode - identifier node or "this".
	/// @param variablesTable - table of variables.
	/// @param currentScope - information about current scope.
	static qReal::Id elementId(const QSharedPointer<simpleParser::ast::Node> &linksIdentifierNode
			, VariablesTable &variablesTable
			, const CurrentScope &currentScope);

	/// Returns links of needed type from links of all types.
	/// @param linksTypeNode - links type node.
	/// @param allLinks - list of all links.
	static qReal::IdList linksOfNeededType(const QSharedPointer<simpleParser::ast::Identifier> &linksTypeNode
			, const qReal::IdList &allLinks);
};

}
}
