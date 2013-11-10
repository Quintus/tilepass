#include <stdio.h>
#include <gtk/gtk.h>

int main(int argc, char* argv[])
{
  GtkWidget* p_window;

  gtk_init(&argc, &argv);

  p_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(p_window), "My Window");

  g_signal_connect(p_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

  gtk_widget_show(p_window);
  gtk_main();

  return 0;
}
