#include "main.hpp"
#include "mainwindow.hpp"

MainWindow::MainWindow()
{
  mp_menubar = NULL;

  set_title("Test");
  set_default_size(200, 200);

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
