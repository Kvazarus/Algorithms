import matplotlib.pyplot as plt
import pandas as pd

types = ['random', 'decreasing', 'almost']
thresholds = [5, 10, 20, 30, 50]
figsize = (10, 6)

def read_csv(file):
    df = pd.read_csv(file)
    return df['n'], df['time_ms']

for t in types:
    plt.figure(figsize=figsize)

    file_standard = f"csv_files/merge_{t}.csv"
    n, time_ms = read_csv(file_standard)
    plt.plot(n, time_ms, label="Merge Sort Standard", color='black', linewidth=2)

    colors = ['red', 'blue', 'green', 'orange', 'purple']
    for th, color in zip(thresholds, colors):
        file_hybrid = f"csv_files/hybrid_merge_threshold_{th}_{t}.csv"
        n, time_ms = read_csv(file_hybrid)
        plt.plot(n, time_ms, label=f"Hybrid threshold={th}", color=color, linestyle='--')

    plt.title(f"Merge Sort vs Hybrid Merge+Insertion ({t.capitalize()} array)")
    plt.xlabel("Array size (n)")
    plt.ylabel("Time (ms)")
    plt.grid(True)
    plt.legend()
    plt.tight_layout()
    plt.savefig(f"comparison_{t}.png")
    plt.close()
