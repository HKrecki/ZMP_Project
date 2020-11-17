#include <iostream>
#include "Interp4Move.hh"
#include "MobileObj.hh"

using std::cout;
using std::endl;


extern "C" {
 Interp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Move"; }
}




/*!
 * \brief Utworzenie polecenia
 * 
 *
 */
Interp4Command* CreateCmd(void)
{
  return Interp4Move::CreateCmd();
}


/*!
 * \brief Konstruktor domyślny
 */
Interp4Move::Interp4Move(): _name("obj"), _Speed_mmS(0), _Length_mm(0)
{}


/*!
 * \brief Wyświetla składnię polecenia move, kolejno: nazwa obiektu,
 * prędkość, długość drogi
 */
void Interp4Move::PrintCmd() const
{
  cout << GetCmdName() << " " << _name << " " << _Speed_mmS << " "
       << _Length_mm  << endl;
}


/*!
 * \brief Funkcja zwraca nazwę komendy
 */
const char* Interp4Move::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 * \brief Wykonanie polecenia
 */
bool Interp4Move::ExecCmd( MobileObj  *pMobObj,  int  Socket) const
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  return true;
}


/*!
 *   \brief Odczytanie zadanych parametrów z komendy(nazwa, predkosc, 
 * dlugosc drogi)
 */
bool Interp4Move::ReadParams(std::istream& Strm_CmdsList)
{
  Strm_CmdsList >> _name  >>_Speed_mmS >>_Length_mm;
  
  return (!Strm_CmdsList.fail());
}


/*!
 * \brief Utworzenie nowego polecenia
 */
Interp4Command* Interp4Move::CreateCmd()
{
  return new Interp4Move();
}


/*!
 * \brief Wyświetlenie składni
 */
void Interp4Move::PrintSyntax() const
{
  cout << "   Move  NazwaObiektu  Szybkosc[m/s]  DlugoscDrogi[m]" << endl;
}
