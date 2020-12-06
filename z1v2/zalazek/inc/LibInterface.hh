#ifndef  LIBINTERFACE_HH
#define  LIBINTERFACE_HH

#include <string>
#include <sstream>
#include <cassert>

#include "Interp4Command.hh"
/*!
 * \file
 * \brief Definicja klasy LibInterface
 *
 * Plik zawiera definicję klasy LibInterface
 */

/*!
 * \brief Modeluje interfejs dla bibliotekki
 *
 *  Klasa modeluje interfaejs dla biblioteki
 */

class LibInterface{
  /*! 
   * \brief Uchwyt do biblioteki
   */
  void* _LibHandler;

  /*!
   * \brief Nazwa polecenia, słuąca do identyfikacji potrzebnej biblioteki
   */
  std::string _CmdName;

  /*!
   * \brief Wkażnik do obiektu, klasy zawierającej metody do obsługi wtyczek.
   * Do metod tego obiektu odwołuje się interfejs.
   */
  Interp4Command *(*_pCreateCmd)(void);
  
public:

  /*!
   * \brief Umożliwia odczytanie parametrów i zapis paramertów polecenia
   * \param[in] IStrm  Strumień wejścia, czytanie z pliku
   */
  bool ReadParams(std::istream &IStrm){
    return _pCreateCmd()->ReadParams(IStrm);}


  /*!
   * \brief Wyświetlenie polecenia i parametrów
   */
  void PrintCmd(){
    _pCreateCmd()->PrintCmd();}
  
  
  // TODO: Konstruktor który tworzy biblioteki i sprawdzi poprawność komend.
  /*!
   * \brief Konstruktor klasy dziękipodanej nazwie, konstruktor sprawdza czy
   * biblioteka istnieje, jeśli tak, to przypisuje ją do uchwytu.
   * Przez dany uchwyt zostaje utworzone polecenie i przypisanie nazwy komendy.
   * \param[in] t_libName  Nazwa biblioteki
   */
  LibInterface(const std::string t_libName){
    void *pFun;
    
    this->_LibHandler = dlopen(t_libName.c_str(), RTLD_LAZY);
    if(!(this->_LibHandler)) {
      std::cerr << "!!! Brak biblioteki !!!" << std::endl;
    }

    pFun = dlsym(this->_LibHandler,"CreateCmd");
    if (!pFun) {
      std::cerr << "!!! Nie znaleziono funkcji CreateCmd" << std::endl;
    }
    
    _pCreateCmd = * reinterpret_cast<Interp4Command* (**)(void)>(&pFun);
    this->_CmdName = _pCreateCmd()->GetCmdName();
  }
  

  
  /*!
   * \brief Zwraca nazwę polecenia
   */
  const std::string GetCmdName(){
    return _CmdName;
  }

};

#endif
