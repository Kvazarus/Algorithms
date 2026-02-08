import pandas as pd
import matplotlib.pyplot as plt


def plot_hll_results(file_path='hll_stats.csv'):
    df = pd.read_csv(file_path)

    fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(10, 12))
    plt.subplots_adjust(hspace=0.3)

    ax1.plot(df['Step'], df['Exact'], 'g-', label='Истинное значение ($F_t^0$)', linewidth=2)
    ax1.plot(df['Step'], df['Mean_Estimate'], 'r--', label='Оценка HyperLogLog ($N_t$)', linewidth=2)

    ax1.set_title('График №1: Сравнение оценки и реального количества элементов', fontsize=14)
    ax1.set_xlabel('Размер обработанной части потока', fontsize=12)
    ax1.set_ylabel('Количество уникальных элементов', fontsize=12)
    ax1.legend()
    ax1.grid(True, linestyle='--', alpha=0.7)

    ax2.plot(df['Step'], df['Mean_Estimate'], 'b-', label='Средняя оценка $E(N_t)$', linewidth=2)

    ax2.fill_between(
        df['Step'],
        df['Lower_Bound'],
        df['Upper_Bound'],
        color='blue',
        alpha=0.2,
        label='Область неопределенности ($E \pm \sigma$)'
    )

    ax2.set_title('График №2: Статистика оценки и стандартное отклонение', fontsize=14)
    ax2.set_xlabel('Размер обработанной части потока', fontsize=12)
    ax2.set_ylabel('Количество элементов', fontsize=12)
    ax2.legend()
    ax2.grid(True, linestyle='--', alpha=0.7)

    plt.savefig('hll_analysis.png', dpi=300)
    print("Графики сохранены в файл hll_analysis.png")

    plt.show()


if __name__ == "__main__":
    plot_hll_results()