#ifndef POINTER_LOOKUP_DICTIONARY_H
#define POINTER_LOOKUP_DICTIONARY_H


class PointerLookupDictionaryEntry {
    public:
    void* key;
    void* value;
    PointerLookupDictionaryEntry* next;
};

class PointerLookupDictionary {
    public:
    PointerLookupDictionaryEntry* head;

    void add(void* key, void* value){
        PointerLookupDictionaryEntry* newEntry = new PointerLookupDictionaryEntry();
        newEntry->key = key;
        newEntry->value = value;
        newEntry->next = head;
        head = newEntry;
    }
    void* get(void* key){
        PointerLookupDictionaryEntry* current = head;
        while(current != nullptr){
            if(current->key == key){
                return current->value;
            }
            current = current->next;
        }
        return nullptr;
    }
};

#endif // POINTER_LOOKUP_DICTIONARY_H