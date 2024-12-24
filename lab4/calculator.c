#include <gtk/gtk.h>

static void on_calculate(GtkWidget *widget, gpointer data) {
    GtkEntry **entries = (GtkEntry **)data;
    const char *num1_text = gtk_entry_get_text(entries[0]);
    const char *num2_text = gtk_entry_get_text(entries[1]);
    const char *op_text = gtk_entry_get_text(entries[2]);

    double num1 = atof(num1_text);
    double num2 = atof(num2_text);
    double result = 0.0;

    if (strcmp(op_text, "+") == 0) {
        result = num1 + num2;
    } else if (strcmp(op_text, "-") == 0) {
        result = num1 - num2;
    } else if (strcmp(op_text, "*") == 0) {
        result = num1 * num2;
    } else if (strcmp(op_text, "/") == 0) {
        if (num2 != 0) {
            result = num1 / num2;
        } else {
            gtk_label_set_text(GTK_LABEL(entries[3]), "Error: Division by zero!");
            return;
        }
    } else {
        gtk_label_set_text(GTK_LABEL(entries[3]), "Error: Invalid operator!");
        return;
    }

    char result_text[100];
    snprintf(result_text, sizeof(result_text), "Result: %.2f", result);
    gtk_label_set_text(GTK_LABEL(entries[3]), result_text);
}

int main(int argc, char *argv[]) {
    GtkWidget *window, *grid, *entry1, *entry2, *entry_op, *label_result, *button_calc;

    gtk_init(&argc, &argv);

    // Create main window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Calculator");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create grid layout
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Create widgets
    entry1 = gtk_entry_new();
    entry2 = gtk_entry_new();
    entry_op = gtk_entry_new();
    label_result = gtk_label_new("Result: ");
    button_calc = gtk_button_new_with_label("Calculate");

    // Add widgets to grid
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Number 1:"), 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry1, 1, 0, 2, 1);

    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Operator (+, -, *, /):"), 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry_op, 1, 1, 2, 1);

    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Number 2:"), 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry2, 1, 2, 2, 1);

    gtk_grid_attach(GTK_GRID(grid), button_calc, 1, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), label_result, 0, 4, 3, 1);

    // Pack entries into array for callback
    GtkEntry *entries[4] = {GTK_ENTRY(entry1), GTK_ENTRY(entry2), GTK_ENTRY(entry_op), GTK_ENTRY(label_result)};

    // Connect signal to button
    g_signal_connect(button_calc, "clicked", G_CALLBACK(on_calculate), entries);

    // Show all widgets
    gtk_widget_show_all(window);

    gtk_main();
    return 0;
}
