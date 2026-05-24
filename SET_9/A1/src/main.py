import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import os


csv_filename = "benchmark_results.csv"

if not os.path.exists(csv_filename):
    raise ValueError(f"Ошибка: Файл {csv_filename} не найден")

df = pd.read_csv(csv_filename)

sns.set_theme(style="whitegrid", palette="tab10")

data_types = df['DataType'].unique()

for dt in data_types:
    subset = df[df['DataType'] == dt]

    fig, axes = plt.subplots(1, 2, figsize=(16, 6))
    fig.suptitle(f'Анализ строковых сортировок — Тип данных: {dt}', fontsize=16, fontweight='bold')

    # ГРАФИК 1: Время выполнения (Time_us)
    sns.lineplot(
        data=subset,
        x='Size',
        y='Time_us',
        hue='Algorithm',
        marker='o',
        linewidth=2,
        ax=axes[0]
    )
    axes[0].set_title('Время выполнения', fontsize=14)
    axes[0].set_xlabel('Размер массива (количество строк)', fontsize=12)
    axes[0].set_ylabel('Время (микросекунды)', fontsize=12)
    axes[0].legend(title='Алгоритм')

    # ГРАФИК 2: Количество посимвольных сравнений (Comparisons)
    sns.lineplot(
        data=subset,
        x='Size',
        y='Comparisons',
        hue='Algorithm',
        marker='s',
        linewidth=2,
        ax=axes[1]
    )
    axes[1].set_title('Посимвольные сравнения', fontsize=14)
    axes[1].set_xlabel('Размер массива (количество строк)', fontsize=12)
    axes[1].set_ylabel('Количество сравнений (chars)', fontsize=12)
    axes[1].legend(title='Алгоритм')

    plt.tight_layout()

    output_filename = f'plot_{dt.lower()}.png'
    plt.savefig(output_filename, dpi=300)
    print(f"График сохранен: {output_filename}")

    plt.show()
