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
 * \brief 
 * 
 *
 */
Interp4Command* CreateCmd(void)
{
  return Interp4Move::CreateCmd();
}


/*!
 *
 */
Interp4Move::Interp4Move(): _name("obj"), _Speed_mmS(0), _Length_mm(0)
{}


/*!
 * \brief Wyświetla składnię polecenia
 */
void Interp4Move::PrintCmd() const
{
  /*
   *  Wyswietla kolejno: nazwa polacenia, nazwa obiektu, predkosc obiektu,
   *  dlugosc drogi obiektu
   */
  cout << GetCmdName() << " " << _name << " " << _Speed_mmS << " "
       << _Length_mm  << endl;
}


/*!
 *
 */
const char* Interp4Move::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 *
 */
bool Interp4Move::ExecCmd( MobileObj  *pMobObj,  int  Socket) const
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  return true;
}


/*!
 *
 */
bool Interp4Move::ReadParams(std::istream& Strm_CmdsList)
{
  Strm_CmdsList >> _name  >>_Speed_mmS >>_Length_mm;
  
  return (!Strm_CmdsList.fail());
}


/*!
 *
 */
Interp4Command* Interp4Move::CreateCmd()
{
  return new Interp4Move();
}


/*!
 *
 */
void Interp4Move::PrintSyntax() const
{
  cout << "   Move  NazwaObiektu  Szybkosc[m/s]  DlugoscDrogi[m]" << endl;
}
