#ifndef SCENE_HH
#define SCENE_HH

#include "MobileObj.hh"
#include <string>
#include <map>
#include <iostream>
#include "AccessControl.hh"

using std::shared_ptr;
using std::map;
using std::string;

// Liczba sekwencji
#define STATES_NUMBER 5

// Przykladowa sekwencja dla obiektu
const char* Cmds4Obj1[STATES_NUMBER] = {
  "Cube  2 2.5 1.1  0 0 0  0 0 0  0 0 255\n",
  "Cube  2 2.5 1.1  0 0 1   5 0 0  0 0 255\n",
  "Cube  2 2.5 1.1  0 0 2  10 0 0  0 0 255\n",
  "Cube  2 2.5 1.1  0 0 2  15 0 0  0 0 255\n",
  "Cube  2 2.5 1.1  0 0 2  20 0 0  0 0 255\n"
 };

///////////////////////////////////////////////////////////////////////////////
// KLASA NA CZAS TESTOW

class GeomObject {
  /*!
   * \brief Identyfikuje aktualny stan obiektu.
   *
   * Identyfikuje aktualny stan obiektu. Indeks ten pozwala
   * na wybór z tablicy \link GeomObject::_Cmd4StatDesc _Cmd4StatDesc\endlink
   * odpowiedniego polecenia dla serwera, które reprezentuje aktualne
   * położenie i orientację obiektu.
   */
   int _StateIdx = 0;
  /*!
   * \brief Zestaw sekwencji poleceń symulujących ruch obiektu.
   *
   * Zestaw sekwencji poleceń symulujących ruch obiektu.
   * Każde polecenie odpowiada kolejnym stanom obiektu.
   */
   const char** _Cmd4StatDesc = nullptr;
  
 public:

  /*!
   * \brief Ustawia zestaw poleceń odpowiadających kolejnym stanom
   *        obiektu.
   */
  void SetCmds(const char *CmdsTab[STATES_NUMBER]) { _Cmd4StatDesc = CmdsTab; }
  /*!
   * \brief Udostępnia kolejny zestaw poleceń umożliwiających
   *        zespołu obiektu.
   *
   * Udostępnia kolejny zestaw poleceń umożliwiających
   * zespołu obiektu. Ta metoda "udaje" metodę, która w oryginalnym
   * rozwiązaniu powinna wygenerować odpowiednie polecenie na podstawie
   * przechowywanej informacji o położeniu i orientacji obiektu.
   */
  const char* GetStateDesc() const
  {
    return _Cmd4StatDesc[_StateIdx];
  }
  /*!
   * \brief Zwiększa indeks stanu, o ile aktualny opis nie jest pusty.
   *
   *  Zwiększa indeks stanu, o ile aktualny opis nie jest pusty.
   *  Ta metoda "udaje" metodę, która w oryginalnym rozwiązaniu
   *  jest odpowiedzialna za zmianę stanu obiektu, tzn. zmianę jego
   *  położenia lub orientacji.
   */
  bool IncStateIndex() {
    if (_StateIdx >= STATES_NUMBER-1) return false;
    ++_StateIdx;
    return true;
  }
};

// KLASA NA CZAS TESTOW
///////////////////////////////////////////////////////////////////////////////

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
class Scene: public AccessControl{
  /*!
   * \brief Nazwa sceny
   */
  string _Name{"Nameless map"};
  
public:

  

  /*!
   * \brief Domyślny konstruktor sceny
   */
  //  Scene(){};

  /*!
   * \brief Konstruktor domyslny dedykowany dla polaczenia z serwerem
   * Potrzeba dodania geomObj
   */
  Scene(): _Container4Objects(1)
  {
    _Container4Objects[0].SetCmds(Cmds4Obj1);
    //_Container4Objects[1].SetCmds(Cmds4Obj2);
    //_Container4Objects[2].SetCmds(Cmds4Obj3);
  }

  

  /*!
   * \brief Konstruktor sceny nadający nazwę
   * \param[in] t_name Nazwa sceny
   */
  Scene(string t_name){
    _Name = t_name;
  }

  // Zbior obiektow
  std::vector<GeomObject>   _Container4Objects;
  
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
