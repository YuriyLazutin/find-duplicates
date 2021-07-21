#include "hash_list.h"
#include <list>
#include <string>

template <class key_t, class obj_t>
hash_list<key_t, obj_t>::hash_list()
{

}

template <class key_t, class obj_t>
void hash_list<key_t, obj_t>::put(const key_t p_key, const obj_t p_obj)
{
  typename std::map<key_t, obj_t>::iterator i;
  i = hlst.find(p_key);

  if (i == hlst.end())
    std::list<obj_t> *obj_lst = new std::list<obj_t>;
    obj_lst->push_back(p_obj);
    //hlst.insert( pair<key_t, std::list<obj_t> > (p_key, obj_lst) );
    hlst.insert( pair<key_t, list<obj_t> > (p_key, std::list<obj_t>(p_obj)) );
  else
    i->second.push_back(p_obj);
}
