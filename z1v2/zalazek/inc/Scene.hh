#ifndef SCENE_HH
#define SCENE_HH

#include "MobileObj.hh"
#include <string>
#include <map>
#include <iostream>

using std::shared_ptr;
using std::map;
using std::string;

// Objects map -> Uporządkowana(po nazwach) struktura, przechowująca obiekty(shared_ptr)
typedef map<string, shared_ptr<MobileObj>> Objects_map;

class Scene{  
  string _Name{"Nameless map"};
  
public:

  Scene(){};
  Scene(string t_name){
    _Name = t_name;
  }

  const string GetName(){
    return _Name;
  }
  
  //   std::map<std::string, MobileObj*> _Lst_MobileObjs;
  /*!
   * \brief Mapa przechowująca utworzone obiekty wedłu ich nazwy
   */
  Objects_map _Set_MobileObjs;


  
  /*!
   * \brief Zwraca metode na obiekt modyfikowalny
   */
  MobileObj* FindMobileObj(const char *sName);

  /*!
   * \brief Metoda umożliwiająca dodanie obiektu do sceny. 
   */
  void AddMobileObj(shared_ptr<MobileObj> &pMobObj){
    _Set_MobileObjs.insert(std::pair<string, shared_ptr<MobileObj>>(pMobObj->GetName(), pMobObj));

    std::cout << "Added object: " << pMobObj->GetName() << " to scene: "
	      << _Name  << std::endl;
  }
};

#endif
