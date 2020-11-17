#include <iostream>
#include "Interp4Rotate.hh"
#include "MobileObj.hh"

using std::cout;
using std::endl;


extern "C" {
 Interp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Rotate"; }
}




/*!
 * \brief Utworzenie nowego polecenia
 *
 *
 */
Interp4Command* CreateCmd(void)
{
  return Interp4Rotate::CreateCmd();
}


/*!
 * \brief Konstruktor domyślny
 */
Interp4Rotate::Interp4Rotate(): nazwa_obiektu("obj"), szybkosc_katowa(0), kat_obrotu(0)
{}


/*!
 * \brief Wyświetlenie parametrów
 */
void Interp4Rotate::PrintCmd() const
{
  cout << GetCmdName() << " " << szybkosc_katowa << " " << kat_obrotu << endl;
}


/*!
 * \brief Funkcja zwraca nazwę komendy
 */
const char* Interp4Rotate::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 * \brief Wykonanie polecenia
 */
bool Interp4Rotate::ExecCmd( MobileObj  *pMobObj,  int  Socket) const
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  return true;
}


/*!
 * \brief Odczytanie zadanych parametrów z komendy
 */
bool Interp4Rotate::ReadParams(std::istream& Strm_CmdsList)
{
  Strm_CmdsList >> nazwa_obiektu  >> szybkosc_katowa >> kat_obrotu;
  
  return (!Strm_CmdsList.fail());

}


/*!
 * \brief Utworzenie nowego polecenia
 */
Interp4Command* Interp4Rotate::CreateCmd()
{
  return new Interp4Rotate();
}


/*!
 * \brief Wyświetlenie składni
 */
void Interp4Rotate::PrintSyntax() const
{
  cout << "Rotate nazwa szybkosc_katowa[stopnie/s] kat_obrotu[stopnie]" << endl;
}
