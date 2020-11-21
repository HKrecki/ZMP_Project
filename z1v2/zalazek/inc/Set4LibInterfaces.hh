#ifndef SET4LIBINTERFACES_HH
#define SET4LIBINTERFACES_HH

#include "LibInterface.hh"
#include <string>
#include <map>
#include <memory>


/*
 * \brief Zdefiniowanie mapy, przechowującej funkcjonalności pluginów
 * Plugins interfaces sets
 */
typedef std::map<std::string, std::shared_ptr<LibInterface>> PluginsIFSets;

/*
 * \brief 
 */
class Set4LibInterfaces{
  PluginsIFSets _pluginIFSets; // Mapa interfejsów do pluginów
public:
  

};

#endif
