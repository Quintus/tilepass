#include "main.hpp"
#include "mainwindow.hpp"

/***************************************
 * main()
 ***************************************/

int main(int argc, char* argv[])
{
  Glib::RefPtr<Gtk::Application> p_app = Gtk::Application::create(argc, argv, "eu.quintilianus.tilepass");

  MainWindow window;
  return p_app->run(window);
}
