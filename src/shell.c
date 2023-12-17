#include <zephyr/shell/shell.h>

// Função que realiza a FFT
void perform_fft(double val1, double val2) {
  // Aqui você colocaria o código para realizar a FFT nos valores
  printk("Realizando FFT em %f e %f\n", val1, val2);

  // Exemplo: imprimir valores fictícios de FFT
  printk("Resultado da FFT: [%.2f, %.2f]\n", val1 * 2, val2 * 2);
}

// Callback para o comando de shell
static int cmd_fft(const struct shell *shell, size_t argc, char **argv) {
  if (argc != 3) {
    printk("Uso: fft <val1> <val2>");
    return -EINVAL;
  }

  shell_print(shell, "Executando FFT em %s e %s", argv[1], argv[2]);

  double val1 = strtod(argv[1], NULL);
  double val2 = strtod(argv[2], NULL);

  perform_fft(val1, val2);

  k_msleep(200);

  return 0;
}

// SHELL_CMD_ARG_REGISTER(fft, NULL, "Executa FFT em dois valores", cmd_fft, 1,
// 0);

// Registro do comando de shell
SHELL_STATIC_SUBCMD_SET_CREATE(
    sub_fft, SHELL_CMD(fft, NULL, "Executa FFT em dois valores", cmd_fft),
    SHELL_SUBCMD_SET_END);

SHELL_CMD_REGISTER(fft, &sub_fft, "Comandos de FFT", NULL);
