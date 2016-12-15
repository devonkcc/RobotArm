/*----------------------------------------------------------------------------
 * Name:        position_list.h
 * Description: Short description
 * Note(s):     Definitions and information
 *
 *----------------------------------------------------------------------------*/

#include <stdbool.h>
#include <Arduino.h>

#ifndef __POSITION_LIST__
#define __POSITION_LIST__

typedef struct {
  float gripper_pos;
  float wrist_pos;
  float elbow_pos;
  float shoulder_pos;
  float base_pos;
} coordinate_t;

class position_list_t
{
  private:
    struct node
    {
        node(coordinate_t val);
        node* next;
        coordinate_t value;
    };
    
    // Member Varialbes
    node* head_;
    node* tail_;
    int size_;
        
  public:
  
    // Constructor/Desctructor
    position_list_t();
    ~position_list_t();
    
    //  Accessors:
    int size() const;
    bool empty() const;
    node* get_node(int index) const;
    coordinate_t get_coord(int index) const;
  
    //  Mutators:
    void clear();
    bool insert(int index, coordinate_t val);
    bool insert_front(coordinate_t val);
    bool insert_back(coordinate_t val);
    bool remove(int index);
    bool remove_front();
    bool remove_back();
    bool replace(int index, coordinate_t val);
    
};

#endif __POSITION_LIST__
