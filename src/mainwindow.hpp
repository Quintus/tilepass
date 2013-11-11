#ifndef TILEPASS_MAINWINDOW_HPP
#define TILEPASS_MAINWINDOW_HPP
#include "main.hpp"

class MainWindow: public Gtk::Window
{
public:
  MainWindow();
  virtual ~MainWindow();

private:
  void create_menus();
  void setup_signal_handlers();
  void create_layout();

  void on_menu_file_new();
  void on_menu_file_open();
  void on_menu_file_quit();
  void on_menu_help_about();

  Gtk::VBox m_vbox;
  Gtk::MenuItem* mp_menu_file;
  Gtk::MenuItem* mp_menu_help;
  Gtk::Menu* mp_menu_filemenu;
  Gtk::Menu* mp_menu_helpmenu;
  Gtk::MenuItem* mp_menu_file_new;
  Gtk::MenuItem* mp_menu_file_open;
  Gtk::SeparatorMenuItem* mp_menu_file_sep1;
  Gtk::MenuItem* mp_menu_file_quit;
  Gtk::MenuItem* mp_menu_help_about;
  Gtk::MenuBar* mp_menubar;
};

#endif
