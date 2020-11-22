#include <iostream>
#include "Interp4Pause.hh"
#include "MobileObj.hh"

using std::cout;
using std::endl;


extern "C" {
 Interp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Pause"; }
}




/*!
 * \brief
 *
 *
 */
Interp4Command* CreateCmd(void)
{
  return Interp4Pause::CreateCmd();
}


/*!
 * \brief Konstruktor domyślny
 */
Interp4Pause::Interp4Pause(): _Czas_pauzy_ms(0)
{}


/*!
 * \brief Wyświetla składnię polecenia Pause, w tym czas zatrzymania symulacji
 */
void Interp4Pause::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << " " <<_Czas_pauzy_ms<< endl;
}


/*!
 * \brief Funkcja zwraca nazwę komendy
 */
const char* Interp4Pause::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 * \brief Wykonanie polecenia
 */
bool Interp4Pause::ExecCmd( MobileObj  *pMobObj,  int  Socket) const
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  return true;
}


/*!
 * \brief Odczytanie zadanych parametrów z komendy(czas wstrzymania)
 */
bool Interp4Pause::ReadParams(std::istream& Strm_CmdsList)
{
  Strm_CmdsList >> _Czas_pauzy_ms;
  
  return (!Strm_CmdsList.fail());

  
}


/*!
 * \brief Utworzenie nowego polecenia
 */
Interp4Command* Interp4Pause::CreateCmd()
{
  return new Interp4Pause();
}


/*!
 * \brief Wyświetlenie składni
 */
void Interp4Pause::PrintSyntax() const
{
  cout << "   Pause    Czas wstrzymania symulacji[ms]" << endl;
}
