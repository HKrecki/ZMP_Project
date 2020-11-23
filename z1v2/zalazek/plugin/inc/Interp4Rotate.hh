#ifndef  COMMAND4ROTATE_HH
#define  COMMAND4ROTATE_HH

#ifndef __GNUG__
# pragma interface
# pragma implementation
#endif

#include "Interp4Command.hh"

/*!
 * \file
 * \brief Definicja klasy Interp4Rotate
 *
 * Plik zawiera definicję klasy Interp4Rotate, która modeluje możliość rotacji
 * obiektu.
 */

/*!
 * \brief Modeluje polecenie dla robota mobilnego, które wymusza jego
 * obrót o dowolny kąt.
 *
 *  Klasa modeluje możliwość zadania dowolnej rotacji obiektu.
 */
class Interp4Rotate: public Interp4Command {
  /*!
   * \brief Nazwa obiektu
  */
  std::string nazwa_obiektu;

  /*!
   * \brief Szybkosc kątowa w stopniach na sekundę
  */
  double szybkosc_katowa;

  /*!
   * \brief Kąt obrotu obiektu w stopniach
  */
  double kat_obrotu;
  
 public:
  /*!
   * \brief
   */
  Interp4Rotate();  
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
