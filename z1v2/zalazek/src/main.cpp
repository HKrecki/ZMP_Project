#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>
#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include <sstream>
#include <cstdio>
#include <memory>
#include <list>
#include "Interp4Command.hh"
#include "Set4LibInterfaces.hh"
#include "Scene.hh"
#include "MobileObj.hh"
#include "xmlinterp.hh"


#define LINE_SIZE 500

using namespace std;
using namespace xercesc;

//////////////////////////////////////////////////////////////////////////
// FUNKCJE DO TESTOW CZYTANIA XML - START

/*!
 * Czyta z pliku opis poleceń i dodaje je do listy komend,
 * które robot musi wykonać.
 * \param sFileName - (\b we.) nazwa pliku z opisem poleceń.
 * \param CmdList - (\b we.) zarządca listy poleceń dla robota.
 * \retval true - jeśli wczytanie zostało zrealizowane poprawnie,
 * \retval false - w przeciwnym przypadku.
 */
bool ReadFile(const char* sFileName, Configuration &rConfig)
{
   try {
            XMLPlatformUtils::Initialize();
   }
   catch (const XMLException& toCatch) {
            char* message = XMLString::transcode(toCatch.getMessage());
            cerr << "Error during initialization! :\n";
            cerr << "Exception message is: \n"
                 << message << "\n";
            XMLString::release(&message);
            return 1;
   }

   SAX2XMLReader* pParser = XMLReaderFactory::createXMLReader();

   pParser->setFeature(XMLUni::fgSAX2CoreNameSpaces, true);
   pParser->setFeature(XMLUni::fgSAX2CoreValidation, true);
   pParser->setFeature(XMLUni::fgXercesDynamic, false);
   pParser->setFeature(XMLUni::fgXercesSchema, true);
   pParser->setFeature(XMLUni::fgXercesSchemaFullChecking, true);

   pParser->setFeature(XMLUni::fgXercesValidationErrorAsFatal, true);

   DefaultHandler* pHandler = new XMLInterp4Config(rConfig);
   pParser->setContentHandler(pHandler);
   pParser->setErrorHandler(pHandler);

   try {
     
     if (!pParser->loadGrammar("config/config.xsd",
                              xercesc::Grammar::SchemaGrammarType,true)) {
       cerr << "!!! Plik grammar/actions.xsd, '" << endl
            << "!!! ktory zawiera opis gramatyki, nie moze zostac wczytany."
            << endl;
       return false;
     }
     pParser->setFeature(XMLUni::fgXercesUseCachedGrammarInParse,true);
     pParser->parse(sFileName);
   }
   catch (const XMLException& Exception) {
            char* sMessage = XMLString::transcode(Exception.getMessage());
            cerr << "Informacja o wyjatku: \n"
                 << "   " << sMessage << "\n";
            XMLString::release(&sMessage);
            return false;
   }
   catch (const SAXParseException& Exception) {
            char* sMessage = XMLString::transcode(Exception.getMessage());
            char* sSystemId = xercesc::XMLString::transcode(Exception.getSystemId());

            cerr << "Blad! " << endl
                 << "    Plik:  " << sSystemId << endl
                 << "   Linia: " << Exception.getLineNumber() << endl
                 << " Kolumna: " << Exception.getColumnNumber() << endl
                 << " Informacja: " << sMessage 
                 << endl;

            XMLString::release(&sMessage);
            XMLString::release(&sSystemId);
            return false;
   }
   catch (...) {
            cout << "Zgloszony zostal nieoczekiwany wyjatek!\n" ;
            return false;
   }

   delete pParser;
   delete pHandler;
   return true;
}

// FUNKCJE DO TESTOW CZYTANIA XML - KONIEC
//////////////////////////////////////////////////////////////////////////

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

  // Znalezienie biblioteki w mapie
  if (t_plugins.Find(aux.c_str(), auxInterface)){
    // TODO: Uchwyt na podstawie polecenia


    cout << endl;
    // Jeśli znaleziono daną komendę
    cout << "Found command: " << aux.c_str() << endl;

    // Przygotowanie nazwy biblioteki na podstawie komendy
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
  
  // TUTAJ TESTY CZYTANIA XML //
  cout << "----- Testy czytania xml -----" << endl;
  Configuration Config;
  
  if (!ReadFile("config/config.xml",Config)) return 1;
  
  
  cout << "----- Testy czytania xml -----" << endl;
  
  return 0;
}
  // TUTAJ TESTY CZYTANIA XML //


  
  /* 
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
  */
  // DO TEGO MOMENTU DZIALALO

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
