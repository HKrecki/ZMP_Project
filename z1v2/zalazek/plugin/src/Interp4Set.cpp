#include <iostream>
#include "Interp4Set.hh"
#include "MobileObj.hh"

using std::cout;
using std::endl;


extern "C" {
 Interp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Set"; }
}




/*!
 * \brief Utworzenie polecenia
 *
 *
 */
Interp4Command* CreateCmd(void)
{
  return Interp4Set::CreateCmd();
}


/*!
 * \brief Konstruktor domyślny
 */
Interp4Set::Interp4Set(): _name("obj"), _wsp_x(0), _wsp_y(0), _kat_OZ(0)
{}


/*!
 * \brief Wyświetla składnię polecenia set, kolejno: nzawa obiektu, wsp.
 * x, wsp y, kąt obrotu.
 */
void Interp4Set::PrintCmd() const
{
  cout << GetCmdName() << " " << _name << " " << _wsp_x << " "
       << _wsp_y << " " << _kat_OZ << endl;
}


/*!
 * \brief Funkcja zwraca nazwę komendy
 */
const char* Interp4Set::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 * \brief Wykonanie polecenia
 */
bool Interp4Set::ExecCmd( MobileObj  *pMobObj,  int  Socket) const
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  return true;
}


/*!
 * \brief Odczytanie zadanych parametrów z komendy(nazwa, wsp.x, wsp.y, 
 * rotacja)
 */
bool Interp4Set::ReadParams(std::istream& Strm_CmdsList)
{
  Strm_CmdsList >> _name >> _wsp_x >> _wsp_y >> _kat_OZ;

  return (!Strm_CmdsList.fail());
  
}


/*!
 *
 */
Interp4Command* Interp4Set::CreateCmd()
{
  return new Interp4Set();
}


/*!
 *
 */
void Interp4Set::PrintSyntax() const
{
  cout << "   Set  NazwaObiektu  WspolrzednaX[mm] WspolrzednaY[mm] Katobrotu[stopnie]" << endl;
}
