#include "tree_mutator.h"
#include "../shared/rand.h"

void TreeMutator::mutate(Tree* tree, float mutationRate) {
    PointerLookupDictionaryEntry* entry = tree->nodeLookup->head;

    while (entry != nullptr) {
        Node* node = (Node*)entry->value;

        for (int i=0;i<node->current_forward;i++) {
            NodeLink* link = node->forward_nodes[i];

            link->weight *= (1.0f + mutationRate * ((float)rand() / RAND_MAX * 2.0f - 1.0f));
            link->offset *= (1.0f + mutationRate * ((float)rand() / RAND_MAX * 2.0f - 1.0f));
        }

        entry = entry->next;
    }
}