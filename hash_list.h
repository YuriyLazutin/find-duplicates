#ifndef HASH_LIST_H
#define HASH_LIST_H

#include <map>

template <class key_t, class obj_t>
class hash_list
{
    std::map<key_t, obj_t> hlst;
  public:
    explicit hash_list();
    ~hash_list();
    void put(const key_t p_key, const obj_t p_obj);
    obj_t get(const key_t p_key) const;
};

#endif // HASH_LIST_H
