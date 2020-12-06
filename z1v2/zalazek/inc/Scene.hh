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

/*!
 * \file
 * \brief Definicja klasy Scene
 *
 * Plik zawiera definicję klasy Scene
 */

/*!
 * \brief Modeluje scenę, przestrzeń zdarzeń.
 *
 *  Klasa modeluje scene na której umieszczone są obiekty.
 */
class Scene{
  /*!
   * \brief Nazwa sceny
   */
  string _Name{"Nameless map"};
  
public:

  /*!
   * \brief Domyślny konstruktor sceny
   */
  Scene(){};

  /*!
   * \brief Konstruktor sceny nadający nazwę
   * \param[in] t_name Nazwa sceny
   */
  Scene(string t_name){
    _Name = t_name;
  }

  /*!
   * \brief Zwraca nazwę sceny
   */
  const string GetName(){
    return _Name;
  }
  
  /*!
   * \brief Mapa przechowująca utworzone obiekty. Kluczem jest nazwa
   */
  Objects_map _Set_MobileObjs;
  
  /*!
   * \brief Zwraca metode na obiekt modyfikowalny
   * \param[in] sName  Nazwa szukanego obiektu
   */
  MobileObj* FindMobileObj(const char *sName);

  /*!
   * \brief Metoda umożliwiająca dodanie obiektu do mapy i sceny. 
   * \param[in] pMobObj  Dodawany obiek klasy MobileObj
   */
  void AddMobileObj(shared_ptr<MobileObj> &pMobObj){
    _Set_MobileObjs.insert(std::pair<string, shared_ptr<MobileObj>>(pMobObj->GetName(), pMobObj));

    std::cout << "Added object: " << pMobObj->GetName() << " to scene: "
	      << _Name  << std::endl;
  }
};

#endif
