#ifndef  LIBINTERFACE_HH
#define  LIBINTERFACE_HH

#include <string>
#include <sstream>
#include <cassert>

#include "Interp4Command.hh"

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

  bool ReadParams(std::istream &IStrm){
    return _pCreateCmd()->ReadParams(IStrm);}
  
  void PrintCmd(){
    _pCreateCmd()->PrintCmd();}
  
  
  // TODO: Konstruktor który tworzy biblioteki i sprawdzi poprawność komend.
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
   * \brief Przypisanie nazwy polecenia do interfejsu
   */
  const std::string GetCmdName(){
    return _CmdName;
  }

};

#endif
