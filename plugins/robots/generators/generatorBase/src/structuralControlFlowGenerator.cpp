/* Copyright 2017 QReal Research Group
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
#include "structuralControlFlowGenerator.h"

#include <QtCore/QQueue>

#include <QtCore/QDebug>

using namespace qReal;
using namespace generatorBase;
using namespace semantics;


StructuralControlFlowGenerator::StructuralControlFlowGenerator(const qrRepo::RepoApi &repo
		, ErrorReporterInterface &errorReporter
		, GeneratorCustomizer &customizer
		, PrimaryControlFlowValidator &validator
		, const Id &diagramId
		, QObject *parent
		, bool isThisDiagramMain)
	: ControlFlowGeneratorBase(repo, errorReporter, customizer, validator, diagramId, parent, isThisDiagramMain)
	, mVerteces(0)
	, isPerformingGeneration(false)
{
}

ControlFlowGeneratorBase *StructuralControlFlowGenerator::cloneFor(const Id &diagramId, bool cloneForNewDiagram)
{
	Q_UNUSED(diagramId)
	Q_UNUSED(cloneForNewDiagram)
	// to do
	return nullptr;
}

void StructuralControlFlowGenerator::beforeSearch()
{
	// to do
}

void StructuralControlFlowGenerator::visit(const Id &id, const QList<LinkInfo> &links)
{
	if (!isPerformingGeneration) {
		updateVerteces(id, links);
	} else {
		//dummyReduceFunction(mMapIdToVertexLabel[id]);
		ControlFlowGeneratorBase::visit(id, links);
	}
}

void StructuralControlFlowGenerator::visitRegular(const Id &id, const QList<LinkInfo> &links)
{

}

void StructuralControlFlowGenerator::visitConditional(const Id &id, const QList<LinkInfo> &links)
{
	Q_UNUSED(links)

	int vertex = mMapIdToVertexLabel[id];
	if (isIfThen(id)) {

	} else {

	}


	int thenNodeLabel = mMapIdToVertexLabel[]


	dummyReduceFunction(vertex);
}

void StructuralControlFlowGenerator::visitLoop(const Id &id, const QList<LinkInfo> &links)
{
	if (isPerformingGeneration) {
		dummyReduceFunction(mMapIdToVertexLabel[id]);
	} else {

	}
}

void StructuralControlFlowGenerator::visitSwitch(const Id &id, const QList<LinkInfo> &links)
{

	dummyReduceFunction(vertex);
}

void StructuralControlFlowGenerator::visitUnknown(const Id &id, const QList<LinkInfo> &links)
{
	dummyReduceFunction(mMapIdToVertexLabel[id]);
}

void StructuralControlFlowGenerator::afterSearch()
{
}

SemanticTree *StructuralControlFlowGenerator::generate(const Id &initialNode, const QString &threadId)
{
	ControlFlowGeneratorBase::generate(initialNode, threadId);
	return mSemanticTree;
}

void StructuralControlFlowGenerator::performGeneration()
{
	isPerformingGeneration = true;
	buildGraph();
	// to bypass diagram and build graph
	ControlFlowGeneratorBase::performGeneration();
	// to-do check whether diagram was right, maybe ControlFlowGeneratorBase is checking it
}

bool StructuralControlFlowGenerator::isBlock(const Id &id, QVector<int> &region)
{
	int node = mMapIdToVertexLabel[id];
	QVector<int> outgoingList = mFollowers[node];
	if (outgoingList.size() == 1) {
		int next = outgoingList.first();
		if (mPredecessor[next].size() == 1) {
			region.push_back(node);
			region.push_back(next);
			return true;
		}
	}

	return false;
}

bool StructuralControlFlowGenerator::isIfThen(const Id &id, QVector<int> &region)
{
	// it is assumed that semantics of id is If
	QPair<LinkInfo, LinkInfo> branches(ifBranchesFor(id));
	qReal::Id thenNode = branches.first.target;
	qReal::Id elseNode = branches.second.target;

	int thenNodeNumber = mMapIdToVertexLabel[thenNode];
	int elseNodeNumber = mMapIdToVertexLabel[elseNode];

	if (mFollowers[thenNodeNumber].size() == 1 && mPredecessor[thenNodeNumber].size() == 1) {
		int v = mFollowers[thenNodeNumber].first();
		if (v == elseNodeNumber) {
			region.push_back(mMapIdToVertexLabel[id]);
			region.push_back(thenNodeNumber);
			return true;
		}
	}

	return false;
}

bool StructuralControlFlowGenerator::isIfThenElse(const Id &id, QVector<int> &region)
{
	// it is assumed that semantics of id is If
	QPair<LinkInfo, LinkInfo> branches(ifBranchesFor(id));
	qReal::Id thenNode = branches.first.target;
	qReal::Id elseNode = branches.second.target;

	int thenNodeNumber = mMapIdToVertexLabel[thenNode];
	int elseNodeNumber = mMapIdToVertexLabel[elseNode];

	if (mFollowers[thenNodeNumber].size() == 1 && mPredecessor[thenNodeNumber].size() == 1 &&
				mFollowers[elseNodeNumber].size() == 1 && mPredecessor[elseNodeNumber].size() == 1) {

		int v = mFollowers[thenNodeNumber].first();
		int u = mFollowers[elseNodeNumber].first();
		if (v == u) {
			region.push_back(mMapIdToVertexLabel[id]);
			region.push_back(thenNodeNumber);
			region.push_back(elseNodeNumber);
			return true;
		}
	}

	return false;
}

bool StructuralControlFlowGenerator::isSwitch(const Id &id, QVector<int> &region)
{

}

bool StructuralControlFlowGenerator::isSelfLoop(const Id &id, QVector<int> &region)
{
	int node = mMapIdToVertexLabel[id];
	if (mFollowers[node].size() == 1) {
		int next = mFollowers[node].first();
		if (next == node) {
			region.push_back(node);
			return true;
		}
	}
}

bool StructuralControlFlowGenerator::isWhileLoop(const Id &id, QVector<int> &region)
{
	int node = mMapIdToVertexLabel[id];
	if (mFollowers[node].size() == 2) {
		int v = mFollowers[node].at(0);
		int u = mFollowers[node].at(1);

		if (mFollowers[v].size() == 1 && mPredecessor[v].size() == 1
					&& mFollowers[v].first() == node) {
			region.push_back(node);
			region.push_back(v);
			return true;
		} else if (mFollowers[u].size() == 1 && mPredecessor[u].size() == 1
						&& mFollowers[u].first() == node) {
			region.push_back(node);
			region.push_back(u);
			return true;
		}
	}

	return false;
}

void StructuralControlFlowGenerator::updateVerteces(const Id &id, const QList<LinkInfo> &links)
{
	mMapIdToVertexLabel[id] = mVerteces;
	mMapVertexLabelToId[mVerteces] = id;
	mTrees[mVerteces] = mSemanticTree->produceNodeFor(id);
	mVerteces++;
}

void StructuralControlFlowGenerator::dummyReduceFunction(int vertexLabel)
{
	bool ok = true;
	while (ok) {
		ok = false;
		if (isBlock(vertexLabel)) {

			ok = true;
			continue;
		}



	}
}

void StructuralControlFlowGenerator::buildGraph()
{
	for (int vertex : mMapVertexLabelToId.keys()) {
		const qReal::Id id = mMapVertexLabelToId[vertex];

		for (const qReal::Id u : mRepo.outgoingLinks(id)) {
			mFollowers[vertex].push_back(mMapIdToVertexLabel[u]);
		}

		for (const qReal::Id u : mRepo.incomingLinks(id)) {
			mPredecessor[vertex].push_back(mMapIdToVertexLabel[u]);
		}
	}
}
