#include "main.hpp"
#include "mainwindow.hpp"
#include "resource_manager.hpp"

/***************************************
 * main()
 ***************************************/

int main(int argc, char* argv[])
{
  gp_resource_manager = new ResourceManager();

  Glib::RefPtr<Gtk::Application> p_app = Gtk::Application::create(argc, argv, "eu.quintilianus.tilepass");

  MainWindow window;
  int result = p_app->run(window);

  delete gp_resource_manager;

  return result;
}
