#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include <sstream>
#include <cstdio>
#include "Interp4Command.hh"
#include "MobileObj.hh"

#define LINE_SIZE 500

using namespace std;


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

/**********/

bool ExecActions(istream &rIStrm, Interp4Command &rInterp){
  string CmdKey;

  rIStrm >> CmdKey;

  if(CmdKey == "Move"){
    if(!rInterp.ReadParams(rIStrm)) return false;

    cout << "Parametry: " << endl;
    rInterp.PrintCmd();
    
    
  }

  /*
  cout << "Polecenie: " << CmdKey << " "  << endl;
  
  cout << endl;
  rInterp.PrintSyntax();
  cout << endl;
  */
  
  return true;
}


/**********/




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

  cout << endl << IStrm.str() << endl;
	    
  void *pLibHnd_Move = dlopen("libInterp4Move.so",RTLD_LAZY);
  Interp4Command *(*pCreateCmd_Move)(void);
  void *pFun;

  if (!pLibHnd_Move) {
    cerr << "!!! Brak biblioteki: Interp4Move.so" << endl;
    return 1;
  }


  pFun = dlsym(pLibHnd_Move,"CreateCmd");
  if (!pFun) {
    cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
    return 1;
  }
  pCreateCmd_Move = *reinterpret_cast<Interp4Command* (**)(void)>(&pFun);


  Interp4Command *pInterp = pCreateCmd_Move();

  if(!ExecActions(IStrm, *pInterp)){
    cerr << "Something wrong" << endl;
    return 3;

  }

  

  
  /*
  cout << endl;
  cout << pCmd->GetCmdName() << endl;
  cout << endl;
  pCmd->PrintSyntax();
  cout << endl;
  pCmd->PrintCmd();
  cout << endl;
  
  delete pCmd;

  dlclose(pLibHnd_Move);
  */
  
}
