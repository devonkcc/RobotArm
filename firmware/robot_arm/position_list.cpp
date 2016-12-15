/*----------------------------------------------------------------------------
 * Name:        position_list.cpp
 * Description: Data structure to manage the LEDs
 * Note(s):
 *
 *----------------------------------------------------------------------------*/

#include "position_list.h"

/*----------------------------------------------------------------------------
 Functions
 *----------------------------------------------------------------------------*/

position_list_t::node::node(coordinate_t val) {
    next = NULL;
    value = val;
}

position_list_t::position_list_t() {
    head_ = NULL;
    tail_ = NULL;
    size_ = 0;
}

position_list_t::~position_list_t() {
    if ( head_ != NULL)
    {
        node* temp = head_;
        while(head_ != NULL)
        {
            temp = head_->next;
            delete head_;
            head_ = temp;
        }
        tail_ = NULL;
    }
}

void position_list_t::clear() {
  if ( head_ != NULL)
  {
    node* temp = head_;
    while(head_ != NULL)
    {
      temp = head_->next;
      delete head_;
      head_ = temp;
    }
    tail_ = NULL;
    size_ = 0; 
  }
}


int position_list_t::size() const {
    return size_;
}

bool position_list_t::empty() const {
    if (size_ == 0) return true;
    return false;
}

position_list_t::node* position_list_t::get_node(int index) const {
    if (index > size_-1) return NULL;
    node* temp = head_;
    for (int i = 0; i < index; i++)
    {
        temp = temp->next;
    }
    return temp;
}

coordinate_t position_list_t::get_coord(int index) const {
  return get_node(index)->value;
}

bool position_list_t::insert(int index, coordinate_t val) {
    if (index > size_ || index < 0) return false;
    
    node* newnode = new node(val);
    if (empty())
    {
        head_ = newnode;
        tail_ = newnode;
        newnode->next = NULL;
    }
    else if (index == 0)
    {
        newnode->next = head_;
        head_ = newnode;
    }
    else
    {
        node* temp = get_node(index-1);
        temp->next = newnode;
        newnode->next = temp->next->next;
    }
    
    size_++;
    return true;
}

bool position_list_t::insert_front(coordinate_t val) {
    return insert(0, val);
}

bool position_list_t::insert_back(coordinate_t val) {
    return insert(size_, val);
}

bool position_list_t::remove(int index) {
    if (index >= size_ || index < 0) return false;
    else if (size_ == 1)
    {
        delete head_;
        head_ = NULL;
        tail_ = NULL;
    }
    else if (index == 0)
    {
        node* temp = head_;
        head_ = head_->next;
        delete temp;
        
    }
    else if (index == size_-1)
    {
        node* temp = get_node(size_-2);
        temp->next = NULL;
        delete tail_;
        tail_ = temp;
    }
    else
    {
        node* temp = get_node(index-1);
        node* remove = temp->next;
        temp->next = remove->next;
        delete remove;
    }
    
    size_--;
    return true;
}

bool position_list_t::remove_front() {
    return remove(0);
}

bool position_list_t::remove_back() {
    return remove(size_-1);
}

bool position_list_t::replace(int index, coordinate_t val) {
    if (index >= size_ || index < 0) return false;
    get_node(index)->value = val;
    return true;
}



