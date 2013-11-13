#ifndef TILEPASS_RESOURCE_MANAGER_HPP
#define TILEPASS_RESOURCE_MANAGER_HPP
#include "main.hpp"

class ResourceManager
{
public:
  ResourceManager();
  virtual ~ResourceManager();

  boost::filesystem::path get_app_root_dir();
  boost::filesystem::path get_app_data_dir();
private:

  boost::filesystem::path m_app_root_dir;
};

extern ResourceManager* gp_resource_manager;

#endif
