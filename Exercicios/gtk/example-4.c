#include <gtk/gtk.h>

static void
tipos (GtkWidget *widget,
             gpointer   data)
{
  printf("size_t: %d\n", sizeof(size_t));
  printf("char: %d\n", sizeof(char));
  printf("short int: %d\n", sizeof(short int));
  printf("int: %d\n", sizeof(int));
  printf("long int: %d\n", sizeof(long));
  printf("long long int: %d\n", sizeof(long long));
  printf("float: %d\n", sizeof(float));
  printf("double: %d\n", sizeof(double));
}

int
main (int   argc,
      char *argv[])
{
  GtkBuilder *builder;
  GObject *window;
  GObject *button;

  gtk_init (&argc, &argv);

  /* Construct a GtkBuilder instance and load our UI description */
  builder = gtk_builder_new ();
  gtk_builder_add_from_file (builder, "builder.ui", NULL);

  /* Connect signal handlers to the constructed widgets. */
  window = gtk_builder_get_object (builder, "window");
  g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

  button = gtk_builder_get_object (builder, "tipos");
  g_signal_connect (button, "clicked", G_CALLBACK (tipos), NULL);
  
  button = gtk_builder_get_object (builder, "button1");
  // g_signal_connect (button, "clicked", G_CALLBACK (tipos), NULL);

  button = gtk_builder_get_object (builder, "button2");
  // g_signal_connect (button, "clicked", G_CALLBACK (tipos), NULL);

  button = gtk_builder_get_object (builder, "quit");
  g_signal_connect (button, "clicked", G_CALLBACK (gtk_main_quit), NULL);

  gtk_main ();

  return 0;
}