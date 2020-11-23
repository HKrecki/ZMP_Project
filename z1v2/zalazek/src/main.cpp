#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include <sstream>
#include <cstdio>
#include <memory>
#include "Interp4Command.hh"
#include "Set4LibInterfaces.hh"
#include "Scene.hh"
#include "MobileObj.hh"


#define LINE_SIZE 500

using namespace std;

/************************************************************************/

bool ExecProcessor( const char *NazwaPliku, istringstream &IStrm4Cmds ){
  string Cmd4Preproc = "cpp -P ";
  char Line[LINE_SIZE];
  ostringstream OTmpStrm;

  Cmd4Preproc += NazwaPliku;
  FILE* pProc = popen(Cmd4Preproc.c_str(), "r");

  if (!pProc) return false;

  while(fgets(Line,LINE_SIZE,pProc)){
    OTmpStrm << Line;
  }

  IStrm4Cmds.str(OTmpStrm.str());

  return pclose(pProc) == 0;
}

/************************************************************************/

bool ExecActions_v1(istream &rIStrm, Interp4Command &rInterp){
  if(!rInterp.ReadParams(rIStrm)) return false;

  cout << "--------------- Parametry ---------------" << endl;
  rInterp.PrintCmd();

  return true;
}

/************************************************************************/

bool ExecActions(istream &rIStrm, Set4LibInterfaces t_plugins){

  // TODO1: Otwarcie bibliotek poza funkcją, w main
  // TODO2: Przeszukiwanie mapy pluginów, przekazanej jako t_plugins
  
  string aux;
  shared_ptr<LibInterface> auxInterface;
  void *pFun;
  void *pLibHnd;
  Interp4Command *(*pCreateCmd)(void);

  string libName;

  rIStrm >> aux;
  
  if (t_plugins.Find(aux.c_str(), auxInterface)){
    cout << endl;
    cout << "Found command: " << aux.c_str() << endl;
    libName = "libInterp4" + aux + ".so";
    
    pLibHnd = dlopen(libName.c_str(), RTLD_LAZY);    
  }
  else
    return false;

  pFun = dlsym(pLibHnd, "CreateCmd");
  pCreateCmd = *reinterpret_cast<Interp4Command* (**)(void)>(&pFun);
  Interp4Command *pCmd = pCreateCmd();

  if(!(pCmd->ReadParams(rIStrm)))
    return false;

  cout << "----- Parameters -----" << endl;
  pCmd->PrintCmd();
  cout << endl;

  
  delete pCmd;
  dlclose(pLibHnd);
  
  return true;  
}


/************************************************************************/



int main(int argc, char** argv)
{
  if(argc < 2){
    cerr << endl;
    cerr << "Za malo parametrow " << endl;
    cerr << endl;
    return 1;
  }

  istringstream IStrm;

  if(!ExecProcessor(argv[1],IStrm)){
    cerr << endl;
    cerr << "Blad" << endl;
    cerr << endl;
    return 2;
  }

  // Wyswietlenie zawartosci pliku
  cout << "Wewnątrz pliku: " << endl;
  cout << endl << IStrm.str() << endl;


  // Utworzenie sceny na której umieszczone zostaną obiekty
  Scene Scene1("Scene1");

  // Utworzenie obiketu i dodanie do sceny
  std::shared_ptr<MobileObj> obj1 = make_shared<MobileObj>();
  Scene1.AddMobileObj(obj1);

  
  // Dodanie bibliotek
  Set4LibInterfaces PluginInterfaces;

  // Dodanie pluginow do mapy
  //----------
  // Ta czesc jest niepotrzebna, dopoki nie bedzie przeszukiwania mapy w execActions
  shared_ptr<LibInterface> Interface4Move = make_shared<LibInterface>("libInterp4Move.so");
  shared_ptr<LibInterface> Interface4Set = make_shared<LibInterface>("libInterp4Set.so");
  shared_ptr<LibInterface> Interface4Rotate = make_shared<LibInterface>("libInterp4Rotate.so");
  shared_ptr<LibInterface> Interface4Pause = make_shared<LibInterface>("libInterp4Pause.so");

  PluginInterfaces.Add(Interface4Move);
  PluginInterfaces.Add(Interface4Set);
  PluginInterfaces.Add(Interface4Rotate);
  PluginInterfaces.Add(Interface4Pause);
  //----------
  // Przeszukanie mapy pluginow po nazwie, zalozenie ze slowo klucz to set
  while(ExecActions(IStrm, PluginInterfaces) == true){}

  return 0;
}
  

  /////////////////////////////////////////////////////////////////////////////
  // DZIAŁA
  /////////////////////////////////////////////////////////////////////////////
  // Przeszukiwanie pliku
  /*
    
  string aux;
  while(IStrm >> aux){
    if(aux == "Set"){

      // !!! To jest w konstruktorze
      void *pLibHnd_Set = dlopen("libInterp4Set.so", RTLD_LAZY);
      Interp4Command *(*pCreateCmd_Set)(void);
      void *pFunS;

      if (!pLibHnd_Set) {
	cerr << "!!! Brak biblioteki !!!" << endl;
	return 1;
      }
      
      pFunS = dlsym(pLibHnd_Set,"CreateCmd");
      if (!pFunS) {
	cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
	return 1;
      }
      pCreateCmd_Set = *reinterpret_cast<Interp4Command* (**)(void)>(&pFunS);
      // !!! To jest w konstruktorze


      
      Interp4Command *pInterp = pCreateCmd_Set();

      if(!ExecActions_v1(IStrm, *pInterp)){
	cerr << "Something wrong" << endl;
	return 3;
      }
    }
    else if(aux == "Move"){
      void *pLibHnd_Move = dlopen("libInterp4Move.so", RTLD_LAZY);
      Interp4Command *(*pCreateCmd_Move)(void);
      void *pFunS;

      if (!pLibHnd_Move) {
	cerr << "!!! Brak biblioteki !!!" << endl;
	return 1;
      }

      pFunS = dlsym(pLibHnd_Move,"CreateCmd");
      if (!pFunS) {
	cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
	return 1;
      }
      pCreateCmd_Move = *reinterpret_cast<Interp4Command* (**)(void)>(&pFunS);
      
      Interp4Command *pInterp = pCreateCmd_Move();

      if(!ExecActions_v1(IStrm, *pInterp)){
	cerr << "Something wrong" << endl;
	return 3;
      }
    }
    else if(aux == "Rotate"){
      void *pLibHnd_Rotate = dlopen("libInterp4Rotate.so", RTLD_LAZY);
      Interp4Command *(*pCreateCmd_Rotate)(void);
      void *pFunS;

      if (!pLibHnd_Rotate) {
	cerr << "!!! Brak biblioteki !!!" << endl;
	return 1;
      }

      pFunS = dlsym(pLibHnd_Rotate,"CreateCmd");
      if (!pFunS) {
	cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
	return 1;
      }
      pCreateCmd_Rotate = *reinterpret_cast<Interp4Command* (**)(void)>(&pFunS);
      
      Interp4Command *pInterp = pCreateCmd_Rotate();

      if(!ExecActions_v1(IStrm, *pInterp)){
	cerr << "Something wrong" << endl;
	return 3;
      }
    }else if(aux == "Pause"){
      void *pLibHnd_Pause = dlopen("libInterp4Pause.so", RTLD_LAZY);
      Interp4Command *(*pCreateCmd_Pause)(void);
      void *pFunS;

      if (!pLibHnd_Pause) {
	cerr << "!!! Brak biblioteki !!!" << endl;
	return 1;
      }

      pFunS = dlsym(pLibHnd_Pause,"CreateCmd");
      if (!pFunS) {
	cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
	return 1;
      }
      pCreateCmd_Pause = *reinterpret_cast<Interp4Command* (**)(void)>(&pFunS);
      
      Interp4Command *pInterp = pCreateCmd_Pause();

      if(!ExecActions_v1(IStrm, *pInterp)){
	cerr << "Something wrong" << endl;
	return 3;
      }
    }
      
  }
}
  /////////////////////////////////////////////////////////////////////////////
  // DZIAŁA
  /////////////////////////////////////////////////////////////////////////////
  
  */


  
  //return 0;  
  
// }
  
  




/*

  //----------//



  
  // Jeszcze starszy kod
  // Utworzenie uchwytow do wtyczek
  // LibInterface Plugins(); <-------- WAZNE, ale jesli dziala bez to ok
  
  //}
  // Stary kod 
  // Handlers, open libs
  void *pLibHnd_Move = dlopen("libInterp4Move.so",RTLD_LAZY);
  void *pLibHnd_Set = dlopen("libInterp4Set.so", RTLD_LAZY);
  void *pLibHnd_Pause = dlopen("libInterp4Pause.so", RTLD_LAZY);
  void *pLibHnd_Rotate = dlopen("libInterp4Rotate.so", RTLD_LAZY);
  
  // Definicja fukncji i przydzielenie wskaznika
  Interp4Command *(*pCreateCmd_Move)(void);
  Interp4Command *(*pCreateCmd_Set)(void);
  Interp4Command *(*pCreateCmd_Pause)(void);
  Interp4Command *(*pCreateCmd_Rotate)(void);
  
  
  void *pFun; // Wskaznik na dowolna funkcje
  void *pFunS;

  if (!pLibHnd_Move || !pLibHnd_Set || !pLibHnd_Pause || !pLibHnd_Rotate) {
    cerr << "!!! Brak biblioteki !!!" << endl;
    return 1;
  }

  
  pFun = dlsym(pLibHnd_Move,"CreateCmd");
  if (!pFun) {
    cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
    return 1;
  }
  pCreateCmd_Move = *reinterpret_cast<Interp4Command* (**)(void)>(&pFun);

  
  pFunS = dlsym(pLibHnd_Set,"CreateCmd");
  if (!pFunS) {
    cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
    return 1;
    }
  pCreateCmd_Set = *reinterpret_cast<Interp4Command* (**)(void)>(&pFunS);


  // Utworzenie komendy, w zaleznosci od polecenia w pliku
  // Interp4Command *pInterp = pCreateCmd_Move();
  Interp4Command *pInterp = pCreateCmd_Set();

  // Wyswietlenie parametrow
  if(!ExecActions(IStrm, *pInterp)){
    cerr << "Something wrong" << endl;
    return 3;

  }
}
  
*/
