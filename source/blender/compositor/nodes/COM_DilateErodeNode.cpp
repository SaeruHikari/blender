/*
 * Copyright 2011, Blender Foundation.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * Contributor: 
 *		Jeroen Bakker 
 *		Monique Dewanchand
 */

#include "COM_DilateErodeNode.h"
#include "DNA_scene_types.h"
#include "COM_ExecutionSystem.h"
#include "COM_DilateErodeOperation.h"
#include "COM_AntiAliasOperation.h"
#include "BLI_math.h"

DilateErodeNode::DilateErodeNode(bNode *editorNode): Node(editorNode) {
}

void DilateErodeNode::convertToOperations(ExecutionSystem *graph, CompositorContext * context) {
	bNode* editorNode = this->getbNode();
	DilateErodeOperation *operation = new DilateErodeOperation();
	operation->setDistance(editorNode->custom2);
	operation->setInset(2.0f);
	
	this->getInputSocket(0)->relinkConnections(operation->getInputSocket(0));

	AntiAliasOperation * antiAlias = new AntiAliasOperation();
	addLink(graph, operation->getOutputSocket(), antiAlias->getInputSocket(0));
	this->getOutputSocket(0)->relinkConnections(antiAlias->getOutputSocket(0));
	graph->addOperation(operation);
	graph->addOperation(antiAlias);
}
