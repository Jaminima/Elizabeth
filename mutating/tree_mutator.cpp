#include "tree_mutator.h"
#include "../shared/rand.h"
#include "../shared/node_helper.h"

void TreeMutator::mutate(Tree* tree, float mutationRate, float reactionRate) {
    PointerLookupDictionaryEntry* entry = tree->nodeLookup->head;

    while (entry != nullptr) {
        Node* node = (Node*)entry->value;

        for (int i=0;i<node->current_forward;i++) {
            NodeLink* link = node->forward_nodes[i];

            link->weight *= (1.0f + mutationRate * Rand::getFloat(-1.0f, 1.0f));
            link->offset *= (1.0f + mutationRate * Rand::getFloat(-1.0f, 1.0f));
        }

        if (Rand::getFloat(0.0f, 1.0f) < reactionRate) {
            int mode = Rand::getInt(0, 1);

            if (mode == 0) {
                int randomIndex = Rand::getInt(0, tree->outputNodeCount - 1);

                Node* outputNode = tree->outputNodes[randomIndex];

                if (NodeHelper::canAddLinkToNodes(node, outputNode)) {
                    NodeHelper::linkNodes(node, outputNode);
                }
            } else {
                int randomIndex = Rand::getInt(0, tree->inputNodeCount - 1);

                Node* inputNode = tree->inputNodes[randomIndex];

                if (NodeHelper::canAddLinkToNodes(inputNode, node)) {
                    NodeHelper::linkNodes(inputNode, node);
                }
            }
        }

        entry = entry->next;
    }
}