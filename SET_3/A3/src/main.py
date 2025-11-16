import matplotlib.pyplot as plt
import pandas as pd

types = ['random', 'decreasing', 'almost']
figsize = (10, 6)

def read_csv(file):
    df = pd.read_csv(file)
    return df['n'], df['time_ms']

for t in types:
    plt.figure(figsize=figsize)

    file_qs = f"csv_files/quick_sort_{t}.csv"
    n, time_ms = read_csv(file_qs)
    plt.plot(n, time_ms, label="Quick Sort", color='red', linestyle='--')

    file_intro = f"csv_files/introsort_{t}.csv"
    n, time_ms = read_csv(file_intro)
    plt.plot(n, time_ms, label="IntroSort", color='blue', linewidth=2)

    plt.title(f"Quick Sort vs IntroSort ({t.capitalize()} array)")
    plt.xlabel("Array size (n)")
    plt.ylabel("Time (ms)")
    plt.grid(True)
    plt.legend()
    plt.tight_layout()
    plt.savefig(f"comparison_{t}.png")
    plt.close()
