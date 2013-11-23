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
  void on_menu_file_save();
  void on_menu_file_saveas();
  void on_menu_edit_uparrow();
  void on_menu_edit_rightarrow();
  void on_menu_edit_downarrow();
  void on_menu_edit_leftarrow();
  void on_menu_edit_prev();
  void on_menu_edit_next();
  void on_menu_help_about();
  void on_next_button_clicked();
  void on_prev_button_clicked();
  void on_tile_selected(int oldindex);

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

  Glib::RefPtr<Gtk::AccelGroup> mp_accel_group;
  Gtk::MenuItem* mp_menu_file;
  Gtk::MenuItem* mp_menu_edit;
  Gtk::MenuItem* mp_menu_help;
  Gtk::Menu* mp_menu_filemenu;
  Gtk::Menu* mp_menu_helpmenu;
  Gtk::Menu* mp_menu_editmenu;
  Gtk::MenuItem* mp_menu_file_new;
  Gtk::MenuItem* mp_menu_file_open;
  Gtk::MenuItem* mp_menu_file_save;
  Gtk::MenuItem* mp_menu_file_saveas;
  Gtk::SeparatorMenuItem* mp_menu_file_sep1;
  Gtk::SeparatorMenuItem* mp_menu_file_sep2;
  Gtk::MenuItem* mp_menu_file_quit;
  Gtk::MenuItem* mp_menu_edit_prev;
  Gtk::MenuItem* mp_menu_edit_next;
  Gtk::SeparatorMenuItem* mp_menu_edit_sep1;
  Gtk::MenuItem* mp_menu_edit_uparrow;
  Gtk::MenuItem* mp_menu_edit_downarrow;
  Gtk::MenuItem* mp_menu_edit_leftarrow;
  Gtk::MenuItem* mp_menu_edit_rightarrow;
  Gtk::MenuItem* mp_menu_help_about;
  Gtk::MenuBar* mp_menubar;

  Glib::ustring m_csv_file;
  Glib::ustring m_img_file;
};

#endif
