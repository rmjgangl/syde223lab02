#ifndef lab2_drones_manager_test_h
#define lab2_drones_manager_test_h

#include "lab2_drones_manager.h"

#define ASSERT_TRUE(T) if (!(T)) return false;
#define ASSERT_FALSE(T) if ((T)) return false;

class DronesManagerTest {
public:
    // PURPOSE: New empty list is valid
    bool test1() {
        DronesManager manager;
        ASSERT_TRUE(manager.get_size() == 0)
        ASSERT_TRUE(manager.empty() == true)
        ASSERT_TRUE(manager.first == NULL)
        ASSERT_TRUE(manager.last == NULL)
        return true;
    }
    
    // PURPOSE: insert_front() and insert_back() on zero-element list
    bool test2() {
        DronesManager manager1, manager2;
        manager1.insert_front(DronesManager::DroneRecord(100));
        manager2.insert_back(DronesManager::DroneRecord(100));
        
        ASSERT_TRUE(manager1.get_size() == manager2.get_size() && manager1.get_size() == 1)
        ASSERT_TRUE(manager1.first != NULL && manager1.first == manager1.last)
        ASSERT_TRUE(manager2.first != NULL && manager2.first == manager2.last)
        ASSERT_TRUE(manager1.first->prev == NULL && manager1.last->next == NULL)
        ASSERT_TRUE(manager2.first->prev == NULL && manager2.last->next == NULL)
        ASSERT_TRUE(manager1.select(0) == manager2.select(0) && manager1.select(0) == DronesManager::DroneRecord(100))
        return true;
    }
    
    // PURPOSE: select() and search() work properly
    bool test3() {
        DronesManager manager;
        
        const int size = 7;
        for (int i = 0; i < size; i++) {
            ASSERT_TRUE(manager.insert_front(DronesManager::DroneRecord(i)))
        }
        
        unsigned int index = 2;
        ASSERT_TRUE(manager.select(index) == size-index-1)
        ASSERT_FALSE(manager.select(size+1) == true)
        ASSERT_FALSE(manager.select(-4) == true)
        
        ASSERT_TRUE(manager.search(0) == abs(size-1))
        ASSERT_TRUE(manager.search(6) == 0)
        
        for (int i = 0; i < size; i++) {
            ASSERT_TRUE(manager.search(i) == abs(size-i-1))
        }

        ASSERT_TRUE(manager.first->prev == NULL && manager.last->next == NULL)
        return true;
    }
    
    // PURPOSE: remove_front() and remove_back() on one-element list
    bool test4 () {
        DronesManager manager;
        ASSERT_FALSE(manager.remove_back())
        ASSERT_TRUE(manager.insert(DronesManager::DroneRecord(42), 0))
        ASSERT_FALSE(manager.insert(DronesManager::DroneRecord(5), 4))
        ASSERT_TRUE(manager.remove_front())
        ASSERT_TRUE(manager.first == NULL && manager.last == NULL)
        ASSERT_TRUE(manager.get_size() == 0 && manager.empty() == 1)
        
        ASSERT_FALSE(manager.remove_front())
        ASSERT_TRUE(manager.insert_back(DronesManager::DroneRecord(100)))
        ASSERT_TRUE(manager.remove_back())
        ASSERT_TRUE(manager.first == NULL && manager.last == NULL)
        ASSERT_TRUE(manager.get_size() == 0 && manager.empty() == 1)
        
        return true;
    }
    
    // PURPOSE: replace() and reverse_list() work properly
    bool test5 () {
        DronesManager manager;
        const int size = 6;
        for (int i = 0; i < size; i++) {
            ASSERT_TRUE(manager.insert_back(DronesManager::DroneRecord(i)))
        }
        
        ASSERT_TRUE(manager.replace(0, DronesManager::DroneRecord(3)))
        ASSERT_TRUE(manager.replace(3, DronesManager::DroneRecord(42)))
        ASSERT_FALSE(manager.replace(8, DronesManager::DroneRecord(100)))
        ASSERT_FALSE(manager.replace(-2, DronesManager::DroneRecord(0)))
        ASSERT_TRUE(manager.replace(5, DronesManager::DroneRecord(6)))
        ASSERT_TRUE(manager.replace(5, DronesManager::DroneRecord(6)))
        ASSERT_TRUE(manager.replace(4, DronesManager::DroneRecord(7)))
        
        ASSERT_TRUE(*manager.first == DronesManager::DroneRecord(3))
        ASSERT_TRUE(*manager.last == DronesManager::DroneRecord(6))
        ASSERT_TRUE(*(manager.last->prev->prev) == DronesManager::DroneRecord(42))
        
        int test_values[size] = {6, 7, 42, 2, 1, 3};
        ASSERT_TRUE(manager.reverse_list());
        for (int i = 0; i < size; i++) {
            ASSERT_TRUE(manager.select(i) == DronesManager::DroneRecord(test_values[i]));
        }
        ASSERT_TRUE(manager.first->prev == NULL && manager.last->next == NULL)
        
        return true;
    }
    
    // PURPOSE: insert_front() keeps moving elements forward
    bool test6 () {
        DronesManager manager;
        const int size = 7;
        for (int i = 0; i < size; i++) {
            ASSERT_TRUE(manager.insert_front(DronesManager::DroneRecord(i)))
            ASSERT_TRUE(manager.get_size() == (i+1))
            ASSERT_TRUE(*manager.first == DronesManager::DroneRecord(i))
            
            DronesManager::DroneRecord* temp = manager.first;
            for (int j = 0; j <= i; j++) {
                DronesManager::DroneRecord value = DronesManager::DroneRecord(i - j);
                ASSERT_TRUE(temp && *temp == value)
                temp = temp->next;
            }
        }
        ASSERT_TRUE(manager.first->prev == NULL && manager.last->next == NULL)
        return true;
    }
    
    // inserting at different positions in the list
    bool test7() {
        DronesManager manager;
        for (int i = 0; i < 4; i++) {
            ASSERT_TRUE(manager.insert_back(DronesManager::DroneRecord(i)))
        }
        ASSERT_TRUE(manager.insert(DronesManager::DroneRecord(4), 1))
        ASSERT_TRUE(manager.insert(DronesManager::DroneRecord(5), 1))
        ASSERT_TRUE(manager.insert(DronesManager::DroneRecord(6), 5))
        ASSERT_TRUE(manager.insert(DronesManager::DroneRecord(7), 7))
        
        // Check that the list has the right values
        int expected_values[] = {0, 5, 4, 1, 2, 6, 3, 7};
        ASSERT_TRUE(manager.get_size() == 8) // fails here
        DronesManager::DroneRecord* n = manager.first;
        for (int i = 0; i < manager.get_size(); i++) {
            ASSERT_TRUE(n != NULL && *n == DronesManager::DroneRecord(expected_values[i]))
            n = n->next;
        }
        ASSERT_TRUE(manager.first->prev == NULL && manager.last->next == NULL)
        return true;
    }
    
    // try to remove too many elements, then add a few elements
    bool test8() {
        DronesManager manager;
        for (int i = 0; i < 4; i++) {
            ASSERT_TRUE(manager.insert_back(DronesManager::DroneRecord(i)))
        }
        
        for (int i = 0; i < 4; i++) {
            ASSERT_TRUE(manager.remove_back())
        }
        
        // Try a bunch of invalid commands.
        ASSERT_FALSE(manager.remove_front())
        ASSERT_FALSE(manager.remove_front())
        ASSERT_FALSE(manager.remove(0))
        ASSERT_TRUE(manager.empty() && manager.get_size() == 0)
        
        int expected_value = 1234;
        ASSERT_TRUE(manager.insert(DronesManager::DroneRecord(expected_value), 0))
        ASSERT_TRUE(*manager.first == DronesManager::DroneRecord(expected_value) &&
                    *manager.last == DronesManager::DroneRecord(expected_value))
        
        ASSERT_TRUE(manager.first->prev == NULL && manager.last->next == NULL)
        ASSERT_TRUE(manager.first == manager.last)
        return true;
    }
    
    // lots of inserts and deletes, some of them invalid
    bool test9() {
        DronesManager manager;
        ASSERT_FALSE(manager.remove(0))
        ASSERT_TRUE(manager.insert_back(DronesManager::DroneRecord(32)))
        ASSERT_TRUE(manager.insert_front(DronesManager::DroneRecord(44)))
        ASSERT_FALSE(manager.insert(DronesManager::DroneRecord(12),3))
        ASSERT_TRUE(manager.insert(DronesManager::DroneRecord(12),2))
        ASSERT_TRUE(manager.remove_back())
        ASSERT_FALSE(manager.remove(5))
        ASSERT_TRUE(manager.remove_front())
        ASSERT_TRUE(manager.insert_back(DronesManager::DroneRecord(88)))
        ASSERT_FALSE(manager.insert(DronesManager::DroneRecord(12345),6))
        ASSERT_TRUE(manager.remove(1))
        ASSERT_TRUE(manager.insert(DronesManager::DroneRecord(99),0))
        
        // Check that the manager has the right values
        ASSERT_TRUE(manager.select(0) == DronesManager::DroneRecord(99) && *manager.first == DronesManager::DroneRecord(99))
        ASSERT_TRUE(manager.select(1) == DronesManager::DroneRecord(32) && *manager.last == DronesManager::DroneRecord(32))
        
        ASSERT_TRUE(manager.first->next == manager.last && manager.last->prev == manager.first)
        ASSERT_TRUE(manager.first->prev == NULL && manager.last->next == NULL)
        
        return true;
    }
    
    // inserts into an unsorted list, then sort the list
    bool test10() {
        DronesManagerSorted manager;
        ASSERT_TRUE(manager.insert_back(DronesManager::DroneRecord(25)))
        ASSERT_TRUE(manager.insert_front(DronesManager::DroneRecord(45)))
        ASSERT_FALSE(manager.insert_sorted_asc(DronesManager::DroneRecord(25)))
        ASSERT_TRUE(manager.insert(DronesManager::DroneRecord(11),2))
        ASSERT_TRUE(manager.insert(DronesManager::DroneRecord(15),2))
        ASSERT_FALSE(manager.insert_sorted_asc(DronesManager::DroneRecord(35)))
        ASSERT_TRUE(manager.insert(DronesManager::DroneRecord(72),2))
        ASSERT_FALSE(manager.is_sorted_asc())
        manager.sort_asc();
        ASSERT_TRUE(manager.is_sorted_asc())
        
        DronesManagerSorted manager2;
        ASSERT_TRUE(manager2.insert_back(DronesManager::DroneRecord(22)))
        ASSERT_TRUE(manager2.insert_front(DronesManager::DroneRecord(11)))
        ASSERT_FALSE(manager2.insert_sorted_desc(DronesManager::DroneRecord(25)))
        ASSERT_TRUE(manager2.insert(DronesManager::DroneRecord(55),2))
        ASSERT_TRUE(manager2.insert(DronesManager::DroneRecord(31),2))
        ASSERT_FALSE(manager2.insert_sorted_desc(DronesManager::DroneRecord(35)))
        ASSERT_TRUE(manager2.insert(DronesManager::DroneRecord(14),2))
        
        ASSERT_FALSE(manager2.is_sorted_desc())
        manager2.sort_desc();
        ASSERT_TRUE(manager2.is_sorted_desc())
        
        return true;
    }
    
    bool test11() {
        DronesManagerSorted manager;
        
        ASSERT_TRUE(manager.insert_sorted_asc(DronesManager::DroneRecord(2)))
        ASSERT_TRUE(manager.insert_sorted_asc(DronesManager::DroneRecord(1)))
        ASSERT_TRUE(manager.insert_sorted_asc(DronesManager::DroneRecord(7)))
        ASSERT_TRUE(manager.insert_sorted_asc(DronesManager::DroneRecord(25)))
        ASSERT_TRUE(manager.insert_sorted_asc(DronesManager::DroneRecord(11)))
        ASSERT_TRUE(manager.insert_sorted_asc(DronesManager::DroneRecord(3)))
        ASSERT_TRUE(manager.insert_sorted_asc(DronesManager::DroneRecord(4)))
        ASSERT_TRUE(manager.insert_sorted_asc(DronesManager::DroneRecord(5)))
        ASSERT_TRUE(manager.insert_sorted_asc(DronesManager::DroneRecord(6)))
        ASSERT_TRUE(manager.insert_sorted_asc(DronesManager::DroneRecord(1)))
        
        ASSERT_TRUE(manager.select(0) == DronesManager::DroneRecord(1) && *manager.first == DronesManager::DroneRecord(1));
        //ASSERT_TRUE(manager.select(9) == DronesManager::DroneRecord(25) && *manager.last == DronesManager::DroneRecord(25));
        
        ASSERT_TRUE(manager.remove_back())
        ASSERT_TRUE(manager.remove_back())
        //ASSERT_TRUE(manager.remove_back())
        ASSERT_TRUE(manager.remove_front())
        //ASSERT_TRUE(manager.remove_front())
        //ASSERT_TRUE(manager.remove_front())
        ASSERT_TRUE(manager.insert_sorted_asc(DronesManager::DroneRecord(0)))
        
        ASSERT_TRUE(manager.select(0) == DronesManager::DroneRecord(0) && *manager.first == DronesManager::DroneRecord(0));
        //ASSERT_TRUE(manager.select(4) == DronesManager::DroneRecord(6) && *manager.last == DronesManager::DroneRecord(6));
        
        return true;
    }
    
    //insert and remove into sorted manager in descending order
    bool test12() {
        DronesManagerSorted manager;
        
        ASSERT_TRUE(manager.insert_sorted_desc(DronesManager::DroneRecord(3)))
        ASSERT_TRUE(manager.insert_sorted_desc(DronesManager::DroneRecord(4)))
        ASSERT_TRUE(manager.insert_sorted_desc(DronesManager::DroneRecord(5)))
        ASSERT_TRUE(manager.insert_sorted_desc(DronesManager::DroneRecord(25)))
        ASSERT_TRUE(manager.insert_sorted_desc(DronesManager::DroneRecord(11)))
        ASSERT_TRUE(manager.insert_sorted_desc(DronesManager::DroneRecord(2)))
        ASSERT_TRUE(manager.insert_sorted_desc(DronesManager::DroneRecord(1)))
        ASSERT_TRUE(manager.insert_sorted_desc(DronesManager::DroneRecord(7)))
        ASSERT_TRUE(manager.insert_sorted_desc(DronesManager::DroneRecord(6)))
        ASSERT_TRUE(manager.insert_sorted_desc(DronesManager::DroneRecord(1)))
        
        ASSERT_TRUE(manager.select(0) == DronesManager::DroneRecord(25) && *manager.first == DronesManager::DroneRecord(25));
        //ASSERT_TRUE(manager.select(9) == DronesManager::DroneRecord(1) && *manager.last == DronesManager::DroneRecord(1));
        
        ASSERT_TRUE(manager.remove_back())
        ASSERT_TRUE(manager.remove_back())
        ASSERT_TRUE(manager.remove_back())
        ASSERT_TRUE(manager.remove_front())
        ASSERT_TRUE(manager.remove_front())
        ASSERT_TRUE(manager.remove_front())
        ASSERT_TRUE(manager.insert_sorted_desc(DronesManager::DroneRecord(0)))
        
        ASSERT_TRUE(manager.select(0) == DronesManager::DroneRecord(6) && *manager.first == DronesManager::DroneRecord(6));
        //ASSERT_TRUE(manager.select(4) == DronesManager::DroneRecord(0) && *manager.last == DronesManager::DroneRecord(0));
        
        return true;
    }
};

#endif /* lab2_drones_manager_test_h */
