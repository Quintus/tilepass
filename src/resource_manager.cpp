#include "resource_manager.hpp"

/***************************************
 * Extern stuff
 ***************************************/

ResourceManager* gp_resource_manager;

/***************************************
 * Contructors & Destructors
 ***************************************/

ResourceManager::ResourceManager()
{
#ifdef _WIN32
#elif __linux
  char path_data[PATH_MAX];
  int count;

  count = readlink("/proc/self/exe", path_data, PATH_MAX);
  if (count < 0)
    throw std::runtime_error("Failed to retrieve the executable's path from /proc/self/exe!");

  m_app_root_dir = fs::path(std::string(path_data, count)).parent_path().parent_path();
#else
  #error Do not know how to find path to the running executable on this platform.
#endif
}

ResourceManager::~ResourceManager()
{

}

/***************************************
 * Getters & Setters
 ***************************************/

fs::path ResourceManager::get_app_root_dir()
{
  return m_app_root_dir;
}

fs::path ResourceManager::get_app_data_dir()
{
  return m_app_root_dir / Glib::filename_from_utf8("share") / Glib::filename_from_utf8("tilepass") / Glib::filename_from_utf8("data");
}
