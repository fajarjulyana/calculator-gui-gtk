#include <gtk/gtk.h>
#include <cmath>
// Function to perform arithmetic operations
double performOperation(double operand1, double operand2, char operation) {
    switch (operation) {
        case '+':
            return operand1 + operand2;
        case '-':
            return operand1 - operand2;
        case '*':
            return operand1 * operand2;
        case '/':
            if (operand2 != 0) {
                return operand1 / operand2;
            } else {
                return NAN; // Not a Number (for division by zero)
            }
        default:
            return NAN; // Invalid operation
    }
}

// Callback function for button clicks
static void button_clicked(GtkWidget *widget, gpointer data) {
    const gchar *button_label = gtk_button_get_label(GTK_BUTTON(widget));
    GtkEntry *entry = GTK_ENTRY(data);
    const gchar *current_text = gtk_entry_get_text(entry);

    gchar *new_text = g_strdup_printf("%s%s", current_text, button_label);
    gtk_entry_set_text(entry, new_text);
    g_free(new_text);
}

// Callback function for "=" button click
static void calculate_result(GtkWidget *widget, gpointer data) {
    GtkEntry *entry = GTK_ENTRY(data);
    const gchar *expression = gtk_entry_get_text(entry);

    // Parsing the expression
    double operand1, operand2;
    char operation;
    if (sscanf(expression, "%lf%c%lf", &operand1, &operation, &operand2) == 3) {
        // Performing the calculation
        double result = performOperation(operand1, operand2, operation);

        // Displaying the result
        gchar *result_text = g_strdup_printf("%.6f", result);
        gtk_entry_set_text(entry, result_text);
        g_free(result_text);
    } else {
        // Invalid expression
        gtk_entry_set_text(entry, "Error");
    }
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Calculator");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 400);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    GtkWidget *entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry, 0, 0, 4, 1);

    const gchar *button_labels[] = {
        "7", "8", "9", "/",
        "4", "5", "6", "*",
        "1", "2", "3", "-",
        "0", ".", "=", "+"
    };

    for (int i = 0; i < 16; ++i) {
        GtkWidget *button = gtk_button_new_with_label(button_labels[i]);
        g_signal_connect(button, "clicked", G_CALLBACK(i == 14 ? calculate_result : button_clicked), entry);

        int row = i / 4 + 1;
        int col = i % 4;
        gtk_grid_attach(GTK_GRID(grid), button, col, row, 1, 1);
    }

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
