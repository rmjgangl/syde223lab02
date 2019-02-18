#include "lab2_drones_manager.h"
#include <iostream>

DronesManager::DronesManager() {
    first = NULL;
    last = NULL;
    size = 0;
}

DronesManager::~DronesManager() {
    DroneRecord* current = first;
    while (current) {
        current = first->next;
        delete first;
        first = current;
    }
}

bool operator==(const DronesManager::DroneRecord& lhs, const DronesManager::DroneRecord& rhs) {
    bool is_equal = false;
    if(lhs.batteryType == rhs.batteryType &&
    lhs.description == rhs.description &&
    lhs.droneID == rhs.droneID &&
    lhs.droneType == rhs.droneType &&
    lhs.manufacturer == rhs.manufacturer &&
    lhs.range == rhs.range &&
    lhs.yearBought == rhs.yearBought){
        is_equal = true;
    }
    return is_equal;
}

unsigned int DronesManager::get_size() const {
    return size;
}

bool DronesManager::empty() const {
    if (!first) {
        return true;
    }
    return false;
}

DronesManager::DroneRecord DronesManager::select(unsigned int index) const {
    if (!first) {
        return DroneRecord(0);
    } else if (index > size-1) {
        return DroneRecord(*last);
    } else {
        DroneRecord* temp = first;
        int i = 0;
        while (temp) {
            if (i == index) {
                return *temp;
            }
            temp = temp->next;
            ++i;
        }
        return DroneRecord(*temp);
    }
}

unsigned int DronesManager::search(DroneRecord value) const {
    if (!first) {
        return 0;
    } else {
        DroneRecord* temp = first;
        int index = 0;
        while (temp) {
            if (temp->droneID == value)
                return index;
            temp = temp->next;
            ++index;
        }
        return index;
    }
}

void DronesManager::print() const {
    cout << "(";
    DroneRecord* temp = first;
    while (temp) {
        cout << "[" << temp->droneID << ", " << temp->droneType << ", " << temp->description << ", "
        << temp->manufacturer << ", " << temp->batteryType << ", " << temp->yearBought << ", " << temp->range << "]";
        temp = temp->next;
        if (temp)
            cout << "->";
    }
    cout << ")\n";
}

bool DronesManager::insert(DroneRecord value, unsigned int index) {
    if (index > size) {
        return false;
    }
    if (!first) {
        DroneRecord* temp = new DroneRecord(value);
        first = temp;
        last = temp;
        temp->next = NULL;
        temp->prev = NULL;
        ++size;
    } else if (!first->next) {
        DroneRecord* temp = new DroneRecord(value);
        first->next = temp;
        temp->next = NULL;
        temp->prev = first;
        last = temp;
        ++size;
    } else if (index == size) {
        insert_back(value);
    } else if (index == 0) {
        insert_front(value);
    } else {
        DroneRecord* temp = first;
        for (int i = 0; i < index-1; ++i) {
            temp = temp->next;
        }
        DroneRecord* insert = new DroneRecord(value);
        temp->next->prev = insert;
        insert->prev = temp;
        insert->next = temp->next;
        temp->next = insert;
        ++size;
    }
    //++size;
    return true;
}

bool DronesManager::insert_front(DroneRecord value) {
    if (!first) {
        DroneRecord* temp = new DroneRecord(value);
        first = temp;
        last = first;
        temp->next = NULL;
        temp->prev = NULL;
        ++size;
        return true;
    } else {
        DroneRecord* temp = new DroneRecord(value);
        temp->next = first;
        temp->prev = NULL;
        first->prev = temp;
        first = temp;
        ++size;
        return true;
    }
}

bool DronesManager::insert_back(DroneRecord value) {
    if (!first) {
        first = new DroneRecord(value);
        first->next = NULL;
        first->prev = NULL;
        last = first;
        ++size;
        return true;
    } else {
        DroneRecord* temp = last;
        DroneRecord* insert = new DroneRecord(value);
        temp->next = insert;
        insert->prev = temp;
        insert->next = NULL;
        last = insert;
        ++size;
        return true;
    }
}

bool DronesManager::remove(unsigned int index) {
    if (!first || index > size-1) {
        return false;
    } else if (index == 0) {
        remove_front();
    } else if (index == size-1) {
        remove_back();
    } else {
        DroneRecord* temp = first;
        int i = 0;
        while (i < index) {
            temp = temp->next;
            i++;
        }
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        delete temp;
        --size;
    }
    //--size;
    return true;
}

bool DronesManager::remove_front() {
    if (!first) {
        return false;
    } else if (!first->next) {
        delete first;
        first = NULL;
        last = NULL;
    } else {
        DroneRecord* temp = first->next;
        delete temp->prev;
        first = temp;
        first->prev = NULL;
    }
    --size;
    return true;
}

bool DronesManager::remove_back() {
    if (!first) {
        return false;
    } else if (size == 1) {
        delete first;
        first = NULL;
        last = NULL;
        --size;
    } else {
        DroneRecord* temp = last->prev;
        delete (temp->next);
        temp->next = NULL;
        last = temp;
        --size;
    }
    //--size;
    return true;
}

bool DronesManager::replace(unsigned int index, DroneRecord value) {
    if (!first || index > size-1) {
        return false;
    } else {
        remove(index);
        insert(value, index);
        return true;
    }
}

bool DronesManager::reverse_list() {
    if (!first) {
        return false;
    } else if (!first->next) {
        return true;
    } else {
        DroneRecord* temp = first;
        DroneRecord* prev = NULL;
        DroneRecord* next = NULL;
        while (temp) {
            next = temp->next;
            temp->next = prev;
            prev = temp;
            temp = next;
        }
        first = prev;
        // pointer to last?
        return true;
    }
}

bool DronesManagerSorted::is_sorted_asc() const {
    if (!first) {
        return false;
    } else if (!first->next) {
        // return true;
    } else {
        DroneRecord* temp = first;
        while (temp->next != NULL) {
            if (temp->droneID > temp->next->droneID) {
                return false;
            }
            temp = temp->next;
        }
    }
    return true;
}

bool DronesManagerSorted::is_sorted_desc() const {
    if (!first) {
        return false;
    } else if (!first->next) {
        // return true;
    } else {
        DroneRecord* temp = first;
        while (temp->next != NULL) {
            if (temp->droneID < temp->next->droneID) {
                return false;
            }
            temp = temp->next;
        }
    }
    return true;
}

bool DronesManagerSorted::insert_sorted_asc(DroneRecord val) {/*
    DroneRecord* temp = new DroneRecord(val);
    if (!first) {
        first = new DroneRecord(val);
        ++size;
        return true;
    } else if (!first->next) {
        if (first->droneID < temp->droneID) {
            first->next = temp;
            temp->prev = first;
            last = temp;
        } else {
            first->prev = temp;
            temp->next = first;
            last = first;
            first = temp;
        }
        ++size;
        return true;
    } else if (!is_sorted_asc()) {
        return false;
    } else {
        DroneRecord* temp = first;
        int index = 0;
        while (temp) {
            temp = temp->next;
            ++index;
        }
        insert(val, index);
        /*DroneRecord* temp2 = first;
        while (temp2) {
            if (temp2->droneID < temp->droneID) {
                temp2->next = temp;
                temp->prev = temp2;
                temp2 = temp->next;
                temp2->prev = temp;
                temp->next = temp2;
            }
            temp = temp->next;
            temp2 = temp2->next;
        }
        ++size;
        return true;
    }
                                                               */return true;}

bool DronesManagerSorted::insert_sorted_desc(DroneRecord val) {/*
    DroneRecord* temp = new DroneRecord(val);
    if (!first) {
        first = new DroneRecord(val);
        ++size;
        return true;
    } else if (!first->next) {
        if (first->droneID > temp->droneID) {
            first->next = temp;
            temp->prev = first;
            last = temp;
        } else {
            first->prev = temp;
            temp->next = first;
            last = first;
            first = temp;
        }
        ++size;
        return true;
    } else if (!is_sorted_desc()) {
        return false;
    } else {
        DroneRecord* temp2 = last;
        while (temp2) {
            if (temp2->droneID > temp->droneID) {
                temp2->next = temp;
                temp->prev = temp2;
                temp2 = temp->next;
                temp2->prev = temp;
                temp->next = temp2;
            }
            temp = temp->prev;
            temp2 = temp2->prev;
        }
        ++size;
        return true;
    }
                                                                */ return true;}

void DronesManagerSorted::sort_asc() {
    if (!first || !first->next) {
        // size is zero or one
    } else {
        int swapped;
        do {
            swapped = 0;
            DroneRecord* temp = first;
            while (temp->next) {
                if (temp->droneID > temp->next->droneID) {
                    swap(temp, temp->next);
                    swapped = 1;
                }
                temp = temp->next;
            }
            // temp2 = temp;
        }
        while (swapped);
    }
}

void DronesManagerSorted::sort_desc() {
    if (!first || !first->next) {
        // size is zero or one
    } else {
        int swapped;
        do {
            swapped = 0;
            DroneRecord* temp = first;
            while (temp->next) {
                if (temp->droneID < temp->next->droneID) {
                    swap(temp, temp->next);
                    swapped = 1;
                }
            }
        }
        while(swapped);
    }
}
