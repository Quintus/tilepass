#ifndef TILEPASS_MAINWINDOW_HPP
#define TILEPASS_MAINWINDOW_HPP
#include "main.hpp"
#include "tileset_image.hpp"
#include "arrow_tile.hpp"

class MainWindow: public Gtk::Window
{
public:
  MainWindow();
  virtual ~MainWindow();

private:
  // GUI helpers
  void create_menus();
  void setup_signal_handlers();
  void create_layout();

  /// Reloads all widgets after selecting a new file
  void reload_workspace();
  // Updates the progress bar to the current amount of work done.
  void update_progress();

  // Event handlers
  void on_menu_file_new();
  void on_menu_file_open();
  void on_menu_file_quit();
  void on_menu_help_about();

  Gtk::VBox m_vbox;
  Gtk::HBox m_hbox;
  Gtk::VBox m_vbox2;
  Gtk::HBox m_hbox2;

  TilesetImage m_tileset;
  ArrowTile m_arrowtile;
  Gtk::Button m_next_button;
  Gtk::Button m_prev_button;
  Gtk::Label m_progress_label;
  Gtk::ProgressBar m_progress_bar;
  Gtk::Separator m_vsep1;
  Gtk::Separator m_hsep1;
  Gtk::Alignment m_align1;

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

  Glib::ustring m_csv_file;
  Glib::ustring m_img_file;
};

#endif
