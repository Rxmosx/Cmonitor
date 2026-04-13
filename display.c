#include <stdio.h>
#include "display.h"

void display_clear() {
    printf("/033[2J");
}

void display_move_cursor(int row, int col) {
    printf("\033[%d;%dH", row, col);
}

// Liga uma cor. bold = 1 ativa negrito, color = código ANSI
void display_set_color(int bold, int color) {
    printf("\033[%d;%dm", bold ? 1 : 0, color);
}

// Volta ao estilo padrão do terminal
void display_reset_color() {
    printf("\033[0m");
}

// Desenha uma barra de progresso em texto
// Ex: CPU  [=========>          ] 45.2%
void display_bar(const char *label, double percent, int width) {
    int filled = (int)(percent / 100.0 * width);

    printf("%-6s [", label);  // label com 6 chars de largura fixa

    // Escolhe a cor da barra baseado no percentual
    if (percent > 80.0)
        display_set_color(1, COLOR_RED);
    else if (percent > 50.0)
        display_set_color(1, COLOR_YELLOW);
    else
        display_set_color(1, COLOR_GREEN);

    for (int i = 0; i < width; i++) {
        if (i < filled)
            putchar('=');
        else if (i == filled)
            putchar('>');
        else
            putchar(' ');
    }

    display_reset_color();
    printf("] %5.1f%%\n", percent);
}

// Função principal — monta a tela inteira
void display_render(double cpu, double mem_usage, char *model) {

    // display_clear();
    display_move_cursor(1, 1);

    // Título
    display_set_color(1, COLOR_CYAN);
    printf("=== sysmon ===\n\n");
    display_reset_color();

    puts(model);
    display_bar("CPU", cpu, 30);
    display_bar("MEM", mem_usage, 30);
    

    // Força o terminal a desenhar tudo agora
    fflush(stdout);
}