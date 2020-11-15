#ifndef  COMMAND4SET_HH
#define  COMMAND4SET_HH

#ifndef __GNUG__
# pragma interface
# pragma implementation
#endif

#include "Interp4Command.hh"

/*!
 * \file
 * \brief Definicja klasy Interp4Set
 *
 * Plik zawiera definicję klasy Interp4Move i funkcji skladowych. Całość jest
 * opdpowiedzialna za wstępne ustwaienie obiektu na scenie.
 */

/*!
 * \brief Modeluje polecenie dla robota mobilnego, które inicjalizuje położenie
 * obiektu na scenie.
 *
 *  Klasa modeluje ustawienie obiektu na scenie
 */
class Interp4Set: public Interp4Command {

  /*!
   * \brief Nazwa obiektu
   */
  std::string _name;

  /*!
   * \brief Położenie na scenie we współrzędej X
   */
  double _wsp_x;

  /*!
   * \brief Położenie na scenie we współrzędnej Y
   */
  double _wsp_y;

  /*!
   * \brief Kąt obrotu w okół osi Z
   */
  double _kat_OZ;
  
 public:
  /*!
   * \brief
   */
  Interp4Set();  
  /*!
   * \brief Wyświetla postać bieżącego polecenia (nazwę oraz wartości parametrów)
   */
  virtual void PrintCmd() const;
  /*!
   * \brief Wyświetla składnię polecenia
   */
  virtual void PrintSyntax() const;
  /*!
   * \brief Wyświetla nazwę polecenia
   */
  virtual const char* GetCmdName() const;
  /*!
   * \brief Wykonuje polecenie oraz wizualizuje jego realizację
   */
  virtual bool ExecCmd( MobileObj  *pMobObj, int Socket) const;
  /*!
   * \brief Czyta wartości parametrów danego polecenia
   */
  virtual bool ReadParams(std::istream& Strm_CmdsList);
  /*!
   * \brief Wyświetla wartości wczytanych parametrów
   */
  virtual void PrintParams() {}
  /*!
   * \brief
   *
   *  Ta metoda nie musi być zdefiniowna w klasie bazowej.
   */
  static Interp4Command* CreateCmd();
 };

#endif
