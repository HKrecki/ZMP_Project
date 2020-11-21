#ifndef SCENE_HH
#define SCENE_HH

#include "MobileObj.hh"

// TODO: tepedef for map of mobileObj's

class Scene{
public:
  std::map<std::string, MobileObj*> _Lst_MobileObjs;

  /*!
   * \brief Zwraca metode na obiekt modyfikowalny
   */
  MobileObj* FindMobileObj(const char *sName);
  void AddMobileObj(MobileObj *pMobObj);
};

#endif
