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

fs::path ResourceManager::get_resource(Glib::ustring basename)
{
  return get_app_data_dir() / Glib::filename_from_utf8(basename);
}

Glib::RefPtr<Gdk::Pixbuf> ResourceManager::get_image(Glib::ustring basename)
{
  fs::path filepath = get_resource(basename);
  Glib::RefPtr<Gdk::Pixbuf> p_pixbuf;

  try {
    p_pixbuf = Gdk::Pixbuf::create_from_file(filepath.native());
  }
  catch(Glib::FileError err) {
    std::cerr << "Failed to load resource '" << Glib::filename_to_utf8(filepath.native()) << "'. "
              << "Reason: " << err.what() << std::endl << "Terminating." << std::endl;
    throw;
  }

  return p_pixbuf;
}
