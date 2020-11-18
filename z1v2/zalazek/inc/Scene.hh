#ifndef SCENE_HH
#define SCENE_HH

#include "MobileObj.hh"

class Scene{
public:
  std::map<string, MobileObj*> _Lst_MobileObjs;

  /*!
   * \brief Zwraca metode na obiekt modyfikowalny
   */
  MobileObj* FindMobileObj(const char *sName);
  void AddMobileObj(MobileObj *pMobObj);
};
