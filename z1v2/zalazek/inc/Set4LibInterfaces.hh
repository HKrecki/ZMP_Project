#ifndef SET4LIBINTERFACES_HH
#define SET4LIBINTERFACES_HH

#include "LibInterface.hh"
#include <string>
#include <map>
#include <memory>

using std::string;
using std::shared_ptr;
using std::pair;

/*
 * \brief Mapa przechowująca funkcjonalności pluginów
 * Plugins interfaces sets. Z tej mapy są wyszukiwane odpowiednie 
 * biblioteki.
 */
typedef std::map<std::string, std::shared_ptr<LibInterface>> PluginsIFSets;

/*
 * \brief Zestaw interfejsow do wtyczek
 */
class Set4LibInterfaces{
  PluginsIFSets _pluginIFSets; // Mapa interfejsów do pluginów, patrz mobObj
public:

  //   const PluginsIFSets& GetLibInterfaces() const { return _pluginIFSets; }
  
  void Add(shared_ptr<LibInterface> &pLibInterface){
    _pluginIFSets.insert(std::pair<string, shared_ptr<LibInterface>>(pLibInterface->GetCmdName(), pLibInterface));
  }

  bool Find(string t_libName, shared_ptr<LibInterface> &t_libIF){
    //    PluginsIFSets It = PluginsIFSets.find(t_libName);
    auto it = _pluginIFSets.find(t_libName);
    
    if(it == _pluginIFSets.end()){
      return false;
    }
    else{
      t_libIF = it->second;
      return true;
    }
  }
};

#endif
