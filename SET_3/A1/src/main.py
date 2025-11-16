import numpy as np
import matplotlib.pyplot as plt

# Загружаем файл:
# n   zone   approx   exact
data = np.loadtxt("results.txt")

n = data[:, 0]
zone = data[:, 1]
approx = data[:, 2]
exact = data[:, 3]

S_exact = exact[0]

# 0 = узкая, 1 = широкая
narrow = (zone == 0)
wide = (zone == 1)

# --------------------------
#   ГРАФИКИ ПЕРВОГО ТИПА
# --------------------------

plt.figure(figsize=(10, 6))
plt.plot(n[narrow], approx[narrow], label="узкая область", linewidth=2)
plt.plot(n[wide], approx[wide], label="широкая область", linewidth=2)

plt.title("Приближённое значение площади\nв зависимости от количества точек n", fontsize=16)
plt.xlabel("n (количество испытаний)", fontsize=14)
plt.ylabel("Sₙ (приближённая площадь)", fontsize=14)

plt.grid(True, linestyle="--", alpha=0.4)
plt.legend(fontsize=12)
plt.tight_layout()
plt.savefig("approx_values.png", dpi=200)


# --------------------------
#   ГРАФИКИ ВТОРОГО ТИПА
# --------------------------

rel_narrow = np.abs(approx[narrow] - S_exact) / S_exact
rel_wide = np.abs(approx[wide] - S_exact) / S_exact

plt.figure(figsize=(10, 6))
plt.plot(n[narrow], rel_narrow, label="узкая область", linewidth=2)
plt.plot(n[wide], rel_wide, label="широкая область", linewidth=2)

plt.title("Относительное отклонение от точной площади\nв зависимости от количества точек n", fontsize=16)
plt.xlabel("n (количество испытаний)", fontsize=14)
plt.ylabel("δ(n) = |Sₙ − S_exact| / S_exact", fontsize=14)

plt.grid(True, linestyle="--", alpha=0.4)
plt.legend(fontsize=12)
plt.tight_layout()
plt.savefig("relative_error.png", dpi=200)
