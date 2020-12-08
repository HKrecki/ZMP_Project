#include "Scene.hh"

using namespace std;


int Send(int Sk2Server, const char *sMesg)
{
  ssize_t  IlWyslanych;
  ssize_t  IlDoWyslania = (ssize_t) strlen(sMesg);

  while ((IlWyslanych = write(Sk2Server,sMesg,IlDoWyslania)) > 0) {
    IlDoWyslania -= IlWyslanych;
    sMesg += IlWyslanych;
  }
  if (IlWyslanych < 0) {
    cerr << "*** Blad przeslania napisu." << endl;
  }
  return 0;
}



class Sender {
  /*!
   * \brief Wartość tego pola decyduje o kontynuacji wykonywania wątku.
   * 
   * Wartość tego pola decyduje o kontynuacji wykonywania wątku.
   * W przypadku wartości \p true, pętla wątku będzie wykonywana.
   * Natomiast wartość \p false powoduje przerwanie pętli.
   */
   volatile bool    _ContinueLooping = true;
  /*!
   * \brief Deskryptor gniazda sieciowego, poprzez które wysyłane są polecenia.
   */
   int             _Socket = 0;
  /*!
   * \brief Wskaźnik na scenę, które stan jest przesyłany w postaci
   *        poleceń do serwera graficzneg.
   */
   Scene          *_pScn = nullptr;

  
 public:
  /*!
   * \brief Inicjalizuje obiekt deskryptorem gniazda i wskaźnikiem
   *        na scenę, na zmianę stanu które będzie ten obiekt reagował.
   */
   Sender(int Socket, Scene *pScn): _Socket(Socket), _pScn(pScn) {}

  /*!
   * \brief Sprawdza, czy pętla wątku może być wykonywana.
   * 
   * Sprawdza, czy pętla wątku może być wykonywana.
   * \retval true - pętla wątku może być nadal wykonywana.
   * \retval false - w przypadku przeciwnym.
   */
   bool ShouldCountinueLooping() const { return _ContinueLooping; }
  /*!
   * \brief Powoduje przerwanie działania pętli wątku.
   *
   * Powoduje przerwanie działania pętli wątku.
   * \warning Reakcja na tę operację nie będize natychmiastowa.
   */  
   void CancelCountinueLooping() { _ContinueLooping = false; }

  /*!
   * \brief Ta metoda jest de facto treścią wątku komunikacyjnego
   *
   * Przegląda scenę i tworzy odpowiednie polecenia, a następnie
   * wysyła je do serwera.
   * \param[in] Socket - deskryptor gniazda sieciowego, poprzez które
   *                     wysyłane są polecenia.
   */
   void Watching_and_Sending() {
     while (ShouldCountinueLooping()) {
       if (!_pScn->IsChanged())  { usleep(10000); continue; }
       _pScn->LockAccess();
       
       //------- Przeglądanie tej kolekcji to uproszczony przykład
       
       Send(_Socket,"Clear\n"); // To jest konieczne, aby usunąć wcześniejsze obiekty.
       cout << "Clear\n";
       for (const GeomObject &rObj : _pScn->_Container4Objects) {
                                     // Ta instrukcja to tylko uproszczony przykład
	 cout << rObj.GetStateDesc();
         Send(_Socket,rObj.GetStateDesc()); // Tu musi zostać wywołanie odpowiedniej
                                           // metody/funkcji gerującej polecenia dla serwera.
       }
       Send(_Socket,"Display\n"); // To jest konieczne, aby zobaczyć zmiany
       cout << "Display\n";
       
       _pScn->CancelChange();
       _pScn->UnlockAccess();
     }
   }
};
