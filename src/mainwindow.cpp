#include "mainwindow.hpp"

/***************************************
 * Constructors & Destructors
 ***************************************/

MainWindow::MainWindow()
  : Gtk::Window(),
    m_vsep1(Gtk::ORIENTATION_VERTICAL),
    m_hsep1(Gtk::ORIENTATION_HORIZONTAL),
    m_align1(0.5, 0.5, 0, 0)
{
  mp_menubar = NULL;

  set_title("Test");
  set_default_size(400, 500);

  m_progress_label.set_text("Progress:");
  m_progress_label.set_alignment(Gtk::ALIGN_START);
  m_next_button.set_label("Next");
  m_prev_button.set_label("Previous");

  create_menus();
  create_layout();
  setup_signal_handlers();

  show_all_children();
}

MainWindow::~MainWindow()
{
  delete mp_menubar;
  delete mp_menu_file;
  delete mp_menu_help;
}

/***************************************
 * Helpers
 ***************************************/

void MainWindow::create_menus()
{
  ////////// File //////////
  mp_menu_filemenu  = new Gtk::Menu();
  mp_menu_file_new  = new Gtk::MenuItem("New");
  mp_menu_file_open = new Gtk::MenuItem("Open");
  mp_menu_file_sep1 = new Gtk::SeparatorMenuItem();
  mp_menu_file_quit = new Gtk::MenuItem("Quit");
  mp_menu_filemenu->append(*mp_menu_file_new);
  mp_menu_filemenu->append(*mp_menu_file_open);
  mp_menu_filemenu->append(*mp_menu_file_sep1);
  mp_menu_filemenu->append(*mp_menu_file_quit);

  ////////// Help //////////
  mp_menu_helpmenu = new Gtk::Menu();
  mp_menu_help_about = new Gtk::MenuItem("About");
  mp_menu_helpmenu->append(*mp_menu_help_about);

  ////////// The menubar //////////
  mp_menubar   = new Gtk::MenuBar();
  mp_menu_file = new Gtk::MenuItem("File");
  mp_menu_help = new Gtk::MenuItem("Help");

  mp_menu_file->set_submenu(*mp_menu_filemenu);
  mp_menu_help->set_submenu(*mp_menu_helpmenu);

  mp_menubar->append(*mp_menu_file);
  mp_menubar->append(*mp_menu_help);
}

void MainWindow::setup_signal_handlers()
{
  mp_menu_file_new->signal_activate().connect(sigc::mem_fun(*this, &MainWindow::on_menu_file_new));
  mp_menu_file_open->signal_activate().connect(sigc::mem_fun(*this, &MainWindow::on_menu_file_open));
  mp_menu_file_quit->signal_activate().connect(sigc::mem_fun(*this, &MainWindow::on_menu_file_quit));
  mp_menu_help_about->signal_activate().connect(sigc::mem_fun(*this, &MainWindow::on_menu_help_about));
}

void MainWindow::create_layout()
{
  m_vbox.pack_start(*mp_menubar, Gtk::PACK_SHRINK);
  m_vbox.pack_start(m_hbox, Gtk::PACK_EXPAND_WIDGET);
  m_hbox.pack_start(m_vbox2, Gtk::PACK_EXPAND_WIDGET);

  m_vbox2.set_spacing(10);
  m_align1.add(m_arrowtile);
  m_vbox2.pack_start(m_align1, Gtk::PACK_EXPAND_WIDGET);
  m_vbox2.pack_start(m_progress_label, Gtk::PACK_SHRINK);
  m_vbox2.pack_start(m_progress_bar, Gtk::PACK_SHRINK);
  m_vbox2.pack_start(m_hsep1, Gtk::PACK_SHRINK);
  m_vbox2.pack_start(m_hbox2, Gtk::PACK_SHRINK);

  m_hbox2.set_border_width(20);
  m_hbox2.set_spacing(20);
  m_hbox2.pack_end(m_next_button, Gtk::PACK_SHRINK);
  m_hbox2.pack_end(m_prev_button, Gtk::PACK_SHRINK);

  m_hbox.pack_start(m_vsep1, Gtk::PACK_SHRINK);
  m_hbox.pack_start(m_tileset, Gtk::PACK_EXPAND_WIDGET);

  add(m_vbox);
}

/***************************************
 * Signal handlers
 ***************************************/

void MainWindow::on_menu_file_quit()
{
  close();
}

void MainWindow::on_menu_file_new()
{
  Glib::RefPtr<Gtk::FileFilter> csv_filter = Gtk::FileFilter::create();
  Glib::RefPtr<Gtk::FileFilter> img_filter = Gtk::FileFilter::create();
  Glib::RefPtr<Gtk::FileFilter> any_filter = Gtk::FileFilter::create();
  csv_filter->set_name("Comma-separated value files (*.csv)");
  csv_filter->add_pattern("*.csv");
  img_filter->set_name("Image files (*.png)");
  img_filter->add_pattern("*.png");
  any_filter->set_name("Any files (*)");
  any_filter->add_pattern("*");

  Gtk::FileChooserDialog csv_fd(*this, "Choose the passability file", Gtk::FILE_CHOOSER_ACTION_SAVE);
  csv_fd.add_filter(csv_filter);
  csv_fd.add_filter(any_filter);
  csv_fd.add_button("Cancel", Gtk::RESPONSE_CANCEL);
  csv_fd.add_button("OK", Gtk::RESPONSE_OK);

  Gtk::FileChooserDialog img_fd(*this, "Choose the tileset image file", Gtk::FILE_CHOOSER_ACTION_OPEN);
  img_fd.add_filter(img_filter);
  img_fd.add_filter(any_filter);
  img_fd.add_button("Cancel", Gtk::RESPONSE_CANCEL);
  img_fd.add_button("OK", Gtk::RESPONSE_OK);

  if (csv_fd.run() != Gtk::RESPONSE_OK)
    return;
  csv_fd.hide();

  if (img_fd.run() != Gtk::RESPONSE_OK)
    return;

  m_csv_file = Glib::filename_to_utf8(csv_fd.get_filename());
  m_img_file = Glib::filename_to_utf8(img_fd.get_filename());

  reload_workspace();
}

void MainWindow::on_menu_file_open()
{

}

void MainWindow::on_menu_help_about()
{
  Gtk::AboutDialog ad;
  ad.set_version("0.0.1");
  ad.set_copyright("Copyright © 2013 Marvin Gülker");
  ad.run();
}

/***************************************
 * Helper methods
 ***************************************/

void MainWindow::reload_workspace()
{
  m_tileset.load_tileset(m_img_file, 32); // FIXME: Make tile edge length configurable
  m_arrowtile.set_tile(m_tileset.get_current_tile());
}

void MainWindow::update_progress()
{
  
}
